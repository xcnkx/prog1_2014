#include <stdio.h>
#define TRUE 1
#define FALSE 0

int isUpper(char);

main(){
  char c;
  int i,status,count=0;
  
  printf("文字を入力してください：");
  while(1){
    status = scanf("%c",&c);  
    if(status!=1 || c=='\n') break;
    switch(isUpper(c)){
    case FALSE:
      printf("文字 %c の ascii code は %d(0x%x)で,アルファベット大文字ではありません\n",c,c,c);
      break;
    case TRUE:
      printf("文字 %c の ascii code は %d(0x%x)で,アルファベット大文字です\n",c,c,c);
    }
  }
}

int isUpper(char c){
  
  if(c>='A' && c<='Z') return TRUE;
  else return FALSE;
}

