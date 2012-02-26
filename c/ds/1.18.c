typedef enum {female,male} Sex;
typedef struct{
  char *sport;     // 项目名称
  Sex  gender;     // 性别（女：female；男：male）
  char schoolname; // 校名为'A','B','C','D'或'E'
  char *result;    // 成绩
  int score;       // 得分（7,5,4,3,2或1）
} ResultType;

typedef struct{
  int malescore;   // 男子总分
  int femalescore; // 女子总分
  int totalscore;  // 男女团体总分
} ScoreType;

void Scores(ResultType *result, ScoreType *score)
{
	ResultType *iter;
	int i;
	for (i = 0; (iter = result + i) && (iter->score != 0); i++) {
		switch (iter->gender) {
		case male: score->malescore += iter->score;
		case female: score->femalescore += iter->score;
		}
	}
	score->totalscore = score->femalescore + score->malescore;
}
