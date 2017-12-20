#include <stdio.h>
#include <math.h>
double myexp(int,int);
double divx(int,int);

main(){
  int x;
  int y;

  printf("exp(x): x= ");
  scanf("%d", &x);
  printf("accuracy: ");
  scanf("%d", &y);

  myexp(x,y);
  printf("exp(%d) = %f\n",x, exp(x));
}

double myexp(int x, int y){
  
  double e;

  if(y == 0) e = divx(x,y);
  else  e = divx(x,y) + myexp(x,y-1);
  /* このprintfの上下にコードを補い、関数を完成させる */
  printf("%d of depth on exp(%d) = %f\n", y, x, e );

  return e;
}

double divx(int x ,int y){
  /* 関数を完成させよ */
  if(y<=1) return x;
  else return  x / y * divx(x,y-1);
}
