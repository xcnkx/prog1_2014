#include <stdio.h>

char grade_char(int);
int grade_point(int);

main()
{
  int status,score,credit,sum_score=0,sum_credit=0;
  while(1){
    printf("点数と単位数を入力してください。：");
    status = scanf("%d%d",&score,&credit);
    if(status == -1){
      printf("評価平均点（GPA）: %g, 単位数: %d\n",(double)sum_score/sum_credit,sum_credit);
      break;
    }
    else {
      printf("%d 点の評価は %c で、評価は %d です。(%d 単位)\n",score,grade_char(score),grade_point(score),credit);
      sum_score += (grade_point(score)*credit);
      sum_credit += credit;
    } 
  }
}

char grade_char(int score)
{
  if(score>=0 && score<35) return 'F';
  else if(score>=35 && score<50) return 'D';
  else if(score>=50 && score<65) return 'C';
  else if(score>=65 && score<80) return 'B';
  else if(score>=80 && score<=100) return 'A';
}

int grade_point(int score)
{
  if(score>=0 && score<35) return 0;
  else if(score>=35 && score<50) return 1;
  else if(score>=50 && score<65) return 2;
  else if(score>=65 && score<80) return 3;
  else if(score>=80 && score<=100) return 4;
}
