#include <stdio.h>
#include <math.h>
#define MAX_ST_NUM 20                   /* 学生数の最大値 */
#define MAX_SCORE 110			/* 110点満点 */
int student_id[MAX_ST_NUM];             /* 学籍番号  */
int abs_score[MAX_ST_NUM];              /* 点数 (補正前) */
char abs_grade[MAX_ST_NUM];             /* 補正前の評価 (A - F) */
int rel_score[MAX_ST_NUM];              /* 点数 (補正後) */
char rel_grade[MAX_ST_NUM];             /* 補正後の評価 (A - F) */
int grade_dist[2][5];                   /* 評価の分布 [0]:補正前, [1] 補正後 */
                                        /* 例 grade_dist[0][0] 補正前の Fの人数 */
char cgrade[5]={'F','D','C','B','A'};   /* 評価文字（評価点数と対応している） */
int num_student=0;                        /* 実際に成績を読み込んだ学生の数 */
double abs_ave=0.0;                     /* 平均点（補正前） */
double rel_ave=0.0;                     /* 平均点（補正後） */

int calib(int);
void adjust_score(void);
void printf_grade(void);
void printf_stat(void);
char grade_char(int);


int main(void){
  int i,j,status;
 
  for(i=0;i<MAX_ST_NUM;i++){
    status = scanf("%d%d",&student_id[i],&abs_score[i]);
    if(status == EOF) break;
    num_student++;
  }
  
  for(i=0;i<num_student;i++) rel_score[i] = calib(abs_score[i]);
  
  adjust_score();  /* 平均点を求め補正後の点数を配列に書きこむ。*/
  		   /* また、補正前後の各々の点数に対して評価を決定し、
		      その分布の処理も行う。*/
  printf_grade();   /* 補正前と後の点数と評価を表示。実行例参照 */
  printf_stat();    /* 統計と評価分布を表示。フォーマットは実行例参照 */
 
}

int calib(score)
{
  double r_score;

  r_score = ((double)100/MAX_SCORE)*score+0.5;
  if(r_score>100) return 100;
  else return r_score;
}
  

void adjust_score(void)
{
  int i,j,abs_sum_score=0,rel_sum_score=0;
  
  for(i=0;i<2;i++){           /*grade_dist 初期化*/  
    for(j=0;j<5;j++){
      grade_dist[i][j] = 0;
    }
  }

  for(i=0;i<num_student;i++){
    abs_sum_score += abs_score[i];                         
    abs_grade[i] = grade_char(abs_score[i]);
    rel_sum_score += rel_score[i];
    rel_grade[i] = grade_char(rel_score[i]);
    for(j=0;j<5;j++){
      if(abs_grade[i] == cgrade[j]) grade_dist[0][j]++;
      if(rel_grade[i] == cgrade[j]) grade_dist[1][j]++;
    }
   
  }
  abs_ave = (double)abs_sum_score/num_student;
  rel_ave = (double)rel_sum_score/num_student;
  
}

void printf_grade(void)
{
  int i,j;

  printf("ID\t点数\t評価\t点数\t評価\n");
  printf("\t（補正前）\t（補正後）\n");
  printf("---------------------------------\n");
  
  for(i=0;i<num_student;i++){
    printf("%d\t%d\t%c\t%d\t%c\n",student_id[i],abs_score[i],abs_grade[i],rel_score[i],rel_grade[i]);
  }
  
  printf("---------------------------------\n");

}

void printf_stat(void)
{
  int i;

  printf("統計\n");
  printf("学生数 %d人 補正前平均点 %.1f点 補正後平均点 %.1f点\n",num_student,abs_ave,rel_ave);
  printf("評価分布\n");
  printf("補正前 ");
  for(i=0;i<5;i++){
    printf("%c %d ",cgrade[4-i],grade_dist[0][4-i]);
  }
  printf("\n");
  printf("補正後 ");
   for(i=0;i<5;i++){
    printf("%c %d ",cgrade[4-i],grade_dist[1][4-i]);
  }
  printf("\n");

}

char grade_char(int score)
{
  if(score>=0 && score<35) return 'F';
  else if(score>=35 && score<50) return 'D';
  else if(score>=50 && score<65) return 'C';
  else if(score>=65 && score<80) return 'B';
  else if(score>=80 && score<=MAX_SCORE) return 'A';
  else return -1;
}
