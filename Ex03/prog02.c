#include<stdio.h>
#include<stdlib.h>
#define MAX 1000


int L2U(int);
int U2L(int);
int U2L_L2U(int);

main(){
  FILE *fpin,*fpout;                     //ファイルポインタの宣言
  char buf[MAX];                      //変数宣言
  int n;

  fpin = fopen("data.in","r");         //ファイル名を指定し、オープン
  if(fpin == NULL){                     //オープン失敗なら真
    printf("read file open error\n");   //エラーメッセージの出力
    exit(1);                            //プログラムの終了 
  }
  
  fpout = fopen("prog02.out","w");         //ファイル名を指定し、オープン
  if(fpout == NULL){                     //オープン失敗なら真
    printf("write file open error\n");   //エラーメッセージの出力
    fclose(fpin);                      //ファイルをクローズ
    exit(2);                            //プログラムの終了
  }
  //upper to lower
  for(n=0;n<MAX;n++){
    buf[n] = fgetc(fpin);
    if(buf[n]==EOF) break;
    fputc(U2L(buf[n]),fpout);
  }
  //lower to upper
  for(n=0;n<MAX;n++){
    if(buf[n]==EOF) break;
    fputc(L2U(buf[n]),fpout);
  }
  //upper to lower & lower to upper
  for(n=0;n<MAX;n++){
    if(buf[n]==EOF) break;
    fputc(U2L_L2U(buf[n]),fpout);
  }
    
    

  fclose(fpout);                   //ファイルをクローズ
  fclose(fpin);                     //ファイルをクローズ
}
// function upper to lower
int U2L(int c){
  if(c>='A' && c<='Z'){
    return c+('a'-'A');
  }
  else return c;
}
//function lower to upper 
int L2U(int c){
  if(c>='a' && c<='z'){
    return c+('A'-'a');
  }
  else return c;
}
//function upper to lower & lower to upper
int U2L_L2U(int c){
  if(c>='A' && c<='Z'){
    return c+('a'-'A');
  }
  else if(c>='a' && c<='z'){
    return c+('A'-'a');
  }
  else return c;
}
