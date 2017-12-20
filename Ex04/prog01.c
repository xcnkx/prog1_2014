#include <stdio.h>

main()
{
  int i, *p;
  i = 777;
  p = &i;
  
  printf("The value of i : %d\n", i);
  printf("The address of i : %p\n",&i);
  
  printf("The value pointed by p : %d\n",*p);
  printf("The value of p : %p\n",p);
  printf("The address of p : %p\n",&p);
}
