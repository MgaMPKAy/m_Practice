#include <stdio.h>

void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int day_per_month[]= {31, 28, 31, 30, 31, 30,
			    31, 31, 30, 31, 30, 31};
	int month, day;
	
	if ((year % 100 == 0 && year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
		day_per_month[1] = 29;
	
	for (month = 0, day = 0; day < yearday; month++) {
		day += day_per_month[month];
	}
	*pmonth = month;

	*pday = yearday - day + day_per_month[month - 1];
}

int main(void)
{
	int year, month, day, yearday;

	printf("Year: ");
	scanf("%d", &year);
	printf("N: ");
	scanf("%d", &yearday);

	month_day(year, yearday, &month, &day);

	printf("%d-%d-%d\n", year, month, day);

	return 0;
}
