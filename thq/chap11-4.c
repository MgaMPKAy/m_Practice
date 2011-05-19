#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct date {
	int year, month, day;
};

struct student{
	char name[20];
	char sex;
	struct date birth;
};

int compare(struct date x, struct date y)
{
	if (x.year == y.year) {
		if (x.month == y.month) {
			return x.day < y.day;
		} else {
			return x.month < y.month;
		}
	} else {
		return x.year < y.year;
	}
}

int main(void)
{
	int i, c, stud;
	struct student studs[4];
	for (i = 0; i < 4; i++) {
		printf("Name: ");
		scanf("%s", studs[i].name);
		printf("Sex: ");
		while((c = getchar()) != '\n' && c != EOF);
		scanf("%c", &(studs[i].sex));
		printf("Year: ");
		scanf("%d",&(studs[i].birth.year));
		printf("Month: ");
		scanf("%d", &(studs[i].birth.month));
		printf("Day: ");
		scanf("%d", &(studs[i].birth.day));
		printf("-----------------\n");
	}

	for(stud = 0, i = 0; i < 4; i++) {
		if (compare(studs[i].birth, studs[stud].birth)) {
			stud = i;
		}
	}
	printf("%s\n", studs[stud].name);
	return 0;
}		
