#include <stdio.h>
#include <stdlib.h>

int main(){
  int *p[4];
  int a[2][4]={{1,2,3,4},{5,6,7,8}};
  p = a; 
  printf("%d\n", p[1][0]);

  return 0;
}
