#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int delcap(char *);

main(int argc,char *argv[])
{
  
  int i,n,elem;
  char *array;
  
  for(i=1;i<argc;i++){
    
    array = (char *)malloc(strlen(argv[i])*sizeof(char));
    strcpy(array,argv[i]);
    printf("%s(%d) -> ",argv[i],strlen(argv[i]));
    n=delcap(array); 
    printf("%s(%d)\n",array,n);
    
    free(array);
  }
}

int delcap(char *array)
{
  int i,j=0;
  
  for(i=0;array[i]!='\0';i++){
    if(array[i]>='a' && 'z'>=array[i]){
      array[j] = array[i];
      j++;
    }
    else continue;
  }
  array[j] = '\0';
  
  return strlen(array);
}
  
    
      

  
  
