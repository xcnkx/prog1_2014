#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#define NUM 4

char *reverse(char *);

int main(){
  
  char *array[NUM] = {"abcd","efgh","lmnopqr","stuvw"};
  int i;

  for(i=0;i<NUM;i++){
    printf("[%d] : %s -> %s\n",i,array[i],reverse(array[i]));
    
  }
}

char *reverse(char *str)
{
  char *buf;
  int i,j=0,len;

  for(i=0;str[i] != '\0';i++);
  len = i;

  buf = (char*)malloc(sizeof(char)*len);
  
  for(i=len;i>0;i--){
    buf[j] = str[i-1];
    j++;
  }
  j++ ;
  buf[j] = '\0';

  return buf;
}
  
