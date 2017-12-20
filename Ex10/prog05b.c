#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 20000
#define LOOP 20000

typedef struct {
  int data[N];    /* N個の要素を持つ配列 */
  int maxdata;    /* データの最大値         */
  int mindata;    /* データの最小値         */
  double avedata; /* データの平均値         */
} My_Array;

void FindMember1(My_Array *);
My_Array FindMember2(My_Array);

main(){

  int i;
  My_Array A,B,*p=&A;
  time_t start,end;
  double keika1,keika2;
  //reset A 
  A.maxdata = 0;
  A.mindata = 0;
  A.avedata = 0;
  // copy A to B
  B=A;
  //rand by time
  srand((unsigned int)time(NULL)); 
  
  for(i=0;i<N;i++){
    A.data[i]=rand()%101;
  }
  
  start = clock();
  for(i=0;i<LOOP;i++){
    FindMember1(p);
  }
  end = clock();
  keika1 = (end-start)/(double)CLOCKS_PER_SEC;
  
  start = clock();
  for(i=0;i<LOOP;i++){
    B = FindMember2(B);
  }
  end = clock();
  keika2 = (end-start)/(double)CLOCKS_PER_SEC; 
  
  printf("Call by value : %f sec\n",keika2);
  printf("Call by address :%f sec\n",keika1);
}  
  
void FindMember1(My_Array *p){
  
  int i;
  
  for(i=0;i<N;i++){
    if(p->maxdata<p->data[i]) p->maxdata = p->data[i];
    if(p->mindata>p->data[i]) p->mindata = p->data[i];
    p->avedata += p->data[i];
  }
  
  p->avedata /= N;
    
}

My_Array FindMember2(My_Array B){
  
  int i;
  
  for(i=0;i<N;i++){
    if(B.maxdata<B.data[i]) B.maxdata = B.data[i];
    if(B.mindata>B.data[i]) B.mindata = B.data[i];
    B.avedata += B.data[i];
  }
  
  B.avedata /= N;
  
  return B;
}
  
  
  
