#include <stdio.h>
#include<string.h>
#include "prog01.h"
#define MAX 2
#define DAY 1
#define MONTH 4
#define YEAR 2014

int getage(Record);
Record input(void);
void output(Record);


int main(){

  int i;
  Record data[MAX];

  printf("--------データ入力--------\n");
  for(i=0;i<MAX;i++){
    printf("%d人目の",i+1);
    data[i] = input();
    printf("\n");
  }
  
  printf("--------データ出力--------\n");
  printf("年齢基準日：%d年%d月%d日\n",YEAR,MONTH,DAY);
  for(i=0;i<MAX;i++){
    printf("%d人目のデータ\n",i+1);
    output(data[i]);
    printf("年齢：%d\n\n",getage(data[i]));
  }
}

Record input(void){
  
  Record data;
 
  printf("データを入力して下さい\n");
  printf("名前(姓)          -> ");
  scanf("%s",&data.name);
  printf("生まれた年(西暦)  -> ");
  scanf("%d",&data.birthday[0]);
  printf("生まれた月        -> ");
  scanf("%d",&data.birthday[1]);
  printf("生まれた日        -> ");
  scanf("%d",&data.birthday[2]);
  printf("性別(0:男性,1:女性) -> ");
  scanf("%d",&data.gender);
  
  return data;

  
}

void output(Record data){
  
  char gender[10];
  
  if(data.gender == 0) strcpy(gender,"男性\0");
  else strcpy(gender,"女性\0");
  
  printf("名前(姓): %s\n生年月日: %d年 %d月 %d日 (%s)\n",data.name,data.birthday[0],data.birthday[1],data.birthday[2],gender);
}


int getage(Record data){
  
  if(data.birthday[1] >= MONTH){
    if(data.birthday[2] > DAY || data.birthday[2] == DAY){
      return YEAR - data.birthday[0]-1;
    }
    else return YEAR - data.birthday[0];
    
  }
  else return YEAR - data.birthday[0];
  
}
