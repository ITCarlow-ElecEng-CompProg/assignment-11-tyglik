/** Lab 11 - Date Calculator
 *
 * Martina Nunvarova
 * 6/11/2017
 */

/**
Every year that is exactly divisible by four is a leap year, except for years that are exactly divisible by 100,
but these centurial years are leap years if they are exactly divisible by 400.
For example, the years 1700, 1800, and 1900 are not leap years, but the year 2000 is.
*/

#include <iostream>
#include <stdio.h>

using namespace std;

const char monthDays[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};           ///Define the standard days in a month ([0] = 0, to have monthDays[month] behaviour)

struct struDate {                                                           ///defined structure struDate - Global
    unsigned int y;
    unsigned short int m,d;
};

///integer input value:
///     prompt - the text to be displayed
///     zeroOptions - 0=no option, only positive value; 1=Zero and positive; 2=Any real number
int getIntValue(string prompt, int zeroOptions)
{
    int output;
    char outOK;

    do {
        outOK=1;
        cout << prompt;
        fflush(stdout);
        fflush(stdin);
        cin>>output;
        if (output<0) {
            if (zeroOptions<2)
                outOK=0;
        } else if (output==0) {
            if (zeroOptions<1)
                outOK=0;
        }
        if (!outOK)
            cout << "Illegal input. ";
    } while (!outOK);
    return output;
}

/// get a Year number
void getYear(struDate *dt)
{
    loop:                                                                       ///Using labels, to loop
        (*dt).y = getIntValue("Please enter the Year (1200 - 2500): ",0);       /// limiting the year 1200-2500
    if (((*dt).y<1200)||((*dt).y>2500)) {                                       /// single if statement will output and loop
        cout << "Illegal input. ";
        goto loop;
    }
}

///get a month number   (same as above)
void getMonth(struDate *dt)
{
    loop:
        dt->m = getIntValue("Please enter the month (1 - 12): ",0);
    if (dt->m>12) {
        cout << "Illegal input. ";
        goto loop;
    }
}

/**
Every year that is exactly divisible by four is a leap year, except for years that are exactly divisible by 100,
but these centurial years are leap years if they are exactly divisible by 400.
For example, the years 1700, 1800, and 1900 are not leap years, but the year 2000 is.
*/

///get the amount of days in a Month and Year combination
unsigned short int getMonthDays(struDate dt)
{
    unsigned short int days,leap;

    days=monthDays[dt.m];                              /// the days in the month
    if (dt.m==2) {                                     /// but in February, look for a leap year:
        leap=0;                                        /// default, no leap
        if (! (dt.y % 400))                            /// if divisible by 400
            leap=1;
        else if (!(dt.y % 100))                        /// if divisible by 100
            leap=0;
        else if (!(dt.y %4))                           /// if divisible by 4
            leap=1;
        days+=leap;
    }
    return days;
}

///get a day from user
void getDay(struDate *dt)
{
    char c[100];
    short unsigned int days;

    days=getMonthDays(*dt);
    sprintf(c,"Please enter the day in %i/%i (1 - %i): ",dt->m,dt->y,days);
    loop:
        dt->d = getIntValue(c,0);
    if (dt->d>days) {
        cout << "Illegal input. ";
        goto loop;
    }
}

void addDay(struDate today, struDate *tomorrow)
{
    unsigned short int mdays;

    mdays=getMonthDays(today);

    tomorrow->y=today.y;
    tomorrow->m=today.m;
    tomorrow->d=today.d+1; ///add a day

    if (tomorrow->d > mdays) {
        tomorrow->m+=1;     ///add a month and set the 1st day
        tomorrow->d=1;
        if (tomorrow->m > 12) {
            tomorrow->m = 1;
            tomorrow->y += 1;
        }
    }
}

///Main Function
int main()
{
    struDate today, tomorrow; /// int day1, day2
    char input[10];

    cout <<"Date calculator"<<endl<<endl<<"What day is today?"<<endl<<endl;
    getYear(&today);
    getMonth(&today);
    getDay(&today);

    addDay(today,&tomorrow);

    cout <<endl<<endl<<"Tomorrow will be the "<<tomorrow.d<<"/"<<tomorrow.m<<"/"<<tomorrow.y<<endl<<endl<<endl<<"Enter anything (i.e. 'q') to quit: ";
    cin >>input;

    return 0;                                                               ///exit to OS no errors
}
