#include <stdio.h>
#define N 10

int func(int);

main()
{
  int n,r;

  while(1) {
    printf("数値を入力して下さい（正：格納、負：取出）-> ");
    if (scanf("%d",&n)==EOF) break;
    r=func(n);/* スタックに格納または取出*/
    func(0); /* スタックを表示 */
    if (r!=0) printf("取り出したデータ: %d\n",r); /* 取得データの表示 */
  }
  printf("\n");
}

/* 引数：：正の整数：スタックに格納、負の整数：スタックから取出
　　０：スタックの中身を表示　
戻り値：スタックから取り出した値、それ以外は０を返す*/
int func(int x)
{
  static int stack[N]; /* スタック本体 */
  static int num=0;  /* データ数 */
  int i;

  if(x>0){
    stack[num++]=x;
    return 0;
  }
  else if(x<0){
    return stack[--num];
  }
  else {
    printf("num=%d [",num);
    for (i=0;i<num;i++) printf("%d ",stack[i]);
    printf("]\n");
    
    return 0;
  }
    

}
