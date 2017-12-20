#include <stdio.h>
#include <string.h>
#include <stdlib.h>

main(int argc, char *argv[])
{
  
  int i,j;
  
  for(i=1;i<argc;i++){
    for(j=strlen(argv[i]);j>=0;j--){
      printf("%c",argv[i][j]);
    }
    printf("\n");
  }
}
