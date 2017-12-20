#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

/* マクロ定義 */
#define N     256
#define RD    64
#define BLACK '1'
#define WHITE '0'

/* 構造体宣言 */
typedef struct{
  int    x;
  int    y;
} XYdata;

/* 関数のプロトタイプ宣言 */
void init(void);
void rev(XYdata);
void circle(XYdata);
void imgout(void);

/* 外部変数の定義 */
char data[N][N];

int main(int argc, char *argv[])
{
  XYdata cent ;
  int ncent,i;

  /* コマンドラインから円の中心座標を何組か入力される */

  /* 入力された中心座標が何組あるか計算 */
  ncent = (argc-1)/2;
      
  /* 画像初期化関数(すべて白くする)を呼ぶ */
  init();

  //imgout();  
  /* 座標の組の数だけ繰返し… */
  for(i=0;i<ncent;i++){
    /* 円の内部を白黒反転する */
    cent.x = atoi( argv[i*2+2]);
    cent.y = atoi(argv[i*2+1]);
    circle( cent );
  }
  /* 表示 */     
  imgout();
}

/* すべての点を白に初期化する関数 */
void init(void)
{
  int i,j;
  
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      data[i][j] = WHITE;
    }
  }
  
}

/* 引数で指示された座標の点一つを白黒反転する関数 */
void rev(XYdata a)
{
  if(data[a.y][a.x] == BLACK){
    data[a.y][a.x] = WHITE;
  }
  else data[a.y][a.x] = BLACK;
}

/* 引数で指示された座標を中心に,半径 RD 以内の点を白黒反転する関数 */
void circle(XYdata c)
{
  int i,j;
  XYdata p;

  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      if(pow((double)j - (double)c.x, 2) + pow((double)i - (double)c.y,2) <= pow((double)RD,2)){
	p.x = j;
	p.y = i;
	rev(p);
      }
    }
  }
}

/* Plain PBM形式で画像データを出力する関数 */
void imgout(void)
{
  int i,j;

  printf("P1\n");
  printf("%d %d\n",N,N);
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%c ",data[j][i]);
    }
    printf("\n");
  }
}
