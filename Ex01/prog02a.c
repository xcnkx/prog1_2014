#include <stdio.h>

main(){

  char c;
  
  printf("文字を入力してください：");
  scanf("%c",&c);
  printf("文字 %c の ascii code は %d(0x%x)です\n",c,c,c);
}
