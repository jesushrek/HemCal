#include "swephexp.h"
#include "constants.h"

//27.7103° N, 85.3222° E
double geoPos[] = { 
    [Longitude] = 85.3222, 
    [Latitude] = 27.7103, 
    [Altitude] = 1324.0 
};

typedef struct 
{ 
    int tithi;
    double tithiStart;
    double tithiEnd;
    EnumPaksha paksha;

} Tithi;

typedef struct 
{ 
    int nakshatra;
    double nakshatraStart;
    double nakshatraEnd;

} Nakshatra;

typedef struct 
{ 
    int yoga;
    double yogaStart;
    double yogaEnd;

} Yoga;

typedef struct 
{ 
    int muhurata;
    double muhurataStart;
    double muhurataEnd;

} Muhuratas;

typedef struct
{ 
    int karana;
    double karanaStart;
    double karanaEnd;
} Karana;

typedef struct
{ 
    double sunrise;
    double sunset;
    double ayanamsa;

    Date adDate;
    Date bsDate;
    double julianDate;

    Tithi tithi[2];
    Nakshatra nakshatras[2];
    Yoga yogas[2];
    int vara;
    Muhuratas muhuratas[30];
    Karana karana[4];

} PanchangaDay;

double getTithi(double jd)
{ 
    char serr[AS_MAXCH];
    int iflag = SEFLG_SWIEPH | SEFLG_SIDEREAL;

    double x2[6];

    int iflgret = swe_calc_ut(jd, SE_SUN, iflag, x2, serr);

    if(iflgret < 0)
        printf("Error: %s \n", serr);

    double sunLongitude = x2[0];

    iflgret = swe_calc_ut(jd, SE_MOON, iflag, x2, serr);

    if(iflgret < 0)
        printf("Error: %s \n", serr);

    double moonLongitude = x2[0];

    double diff = moonLongitude - sunLongitude;

    if(diff < 0)
        diff += 360;

    return (diff / 12) + 1; // tithi
}

double tithiBoundry(double jd, int tithiIndex)
{ 
    double precision = 0.5 / 1440.0;
    double low = jd - 1;
    double high = jd + 1;
    double mid;

    for(int i = 0; i < 20; ++i)
    {
        mid = (low + high) / 2.0;

        double currentTithi = getTithi(mid);

        if( tithiIndex >= 30.0 && currentTithi <= 15.0)
            currentTithi += 30.0;

        if( currentTithi < tithiIndex)
            low = mid;
        else 
            high = mid;
    }

    return mid;
}

double getNakshatra(double jd)
{ 
    char serr[AS_MAXCH];
    int iflag = SEFLG_SWIEPH | SEFLG_SIDEREAL;

    double x2[6];

    int iflgret = swe_calc_ut(jd, SE_MOON, iflag, x2, serr);

    if(iflgret < 0)
        printf("Error: %s \n", serr);

    return (x2[0] / (360.0 / 27.0)) + 1.0;
}

double nakshatraBoundry(double jd, int nakshatraIndex)
{ 
    double precision = 0.5 / 1440.0;
    double low = jd - 1;
    double high = jd + 1;
    double mid;

    for(int i = 0; i < 20; ++i)
    {
        mid = (low + high) / 2.0;

        double currentnakshatra = getNakshatra(mid);

        if( nakshatraIndex >= 27.0 && currentnakshatra <= 13.5)
            currentnakshatra += 27.0;

        if( currentnakshatra < nakshatraIndex)
            low = mid;
        else 
            high = mid;
    }

    return mid;
}

double getYoga(double jd)
{ 
    char serr[AS_MAXCH];
    int iflag = SEFLG_SWIEPH | SEFLG_SIDEREAL;

    double x2[6];

    int iflgret = swe_calc_ut(jd, SE_SUN, iflag, x2, serr);

    if(iflgret < 0)
        printf("Error: %s \n", serr);

    double sunLongitude = x2[0];

    iflgret = swe_calc_ut(jd, SE_MOON, iflag, x2, serr);

    if(iflgret < 0)
        printf("Error: %s \n", serr);

    double moonLongitude = x2[0];

    double diff = moonLongitude + sunLongitude;
    if(diff >= 360) diff -= 360;
    if(diff < 0) diff += 360;

    return (diff / (360.0 / 27.0)) + 1.0;
}

