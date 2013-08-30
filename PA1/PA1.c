/*
 * Ted Meyer
 */

#include<stdio.h>

typedef enum { false, true } bool;

int main(void) {
	// function declarations
	void printMonth(int days, int first);
	bool isLeap(int year);
	int getNextStartDay(int currentStart, int month);
	int year;

	printf("Please enter year for this calendar:- ");
	scanf("%i", &year);
	printf("  ***    CALENDAR for %i    ***\n",year);

	int month = 1;
	bool leap = isLeap(year);
	int daystart = (37 + (year-1) + (year-1)/4 + (year-1)/400 -(year-1)/100) % 7;
	if (daystart == 0){
		daystart = 7;
	}

	while(month <= 12) {

		switch(month) {
			case 1:
				printf("January %i\n\n", year);
				printMonth(31, daystart);
				daystart = getNextStartDay(daystart, 31);
				break;
			case 2:
				printf("February %i\n\n", year);
				printMonth(leap?29:28, daystart);
				daystart = getNextStartDay(daystart, leap?29:28);
				break;
			case 3:
				printf("March %i\n\n", year);
				printMonth(31, daystart);
				daystart = getNextStartDay(daystart, 31);
				break;
			case 4:
				printf("April %i\n\n", year);
				printMonth(30, daystart);
				daystart = getNextStartDay(daystart, 30);
				break;
			case 5:
				printf("May %i\n\n", year);
				printMonth(31, daystart);
				daystart = getNextStartDay(daystart, 31);
				break;
			case 6:
				printf("June %i\n\n", year);
				printMonth(30, daystart);
				daystart = getNextStartDay(daystart, 30);
				break;
			case 7:
				printf("July %i\n\n", year);
				printMonth(31, daystart);
				daystart = getNextStartDay(daystart, 31);
				break;
			case 8:
				printf("August %i\n\n", year);
				printMonth(31, daystart);
				daystart = getNextStartDay(daystart, 31);
				break;
			case 9:
				printf("September %i\n\n", year);
				printMonth(30, daystart);
				daystart = getNextStartDay(daystart, 30);
				break;
			case 10:
				printf("October %i\n\n", year);
				printMonth(31, daystart);
				daystart = getNextStartDay(daystart, 31);
				break;
			case 11:
				printf("November %i\n\n", year);
				printMonth(30, daystart);
				daystart = getNextStartDay(daystart, 30);
				break;
			case 12:
				printf("December %i\n\n", year);
				printMonth(31, daystart);
				daystart = getNextStartDay(daystart, 31);
				break;
		}
		month++;
	}

	return 0;
}

int getNextStartDay(int currentStart, int month){
	int k = (currentStart+month)%7;
	return k==0 ? 7 : k;
}

bool isLeap(int year){
	return ((year%4 == 0) && (year%100 != 0)) || (year%400 == 0);
}


void printMonth(int days, int first)
{	//where first=1 corresponds to monday
	printf("%5s%5s%5s%5s%5s%5s%5s\n", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat");
	int i = 1;

	while( i < first ){
		printf("     ");
		i++;
	}

	i = 1;
	while( i <= days ){
		printf("%5i", i);
		if ((i+first-1)%7==0){
			printf("\n");
		}
		i++;
	}
	printf("\n\n");
}

