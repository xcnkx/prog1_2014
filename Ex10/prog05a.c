#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 20000

typedef struct {
  int data[N];    /* N個の要素を持つ配列 */
  int maxdata;    /* データの最大値         */
  int mindata;    /* データの最小値         */
  double avedata; /* データの平均値         */
} My_Array;

void FindMember1(My_Array *);

main(){

  int i;
  My_Array A,*p=&A;
  
  A.maxdata = 0;
  A.mindata = 0;
  A.avedata = 0;
  
  srand((unsigned int)time(NULL)); 
  
  for(i=0;i<N;i++){
    A.data[i]=rand()%101;
  }
  
  FindMember1(p);
  
  printf("maxdata: %d\nmindata: %d\navedata: %f\n\n",A.maxdata,A.mindata,A.avedata);
  
}  
  
void FindMember1(My_Array *p){
  
  int i;
  
  for(i=0;i<N;i++){
    if(p->maxdata<p->data[i]) p->maxdata = p->data[i];
    if(p->mindata>p->data[i]) p->mindata = p->data[i];
    p->avedata += p->data[i];
  }
  
  p->avedata /= N;
  
  printf("maxdata: %d\nmindata: %d\navedata: %f\n\n",p->maxdata,p->mindata,p->avedata);
  
}
