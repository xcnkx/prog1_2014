#include <stdio.h>

/* マクロ定義 */
#define N 100
#define BLACK '1'
#define WHITE '0'

/* 外部変数の定義 */
char data[N][N];

/* 関数のプロトタイプ宣言 */
void init(void);
void draw(int, int);
void imgout(void);

main() {
  int i,j;

  init();

  /* 
   * 画像の左下半分を黒く塗りつぶす（ここを作成、draw関数を使うこと）
   */
  
  for(i=0;i<N;i++){
    for(j=0;j<i;j++){
      draw(i,j);
    }
  }

  imgout();
}

/* (0,0)～(N-1,N-1) すべての点を白くする  */
void init(void)
{
  /* 
   * ここを作成
   */
  int i,j;
  
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      data[i][j]=WHITE;
    }
  }
}

/* 引数で指示された座標を黒くする */
void draw(int x, int y)
{
  /* 
   * ここを作成
   */
      data[x][y]=BLACK;
    
  
}

/* Plain PBM形式で画像データを出力する */
void imgout(void)
{
  int i, j;

  /* PBM形式のためのおまじない */
  printf("P1\n");
  printf("%d %d\n", N, N);

  /* 
   * データ出力（ここを作成）
   */
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%c",data[i][j]);
    }
  }
}
