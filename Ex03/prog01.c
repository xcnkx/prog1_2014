#include<stdio.h>
#include<stdlib.h>

main(){
  FILE *fpin,*fpout;                     //ファイルポインタの宣言
  char c;                                //変数宣言

  fpin = fopen("read.dat","r");         //ファイル名を指定し、オープン
  if(fpin == NULL){                     //オープン失敗なら真
    printf("read file open error\n");   //エラーメッセージの出力
    exit(1);                            //プログラムの終了 
  }
  
  fpout = fopen("out.dat"."w");         //ファイル名を指定し、書き込む
  if(fpout == NULL){                     //オープン失敗なら真
    printf("write file open error\n");   //エラーメッセージの出力
    fclose(fpin);                      //ファイルをクローズ
    exit(2);                            //プログラムの終了
  }

  while(fscanf(fpin,"%c",&c)!=EOF){      //EOFでなかったら真
    fprintf(fpout,"%c",c);              //ファイルの出力
  }
  fclose(fpout);                   //ファイルをクローズ
  fclose(fpin);                     //ファイルをクローズ
}
