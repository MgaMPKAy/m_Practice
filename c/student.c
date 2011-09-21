#include <stdio.h>
#include <stdlib.h>

#define STU_NR 3

struct student {
	int id;
	char name[20];
	int score[3];
};

int main(int argc, char *argv[])
{
	struct student * studs[STU_NR];
	struct student * info;
	int i, j;


	//输入学号、姓名
	printf("%s\n", "Id and name");
	for (i = 0; i < STU_NR; ++i) {
		info = malloc(sizeof(struct student));
		studs[i] = info;
		printf("%s: ", "ID");
		scanf("%d", &info->id);
		printf("%s: ", "Name");
		scanf("%s", info->name);

	}

	// 输入成绩
	printf("%s\n", "Scores");
	for (i = 0; i < STU_NR; ++i) {
		int (*score)[3] = &(studs[i]->score);
		printf("%s: ", "Scores");
		scanf("%d%d%d", *score , *score + 1, *score + 2);
	}

	// 输出
	for (i = 0; i < STU_NR; ++i) {
		printf("ID:%d\t Name:%s\t Scores:",
		       studs[i]->id, studs[i]->name);
		for (j = 0; j < 3; j++) {
			printf("%d ", studs[i]->score[j]);
		}
		printf("\n");
	}

	return 0;
}
