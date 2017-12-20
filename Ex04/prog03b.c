#include <stdio.h>
/*文字列操作に必要なヘッダファイルをインクルードする*/
#include <string.h>

main()
{
  /*比較する単語２つを文字列配列に格納する*/
  char a[]="university";
  char b[]="aizu";
  int count=0;
  char buf[100];   /* 単語読み取り用の文字配列 */

  /* 文字列の読み取りと置き換え        */
  /* 読取に成功している間は処理を続ける */
  while (scanf("%s",buf)==1){
    /*置き換え対象の文字と入力を比較し、
      一致したら先頭の文字を置き換える*/
    if (strcmp(a,buf)==0||strcmp(b,buf)==0){
      buf[0]+=(-32);
    }
    printf( "%s ", buf );   /* 単語の間にスペースをひとつ入れて出力 */
  }
  printf("\n");
}
