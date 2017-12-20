#include <stdio.h>

main(){
  
  char str1[100], str2[100];
  int i;
  
  printf("Input: ");
  scanf("%s", str1);
  
  for(i=0;;i++){
    if(str1[i]==NULL){
      str2[i]='\0';
      break;
    }
    else str2[i]=str1[i];
  }
  
  printf("[%s]\n",str2);
}
      
