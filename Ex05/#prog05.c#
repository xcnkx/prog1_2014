#include <stdio.h>

main()
{
  char *presidents[4]={"George Washington","John Adams","Thomas Jefferson","James Madison"};
  int i,j,space[4];
  char initial[4];

  for(i=0;i<4;i++){
    printf("%s\n",presidents[i]);
  }

  printf("=======================\n");
  
  for(i=0;i<4;i++){
    for(j=0;presidents[i][j] != ' ';j++){
      if(j==0) initial[i] = presidents[i][j];
    }
    space[i]=j;
  }
  
  for(i=0;i<4;i++){
    printf("%c. ",initial[i]);
      for(j=space[i];presidents[i][j]!='\0';j++){
	printf("%c",presidents[i][j]);
      }
    printf("\n");
  }
}


