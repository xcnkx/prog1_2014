#include <stdio.h>
#define TRUE 1
#define FALSE 0

int isUpper(char);
int isLower(char);

main(){
  char c;
  int i,status,count=0;
  
  printf("文字を入力してください：");
  while(1){
    status = scanf("%c",&c);  
    if(status!=1 || c=='\n') break;
    if(isUpper(c)==TRUE){
      printf("文字 %c の ascii code は %d(0x%x)で,アルファベット大文字ではありません\n",c,c,c);
    }
    else if(isLower(c)==TRUE){
      printf("文字 %c の ascii code は %d(0x%x)で,アルファベット小文字です\n",c,c,c);
    }
    else printf("文字 %c の ascii code は %d(0x%x)で,アルファベットではありません\n",c,c,c);
  }
}

int isUpper(char c){
  if(c>='A' && c<='Z') return TRUE;
  else return FALSE;
}
int isLower(char c){
  if(c>='a' && c<='z') return TRUE;
  else return FALSE;
}


