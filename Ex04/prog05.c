#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024

main(){
  
  char buf[MAX];
  char str[MAX] = "[Wakamatsu]";
  char res[MAX];
  int i,j,n,c = 0,str_len,buf_len;

  while(1){
    printf("%s\n",str);
    if(scanf("%d%s",&n,buf) == EOF){
      break;
    }
    c = 0;
    str_len = strlen(str);
    buf_len = strlen(buf);
    
    if(str_len + buf_len > MAX-1){
      printf("error\n");
      continue;
    }
    if(str_len<n){
      continue;
    }
    
    for(i=0;i<n;i++){
      res[i] = str[i];
      c++;
    }
    if(i==n){
      res[i] = '[';
      for(j=0;j<buf_len;j++){
	res[++i] = buf[j];
      }
      res[++i]=']';
    }
    for(j=c;j<str_len;j++){
      res[++i] = str[j];
    }
    strcpy(str,res);
  }
}
    
    
