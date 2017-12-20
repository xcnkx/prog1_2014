#include <stdio.h>
#include <stdlib.h>

void my_strextract(char *,char *);

int main(){
  
  char *s,buf[128];
  
  while(1){

    printf("Enter string -> ");
   
    if(scanf("%s",buf)!=EOF){
  
      s = (char*)malloc(sizeof(buf));
       
      my_strextract(s,buf);
    }
    else break;
  }
}

void my_strextract(char *s1, char *s2)
{
  int i, j = 0, len,buf;

  for(i = 0; s2[i] != '\0'; i++);
  len = i;

  for(i = 0; i < len; i++){
    if(s2[i] >= '0' && s2[i] <= '9'){
      if(s2[i] == '0' && i == 0) continue;  //0を落す
      s1[j] = s2[i];
      j++;
    }   
  }
  s1[j] = '\0';
  
  buf = atoi(s1);
  printf("%d\n",buf);
  
}
      
    
    
