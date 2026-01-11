#include "constants.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


const bool isLeapAd(int year)
{
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}


const int daysInMonth(int m, bool isLeap)
{ 
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if( m == 1 && isLeap )
        return 29;

    return days[m];
}

const int countDateOffset()
{ 
    int offsetDays = 0;
    for(int m = 0; m < adFirstDate.month; ++m)
        offsetDays += daysInMonth(m, isLeapAd(adFirstDate.year));

    offsetDays += (adFirstDate.day - 1);
    return offsetDays + 1;
}

const int bsDaysInYear( int year )
{ 
    int indexYear = (year - bsFirstDate.year);
    int days = 0;

    for(int m = 0; m < 12; ++m)
        days += daysInMonthByYear[indexYear][m];

    return days;
}

const long long bsToDay( Date bsDate )
{ 
    long long totalDays = 0;
    for(int y = bsFirstDate.year; y < bsDate.year; ++y)
        totalDays += bsDaysInYear(y);

    const int currentIndex = (bsDate.year - bsFirstDate.year);

    for(int m = 0; m < bsDate.month; ++m)
        totalDays += daysInMonthByYear[currentIndex][m];

    //fix the off by one
    return totalDays + (long long)bsDate.day - 1;
}

const long long adToDay( Date adDate )
{ 
    long long totalDays = 0;
    for(int y = adFirstDate.year; y < adDate.year; ++y)
        totalDays += isLeapAd(y)? 366 : 365;

    for(int m = 0; m < adDate.month; ++m)
        totalDays += daysInMonth(m, isLeapAd(adDate.year));

    totalDays -= countDateOffset();
    return totalDays + (long long)adDate.day;
}

const Date bsToAd( Date bsDate )
{
    Date converted = { -1, -1, -1 };
    long long remainingDays = bsToDay(bsDate);
    if(remainingDays < 0)
        return converted;

    int yearIndex = adFirstDate.year;
    while(true)
    { 
        int daysInYear = 0;
        if( yearIndex == adFirstDate.year)
            daysInYear = (365 - countDateOffset());
        else 
            daysInYear = isLeapAd(yearIndex)? 366 : 365;

        if( remainingDays < daysInYear )
            break;

        remainingDays -= daysInYear;
        ++yearIndex;
    }

    for(int m = 0; m < 12; ++m)
    {
        int daysIn = daysInMonth(m, isLeapAd(yearIndex));
        if( remainingDays < daysIn )
        { 
            converted.year = yearIndex;
            converted.month = m;
            converted.day = remainingDays + 1;
            break;
        }
        remainingDays -= daysIn;
    }

    return converted;
}

const Date adToBs( Date adDate )
{
    Date converted = { -1, -1, -1 };
    int remainingDays = adToDay(adDate);

    int yearIndex = bsFirstDate.year;
    if( remainingDays < 0 )
        return converted;

    while(true)
    {
        int daysInYear = bsDaysInYear(yearIndex);
        if( remainingDays < daysInYear )
            break;

        remainingDays -= daysInYear;
        ++yearIndex;
    }

    for(int m = 0; m < 12; ++m)
    { 
        int daysIn = daysInMonthByYear[yearIndex - bsFirstDate.year][m];
        if( remainingDays < daysIn )
        {
            converted.year = yearIndex;
            converted.month = m;
            //fix another off by one 
            converted.day = remainingDays;
            break;
        }
        remainingDays -= daysIn;
    }
    return converted;
}

const Error isValidDateAd( const Date adDate )
{   
    if( adDate.month > 11 || adDate.month < 0 )
        return notValidMonth;

    if(daysInMonth(adDate.month, isLeapAd(adDate.year)) < adDate.day)
        return notValidDay;

    if( adDate.day <= 0 )
        return notValidDay;


    if( adDate.year > adLastDate.year || adDate.year < adFirstDate.year )
        return outOfBounds;

    if( adDate.year == adFirstDate.year )
    { 
        if( adDate.month < adFirstDate.month )
            return outOfBounds;

        if( adDate.month == adFirstDate.month )
            if(adDate.day < adFirstDate.day)
                return outOfBounds;
    }

    if( adDate.year == adLastDate.year )
    { 
        if( adDate.month > adLastDate.month )
            return outOfBounds;

        if( adDate.month == adLastDate.month )
            if(adDate.day > adLastDate.day)
                return outOfBounds;
    }

    return noError;
}

const Error isValidDateBs( const Date bsDate )
{   
    const int index = (bsDate.year - bsFirstDate.year);

    if( bsDate.month > 11 || bsDate.month < 0 )
        return notValidMonth;

    if(daysInMonthByYear[index][bsDate.month] < bsDate.day)
        return notValidDay;

    if( bsDate.day <= 0 )
        return notValidDay;


    if( bsDate.year > bsLastDate.year || bsDate.year < bsFirstDate.year )
        return outOfBounds;

    if( bsDate.year == bsFirstDate.year )
    { 
        if( bsDate.month < bsFirstDate.month )
            return outOfBounds;

        if( bsDate.month == bsFirstDate.month )
            if(bsDate.day < bsFirstDate.day)
                return outOfBounds;
    }

    if( bsDate.year == bsLastDate.year )
    { 
        if( bsDate.month > bsLastDate.month )
            return outOfBounds;

        if( bsDate.month == bsLastDate.month )
            if(bsDate.day > bsLastDate.day)
                return outOfBounds;
    }

    return noError;
}

const Error validate(Date date, bool isAd)
{ 
    switch((int)isAd)
    { 
        case 1: 
            return isValidDateAd(date);
        case 0:
            return isValidDateBs(date);
        default:
            return noError;
    }
    return noError;
}

//int dayofweek(int y, int m, int d)
int dayOfWeekAd(Date adDate)
{
    int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    if ( adDate.month < 3 )
    {
        adDate.year -= 1;
    }
    return (adDate.year + adDate.year/4 - adDate.year/100 + adDate.year/400 + t[adDate.month] + adDate.day) % 7;
}

int daysOfWeekBs(Date bsDate)
{ 
    int anchorDay = dayOfWeekAd(adFirstDate);
    int total = bsToDay(bsDate);

    return (anchorDay + total) % 7;
}
