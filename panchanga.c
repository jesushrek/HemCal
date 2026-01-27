#include "swephexp.h"
#include "constants.h"
#include "convertor.c"

double geoPos[] = { 
    [Longitude] = 85.3222,
    [Latitude] = 27.7103,
    [Altitude] = 1324.0
};

typedef enum 
{
    CALC_TITHI,
    CALC_NAKSHATRA,
    CALC_KARANA,
    CALC_YOGA,
} CalcType;

typedef struct 
{ 
    int tithi;
    double start;
    double end;
} Tithi;

typedef struct 
{ 
    int yoga;
    double start;
    double end;
} Yoga;

typedef struct
{ 
    int muhurata;
    double start;
    double end;
} Muhuratas;

typedef struct 
{ 
    int karana;
    double start;
    double end;
} Karana;

typedef struct 
{ 
    int nakshatra;
    double start;
    double end;
} Nakshatra;

typedef struct 
{ 
    double sunrise;
    double sunset;
    double ayanamsa;

    Date adDate;
    Date bsDate;

    Tithi tithi[2];
    Nakshatra nakshatra[2];
    Yoga yoga[2];

    int vara;
    Muhuratas muhurata[30];
    Karana karana[4];

    int sunRashi;
    int lunarMonth;
} Panchanga;

double getArc(double jd, CalcType type) 
{ 
    char serr[AS_MAXCH];
    int iflag = SEFLG_SWIEPH | SEFLG_SIDEREAL;

    double x2[6];
    swe_calc_ut(jd, SE_SUN, iflag, x2, serr);
    double lonSun = x2[0];

    swe_calc_ut(jd, SE_MOON, iflag, x2, serr);
    double lonMoon = x2[0];

    double result;
    switch(type)
    { 
        case CALC_TITHI:
            result = lonMoon - lonSun;
            break;
        case CALC_NAKSHATRA:
            result = lonMoon;
            break;
        case CALC_YOGA:
            result = lonMoon + lonSun;
            break;
        case CALC_KARANA:
            result = lonMoon - lonSun;
            break;
        default:
            return -535.0;
    }

    while(result < 0) result += 360;
    while(result >= 360) result -= 360;

    if(type == CALC_TITHI)
        return result / 12.0;
    if(type == CALC_KARANA)
        return result / 6.0;

    return (result / (360.0 / 27.0));
}

double getBoundry(double jd, CalcType type, double index)
{ 
    double low = jd - 1;
    double high = jd + 1;
    double mid;

    double boundUpper = 0.0;

    switch(type)
    { 
        case CALC_KARANA:
            boundUpper = 60;
            break;

        case CALC_YOGA:
        case CALC_NAKSHATRA:
            boundUpper = 27.0;
            break;

        case CALC_TITHI:
            boundUpper = 30.0;
            break;

        default:
            return -500.0;
    }

    double result = getArc(jd, type);
    for(int i = 0; i < 20; ++i)
    { 
        mid = (low + high) / 2.0;
        double current = getArc(mid, type);

        if(index > (boundUpper / 2) && current <= (boundUpper / 2))
            current += boundUpper;

        if(current < index)
            low = mid;
        else 
            high = mid;
    }

    return mid;
}

