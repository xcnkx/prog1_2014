#include <stdio.h>

main(){

  char c;
  int i,status,count=0;
  
  printf("文字を入力してください：");
  while(1){
    status = scanf("%c",&c);  
    if(status!=1 || c=='\n') break;
    printf("文字 %c の ascii code は %d(0x%x)です\n",c,c,c);
  }
}
