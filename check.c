#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "swephexp.h"
#include "constants.h"
#include "panchanga.c"

Panchanga returnPanchanga(Date date);

void getFestivalsForYear(int year) {
    Date current = {year, 1, 1};
    bool dashainFound = false;
    bool tiharFound = false;

    printf("Calculating Festivals for Year: %d AD\n", year);
    printf("====================================\n");

    // Scan the whole year (365 days)
    for (int i = 0; i < 365; i++) {
        Panchanga p = returnPanchanga(current);

        // 1. Dashain: Ashwin (6) Shukla Dashami (Index 9)
        if (!dashainFound && p.bsDate.month == 6 && p.tithi[0].tithi == 9) {
            printf("Dashain (Vijaya Dashami): %d-%02d-%02d | BS: %d/%d/%d\n",
                    current.year, current.month, current.day,
                    p.bsDate.year, p.bsDate.month, p.bsDate.day);
            dashainFound = true;
        }

        // 2. Tihar: Kartik (7) Amavasya (Index 14)
        if (!tiharFound && p.bsDate.month == 7 && p.tithi[0].tithi == 14) {
            printf("Tihar (Laxmi Puja)    : %d-%02d-%02d | BS: %d/%d/%d\n",
                    current.year, current.month, current.day,
                    p.bsDate.year, p.bsDate.month, p.bsDate.day);
            tiharFound = true;
        }

        if (dashainFound && tiharFound && current.month > 11) break;

        // Advance to next day using Swiss Ephem utility
        double jd = swe_julday(current.year, current.month, current.day, 12, SE_GREG_CAL);
        jd += 1.0;
        int y, m, d;
        double h;
        swe_revjul(jd, SE_GREG_CAL, &y, &m, &d, &h);
        current.year = y;
        current.month = m;
        current.day = d;
    }
}

int main() {
    swe_set_ephe_path(NULL);

    int targetYear = 2025;
    getFestivalsForYear(targetYear);

    swe_close();
    return 0;
}
