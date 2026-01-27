#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef struct 
{ 
    int year;
    int month;
    int day;
   /* int hour;
    int minute;
    int second; */
} Date;

typedef enum { 
    Prathama,
    Dwitiya,
    Tritiya,
    Chaturthi ,
    Panchami,
    Shashthi,
    Saptami,
    Ashtami,
    Navami,
    Dashami,
    Ekadashi,
    Dwadashi,
    Trayodashi,
    Chaturdashi,
} EnumTithi;

const int Purnima = 14;
const int Amavasya = 29;

typedef enum
{
    January,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December,
    NoMonth,
}EnumMonths;

typedef enum
{
	Longitude,
	Latitude,
	Altitude,
} CoordinateType;

typedef enum
{
    Baishakh,
    Jestha,
    Ashadh,
    Shrawan,
    Bhadra,
    Ashwin,
    Kartik,
    Mangsir,
    Poush,
    Magh,
    Falgun,
    Chaitra,
    NoMonthBs,
}EnumMonthsBs;

typedef enum 
{ 
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    NoDay,
}EnumDays;

typedef enum 
{ 
    Aaitabaar,
    Somabaar,
    Mangalbaar,
    Budhabaar,
    Bihibaar,
    Sukrabaar,
    Sanibaar,
    NoDayBs,
}EnumDaysBs;

typedef enum 
{
    Ashwini, Bharani, Krittika, Rohini, Mrigashira, Ardra, Punarvasu,
    Pushya, Ashlesha, Magha, PurvaPhalguni, UttaraPhalguni, Hasta,
    Chitra, Swati, Vishakha, Anuradha, Jyeshtha, Mula, PurvaAshadha,
    UttaraAshadha, Shravana, Dhanishta, Shatabhisha, PurvaBhadrapada,
    UttaraBhadrapada, Revati
} EnumNakshatra;

typedef enum {
    Bava, Balava, Kaulava, Taitila, Gara, Vanija, Vishti, 
    Shakuni, Chatushpada, Naga, Kintughna             
} EnumKarana;

typedef enum {
    ShuklaPaksha, 
    KrishnaPaksha 
} EnumPaksha;

typedef enum 
{
    Vishkumbha, Priti, Ayushman, Saubhagya, Shobhana, Atiganda, Sukarma,
    Dhriti, Shoola, Ganda, Vriddhi, Dhruva, Vyaghata, Harshana, Vajra,
    Siddhi, Vyatipata, Variyana, Parigha, Shiva, Siddha, Sadhya, Shubha,
    Shukla, Brahma, Indra, Vaidhriti
} EnumYoga;

static const char* PakshaNames[] = { "Shukla", "Krishna" };

static const char* AdMonths[] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

static const char* BsMonths[] = {
    "Baishakh", "Jestha", "Ashadh", "Shrawan", "Bhadra", "Ashwin",
    "Kartik", "Mangsir", "Poush", "Magh", "Falgun", "Chaitra"
};

static const char* AdDays[] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

static const char* BsDays[] = {
    "Aaitabaar", "Somabaar", "Mangalbaar", "Budhabaar", "Bihibaar", "Sukrabaar", "Sanibaar"
};

static const char* TithiNames[] = { 
    "Prathama", "Dwitiya", "Tritiya", "Chaturthi", "Panchami",
    "Shashthi", "Saptami", "Ashtami", "Navami", "Dashami", "Ekadashi", 
    "Dwadashi", "Trayodashi", "Chaturdashi"
};

static const char* NakshatraNames[] = {
    "Ashwini", "Bharani", "Krittika", "Rohini", "Mrigashira", "Ardra", "Punarvasu",
    "Pushya", "Ashlesha", "Magha", "Purva Phalguni", "Uttara Phalguni", "Hasta",
    "Chitra", "Swati", "Vishakha", "Anuradha", "Jyeshtha", "Mula", "Purva Ashadha",
    "Uttara Ashadha", "Shravana", "Dhanishta", "Shatabhisha", "Purva Bhadrapada",
    "Uttara Bhadrapada", "Revati"
};

static const char* YogaNames[] = {
    "Vishkumbha", "Priti", "Ayushman", "Saubhagya", "Shobhana", "Atiganda", "Sukarma",
    "Dhriti", "Shoola", "Ganda", "Vriddhi", "Dhruva", "Vyaghata", "Harshana", "Vajra",
    "Siddhi", "Vyatipata", "Variyana", "Parigha", "Shiva", "Siddha", "Sadhya", "Shubha",
    "Shukla", "Brahma", "Indra", "Vaidhriti"
};

static const char* KaranaNames[] = {
    "Bava", "Balava", "Kaulava", "Taitila", "Gara", "Vanija", "Vishti",
    "Shakuni", "Chatushpada", "Naga", "Kintughna"
};

static const char* TithiPurnima = "Purnima";
static const char* TithiAmavasya = "Amavasya";

typedef enum
{
    notValidMonth = 0,
    outOfBounds,
    notValidYear,
    notValidDay,
    noError,
}Error;

Date adFirstDate = { 1918, April, 13 };
Date adLastDate  = { 2044, April, 12 };

Date bsFirstDate = { 1975, Baishakh, 1 };
Date bsLastDate = { 2100, Chaitra, 30 };

const int dateOffset = 103;

int daysInMonthByYear[][12] = {
    {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {30, 32, 31, 32, 31, 30, 30, 30, 30, 29, 29, 31},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 29, 31},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {31, 31, 31, 32, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {31, 31, 31, 32, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 31, 32, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {30, 32, 31, 32, 31, 31, 29, 30, 30, 29, 29, 31},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {31, 31, 31, 32, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {31, 31, 31, 32, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 31, 32, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {31, 31, 31, 32, 31, 31, 29, 30, 29, 30, 29, 31},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 29, 31},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
    {31, 31, 31, 32, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {31, 31, 31, 32, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {31, 31, 32, 31, 31, 30, 30, 30, 29, 30, 30, 30},
    {31, 31, 32, 31, 31, 30, 30, 30, 29, 30, 30, 30},
    {31, 32, 31, 32, 30, 31, 30, 30, 29, 30, 30, 30},
    {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 30, 30},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 30, 30, 30},
    {30, 31, 32, 32, 30, 31, 30, 30, 29, 30, 30, 30},
    {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 30, 30},
    {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 30, 30},
    {31, 31, 32, 31, 31, 31, 30, 30, 29, 30, 30, 30},
    {30, 31, 32, 32, 31, 30, 30, 30, 29, 30, 30, 30},
    {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 30, 30},
    {31, 31, 32, 31, 31, 30, 30, 30, 29, 30, 30, 30},
    {31, 31, 32, 31, 31, 31, 30, 29, 30, 30, 30, 30},
    {30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 30, 30},
    {31, 31, 32, 31, 31, 31, 29, 30, 29, 30, 29, 31},
    {31, 31, 32, 31, 31, 31, 30, 29, 29, 30, 30, 30},
    {31, 32, 31, 32, 30, 31, 30, 29, 30, 29, 30, 30},
};
#endif
