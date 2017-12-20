#include <stdio.h>
#include <stdlib.h>

char gradechar(int);

int main(int argc, char *argv[]){
  
  int i,elem;
  
  if(argc == 1) exit(1);
  
  for(i=0;i<argc-1;i++){
    
    elem = atoi(argv[i+1]);
    
    printf("Point %d: %c\n",elem,gradechar(elem));
  }
}

char gradechar(int score)
{
  if (score>=80) return 'A';
  else if (score>=65) return 'B';
  else if (score>=50) return 'C';
  else if (score>=35) return 'D';
  else return 'F';
}
