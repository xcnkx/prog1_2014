#include <stdio.h>
#define N 10

int push(int);
int pop(void);
void disp_stack(void);

int stack[N];
int num=0;

main()
{
  int n,r;

  while(1) {
    printf("数値を入力して下さい（正：格納、負：取出）-> ");
    if (scanf("%d",&n)==EOF) break;

    if(n>0){
      r=push(n);
    }
    else if(n<0){
      r=pop();      
    }
    else r=0;
    disp_stack();
    if(r>0) printf("取り出したデータ: %d\n",r);
    else if(r<0) printf("取り出す値がありません、または配列のサイズを越えました。\n");
  }
  printf("\n");
}

int push(int x){
  
  if(num<N){
    stack[num++]=x;
    return 0;
  }
  else return -1;

}

int pop(void){

  if(num !=0) return stack[--num];
  else return -1;

}

void disp_stack(void){
  
  int i;
  
  printf("num=%d [",num);
  for (i=0;i<num;i++) printf("%d ",stack[i]);
  printf("]\n");
  
}
    
