#include <stdio.h>
#include<string.h>
#include "prog01.h"
#define MAX 20
#define DAY 1
#define MONTH 4
#define YEAR 2014

int getage(Record);
Record input(void);
void output(Record);


int main(){

  int i,j;
  Record data[MAX];

  for(i=0;i<MAX;i++){
    data[i] = input();
    if(data[i].gender == EOF) break;
  }
  
  printf("--------データ出力--------\n");
  printf("年齢基準日：%d年%d月%d日\n",YEAR,MONTH,DAY);
  for(j=0;j<i;j++){
    printf("%2d人目:",j+1);
    output(data[j]);
  }
}

Record input(void){
  
  Record data;
 
  
  if(scanf("%s",&data.name) != EOF){
    
    scanf("%d",&data.birthday[0]);
    
    scanf("%d",&data.birthday[1]);
    
    scanf("%d",&data.birthday[2]);
    
    scanf("%d",&data.gender);
  
    return data;
  }
  
  else{
    data.gender = -1;
 
    
    return data;
  }
}

void output(Record data){
  
  char gender[10];
  int age;
  
  if(data.gender == 0) strcpy(gender,"男性\0");
  else strcpy(gender,"女性\0");
  
  printf("名前(姓): %-20s生年月日: %d年 %2d月 %2d日生\t年齢: %2d\t%s\n",data.name,data.birthday[0],data.birthday[1],data.birthday[2],getage(data),gender);
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
