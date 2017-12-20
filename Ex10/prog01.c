#include <stdio.h>

typedef struct{
  int  id;       /* ID       */
  char name[20]; /* 名前     */
  int  score;    /* 点数     */
  char grade;    /* グレード */
} Record;


void PrintData1(Record);
void PrintData2(Record *);

main(){
  
  Record person1={1220006,"Kamiya Cristian",100,'A'},person2={1270007,"James Bond",69,'A'};
  Record *p1,*p2;
  
  p1 = &person1;
  p2 = &person2;

  PrintData1(person1);
  PrintData2(p1);
  
  printf("\n\n");
  
  PrintData1(person2);
  PrintData2(p2);

}

void PrintData1(Record data1)
{
  printf("%d\n",data1.id);
  printf("%s\n",data1.name);
  printf("%d\n",data1.score);
  printf("%c\n",data1.grade);
}

void PrintData2(Record *p)
{
  printf("%d\n",p->id);
  printf("%s\n",p->name);
  printf("%d\n",p->score);
  printf("%c\n",p->grade);
}