double yogaBoundry(double jd, int yogaIndex)
{ 
    double precision = 0.5 / 1440.0;
    double low = jd - 1;
    double high = jd + 1;
    double mid;

    for(int i = 0; i < 20; ++i)
    {
        mid = (low + high) / 2.0;

        double currentyoga = getYoga(mid);

        if( yogaIndex >= 27.0 && currentyoga <= 13.5)
            currentyoga += 27.0;

        if( currentyoga < yogaIndex)
            low = mid;
        else 
            high = mid;
    }

    return mid;
}

PanchangaDay returnPanchanga(Date date)
{ 
    swe_set_sid_mode(SE_SIDM_LAHIRI, 0, 0);
    char serr[AS_MAXCH];
    PanchangaDay pday = {};
    double totalJulianDay = swe_julday(date.year, date.month, date.day, 0, SE_GREG_CAL);

    int rsmi = SE_CALC_RISE | SE_BIT_HINDU_RISING;

    // this is sun rise
    int  returnCode = swe_rise_trans(totalJulianDay, SE_SUN, NULL, SEFLG_SWIEPH, rsmi, geoPos, 0, 0, &pday.sunrise, serr); 

    if(returnCode == ERR)
    { 
        //handle it 
        printf("%s\n", serr);
    }

    // this is sun set
    rsmi = SE_CALC_SET | SE_BIT_HINDU_RISING;
    returnCode = swe_rise_trans(pday.sunrise, SE_SUN, NULL, SEFLG_SWIEPH, rsmi, geoPos, 0, 0, &pday.sunset, serr);

    if(returnCode == ERR)
    { 
        //handle it
        printf("%s\n", serr);
    }


    pday.tithi[0].tithi = getTithi(pday.sunrise);
    int previousTithi  = pday.tithi[0].tithi - 1;

    if(previousTithi == 0)
        previousTithi = 30;

    pday.tithi[0].tithiStart = tithiBoundry(pday.sunrise, previousTithi);
    pday.tithi[0].tithiEnd = tithiBoundry(pday.sunrise, pday.tithi[0].tithi);

    int futureTithi = pday.tithi[0].tithi + 1;

    if(futureTithi > 30)
        pday.tithi[1].tithi = 1;
    else
        pday.tithi[1].tithi = futureTithi;

    pday.tithi[1].tithiStart = pday.tithi[0].tithiEnd;
    pday.tithi[1].tithiEnd  = tithiBoundry(pday.tithi[0].tithiEnd + 0.1, pday.tithi[1].tithi);

    pday.tithi[0].paksha = (pday.tithi[0].tithi <= 15)? ShuklaPaksha : KrishnaPaksha;
    pday.tithi[1].paksha = (pday.tithi[1].tithi <= 15)? ShuklaPaksha : KrishnaPaksha;

    pday.nakshatras[0].nakshatra = getNakshatra(pday.sunrise);
    int previousNakshatra = (pday.nakshatras[0].nakshatra - 1);

    if(previousNakshatra == 0) 
        previousNakshatra = 27;

    pday.nakshatras[0].nakshatraStart = nakshatraBoundry(pday.sunrise, previousNakshatra);
    pday.nakshatras[0].nakshatraEnd = nakshatraBoundry(pday.sunrise, pday.nakshatras[0].nakshatra);

    int futureNakshatra = (pday.nakshatras[0].nakshatra + 1);
    if(futureNakshatra > 27)
        pday.nakshatras[1].nakshatra = 1;
    else
        pday.nakshatras[1].nakshatra = futureNakshatra;

    pday.nakshatras[1].nakshatraStart = pday.nakshatras[0].nakshatraEnd;
    pday.nakshatras[1].nakshatraEnd = nakshatraBoundry(pday.nakshatras[0].nakshatraEnd + 0.1, pday.nakshatras[1].nakshatra);

    pday.yogas[0].yoga = getYoga(pday.sunrise);

    int previousYoga = (pday.yogas[0].yoga - 1);
    if(previousYoga == 0)
        previousYoga = 27;

    pday.yogas[0].yogaStart = yogaBoundry(pday.sunrise, previousYoga);
    pday.yogas[0].yogaEnd = yogaBoundry(pday.sunrise, pday.yogas[0].yoga);

    int futureYoga = (pday.yogas[0].yoga + 1);
    if(futureYoga > 27)
        pday.yogas[1].yoga = 1;
    else
        pday.yogas[1].yoga = futureYoga;

    pday.yogas[1].yogaStart = pday.yogas[0].yogaEnd;
    pday.yogas[1].yogaEnd = yogaBoundry(pday.yogas[0].yogaEnd + 0.1, pday.yogas[1].yoga);

    int alignment = 1.5;
    pday.vara = (int)(pday.sunrise + alignment) % 7;

    return pday;
}
