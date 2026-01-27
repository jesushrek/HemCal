#ifndef CALENDAR_H
#define CALENDAR_H

#include <stdlib.h>
#include <time.h>
#include "constants.h"
#include "convertor.h"

Date returnTodayDate()
{ 
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    Date today = {
        .year = tm.tm_year + 1900,
        .month = tm.tm_mon,
        .day = tm.tm_mday,
            };

    return today;
}

char* prepareCalendar(int daysInMonth, int startingDay)
{ 
    char* calendar = calloc(200, sizeof(char));
    if(!calendar) return NULL;

    strcat(calendar, "Su Mo Tu We Th Fr Sa\n");
    for(int i = 0; i < startingDay; ++i)
        strcat(calendar, "   ");

    char buffer[50];
    for(int day = 1; day <= daysInMonth; ++day)
    { 
        sprintf(buffer, "%2d ", day);
        strcat(calendar, buffer);

        if((startingDay + day) % 7 == 0)
        { 
            strcat(calendar, "\n");
        }
    }

    strcat(calendar, "\0");
    return calendar;
}

void printBsMonth(Date bsDate)
{ 
    int index = bsDate.year - bsFirstDate.year;
    int daysInMonth = daysInMonthByYear[index][bsDate.month];
    printf("      %s %d\n", BsMonths[bsDate.month], bsDate.year);
    Date firstDayOfMonth = {
        .year = bsDate.year,
        .month = bsDate.month,
        .day = 1,
    };
    printf("%s\n\n", prepareCalendar(daysInMonth, daysOfWeekBs(firstDayOfMonth)));
}

void printBsYear(Date bsDate)
{ 
    for(int month = 0; month < 12; ++month)
    { 
        Date currentMonth = {
            .year = bsDate.year,
            .month = month,
            .day = 1,
        };
        printBsMonth(currentMonth);
    }
}

void printThisMonthBs()
{ 
    Date bsCurr = adToBs(returnTodayDate());
    printBsMonth(bsCurr);
}

void printCurrentYear() 
{ 
    Date bsCurr = adToBs(returnTodayDate());
    printBsYear(bsCurr);
}

#endif
