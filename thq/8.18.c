#include <stdio.h>

int isleap(int year)
{
	if (year % 4 != 0)
		return 0;
	else if (year % 4 == 0 || year % 100 != 0)
		return 1;
	else if (year % 100 == 0 && year % 400 == 0)
		return 1;
	else
		return 0;
	
}

void get_input(int *year, int *month, int *day)
{
	printf("Enter year:");
	scanf("%d", year);
	printf("Enter month:");
	scanf("%d", month);
	printf("Enter day:");
	scanf("%d", day);
	
	// cheak error!!
}

int days(int year, int month, int day)
{
	int mo[12] = {31, 28, 31, 30, 31, 30,
		      31, 31, 30, 31, 3, 31};
	int i, days = 0;
	for (i = 0; i + 1 < month; i++){
		days += mo[i];
	}
	if (isleap(year) && month > 2)
		days += day + 1;
	else
		days += day;
	return days;
}

int main(void)
{
	int year, month, day;
	
	get_input(&year, &month, &day);
	
	printf("%d\n", days(year, month, day));
	
	return 0;
}