Panchanga returnPanchanga(Date date)
{ 
    swe_set_sid_mode(SE_SIDM_LAHIRI, 0, 0);
    Panchanga current = {0};

    current.adDate = date; 
    current.bsDate = adToBs(date); 

    char serr[AS_MAXCH];
    int iflag = SEFLG_SWIEPH | SEFLG_SIDEREAL;

    double jdUt = swe_julday(date.year, date.month, date.day, 0, SE_GREG_CAL);

    int rsmi = SE_CALC_RISE | SE_BIT_HINDU_RISING;
    
    // Get sunrise
    int returnCode = swe_rise_trans(jdUt, SE_SUN, NULL, SEFLG_SWIEPH, rsmi, geoPos, 0, 0, &current.sunrise, serr);

    // Get next sunrise (needed for calculating things that span to next day)
    double nextSunrise = 0;
    swe_rise_trans(current.sunrise + 0.5, SE_SUN, NULL, SEFLG_SWIEPH, rsmi, geoPos, 0, 0, &nextSunrise, serr);

    // Get sunset
    rsmi = SE_CALC_SET | SE_BIT_HINDU_RISING;
    returnCode = swe_rise_trans(jdUt, SE_SUN, NULL, SEFLG_SWIEPH, rsmi, geoPos, 0, 0, &current.sunset, serr); 

    if(returnCode == ERR)
    { 
        printf("%s\n", serr);
    }

    // Calculate vara (day of week)
    current.vara = (int)(current.sunrise + 1.5) % 7;
    
    // Calculate ayanamsa
    current.ayanamsa = swe_get_ayanamsa_ut(current.sunrise);

    // Calculate Sun's rashi (zodiac sign)
    double x3[6];
    swe_calc_ut(current.sunrise, SE_SUN, iflag, x3, serr);
    current.sunRashi = (int)(x3[0] / 30.0);

    // Calculate Tithi, Nakshatra, and Yoga
    CalcType types[] = { CALC_TITHI, CALC_NAKSHATRA, CALC_YOGA };
    int maxIndices[] = { 30, 27, 27 };

    for(int i = 0; i < 3; ++i)
    { 
        double valueAtSunrise = getArc(current.sunrise, types[i]);

        double start = getBoundry(current.sunrise, types[i], valueAtSunrise);
        double end = getBoundry(current.sunrise, types[i], valueAtSunrise + 1.0);

        if(types[i] == CALC_TITHI)
        { 
            current.tithi[0].tithi = (int)valueAtSunrise;
            current.tithi[0].start = start;
            current.tithi[0].end = end;
        }
        else if(types[i] == CALC_NAKSHATRA)
        { 
            current.nakshatra[0].nakshatra = (int)valueAtSunrise;
            current.nakshatra[0].start = start;
            current.nakshatra[0].end = end;
        }
        else 
        { 
            current.yoga[0].yoga = (int)valueAtSunrise; 
            current.yoga[0].start = start;
            current.yoga[0].end = end;
        }

        // Check if second element occurs before next sunrise
        if(end < nextSunrise)
        { 
            int newIndex = ((int)valueAtSunrise + 1) % maxIndices[i];
            double end2 = getBoundry(end + 0.05, types[i], (double)newIndex + 1.1);
            
            if(types[i] == CALC_TITHI)
            { 
                current.tithi[1].tithi = newIndex;
                current.tithi[1].start = end;
                current.tithi[1].end = end2;
            }
            else if(types[i] == CALC_NAKSHATRA)
            { 
                current.nakshatra[1].nakshatra = newIndex;
                current.nakshatra[1].start = end;
                current.nakshatra[1].end = end2;
            }
            else 
            { 
                current.yoga[1].yoga = newIndex; 
                current.yoga[1].start = end;
                current.yoga[1].end = end2;
            }
        }
        else
        { 
            if(types[i] == CALC_TITHI)
                current.tithi[1].tithi = -1;
            if(types[i] == CALC_NAKSHATRA)
                current.nakshatra[1].nakshatra = -1;
            if(types[i] == CALC_YOGA)
                current.yoga[1].yoga = -1;
        }
    }

    double kAtRise = getArc(current.sunrise, CALC_KARANA);
    current.karana[0].karana = (int)kAtRise;
    current.karana[0].start = getBoundry(current.sunrise, CALC_KARANA, kAtRise);
    current.karana[0].end = getBoundry(current.sunrise, CALC_KARANA, kAtRise + 1.0);

    for(int j = 1; j < 4; ++j)
    { 
        if(current.karana[j - 1].end < nextSunrise)
        { 
            int nextK = (current.karana[j-1].karana + 1) % 60;
            current.karana[j].karana = nextK;
            current.karana[j].start = current.karana[j-1].end;
            current.karana[j].end = getBoundry(current.karana[j].start + 0.02, CALC_KARANA, (double)nextK + 1);
        }
        else 
        { 
            current.karana[j].karana = -1;
        }
    }

    double totalSolarDay = nextSunrise - current.sunrise;
    double muhurataLength = totalSolarDay / 30.0;

    for(int i = 0; i < 30; i++)
    { 
        current.muhurata[i].muhurata = i;
        current.muhurata[i].start = current.sunrise + (i * muhurataLength);
        current.muhurata[i].end = current.sunrise + ((i + 1) * muhurataLength);
    }

    double tithiNow = getArc(current.sunrise, CALC_TITHI);
    
    double jdNM1 = current.sunrise - (tithiNow * 0.984);
    for(int i = 0; i < 10; ++i)
    { 
        double diff = getArc(jdNM1, CALC_TITHI);
        if(diff > 15) diff -= 30;
        jdNM1 -= (diff * 0.984);
    }

    double jdNM2 = jdNM1 + 29.53;
    for(int i = 0; i < 10; ++i)
    { 
        double diff = getArc(jdNM2, CALC_TITHI);
        if(diff > 15) diff -= 30;
        jdNM2 -= (diff * 0.984);
    }

    double xStart[6], xEnd[6];
    swe_calc_ut(jdNM1 + 0.001, SE_SUN, iflag, xStart, serr);
    swe_calc_ut(jdNM2 + 0.001, SE_SUN, iflag, xEnd, serr);

    int rashiStart = (int)(xStart[0] / 30.0);
    int rashiEnd = (int)(xEnd[0] / 30.0);

    int monthBase = (rashiStart + 1) % 12;
    
    if(rashiStart == rashiEnd)
        current.lunarMonth = monthBase + 100; 
    else
        current.lunarMonth = monthBase;

    return current;
}
