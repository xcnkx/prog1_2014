#include <stdio.h>
#include<string.h>
#include "prog01.h"

Record input(void);
void output(Record);


int main(){
  
  Record data;
  data = input();
  output(data);
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
