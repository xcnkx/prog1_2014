#include <stdio.h>
#include <stdlib.h>

#define BLACK '1'
#define WHITE '0'

char **input_data(int *, int *);
void output_data(char**, int, int);
char **flipud_new(char**, int, int);
char **allocarr2d(int, int);
void freearray(char **, int);

main()
{
  char **img_data;
  int  x_size, y_size;

  /* データ読み込み  */
  img_data = input_data(&x_size, &y_size);

  /* 上下反転 */
  img_data = flipud_new(img_data, x_size, y_size);
  output_data(img_data, x_size, y_size);

  /* データ領域解放 */
  freearray(img_data, y_size);
}

char **input_data(int *x_sizep, int *y_sizep){

  int i,j, x_size, y_size;
  char **data;
  
  if (getchar() != 'P' || getchar() != '1'){
    fprintf(stderr, "データの形式が違います\n");
    exit(1);
  }
  
  scanf("%d", &x_size);
  scanf("%d", &y_size);
  
  data = allocarr2d(x_size,y_size);

   for (i = 0; i < y_size; i++){
    for (j = 0; j < x_size; j++){
      /* scanf入力データがおかしいかＥＯＦになった場合             */
      /* この際、" %c"とすることで空白、改行、タブなどは読み飛ばす */
      if(scanf(" %c", &data[i][j]) != 1){
	exit(3);
      }
      /* データが０／１じゃない場合 */
      if(data[i][j] != WHITE && data[i][j] != BLACK){
	fprintf(stderr, "データが異常でした\n");
	exit(4);
      }
    }
  }
   *x_sizep = x_size;
   *y_sizep = y_size;
  
   return data;
}
  
char **allocarr2d(int x_size,int y_size){
  
  char **data;
  int i;

  data = (char **)malloc(y_size* sizeof(char *));
  for(i=0;i<y_size;i++){
    data[i] = (char*)malloc(x_size*sizeof(char));
  }  
  return data;
}
 
void freearray(char **data, int y_size){
  
  int i;
  
  for(i=0;i<y_size;i++){
    free(data[i]);
  }
  free(data);
}

void output_data(char **data, int x_size, int y_size){ /* データ出力 */

  int i, j;

  /* 最初にP1とx,yの画素数を出力 */
  printf("P1\n");
  printf("%d %d\n", x_size, y_size);

  /* 実際のデータ出力 */
  for (i = 0; i < y_size; i++){
    for (j = 0; j < x_size; j++){
      printf("%c", data[i][j]);
    }
    printf("\n");
  }
}

char **flipud_new(char **data, int x_size, int y_size){
  
  int i,j,y2;
  char **n_data;
  
  
  n_data = allocarr2d(x_size,y_size);
  
  for(i=0; i< x_size; i++){
    for (j=0;j<y_size;j++){
      n_data[j][i] = data[y_size - j -1][i];
    }
  }

  freearray(data,y_size);

  return n_data;
}
  
