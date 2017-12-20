#include <stdio.h>
#define func(x) ((x)*(x)+2)

main()
{
  int a=2;
  double b=3.0;

  printf("a=%d, b=%f\n",a,b);
  printf("func(a)=%d\n",func(a));
  printf("func(a+1)=%d\n",func(a+1));
  printf("func(a)*3=%d\n",func(a)*3);
  printf("func(b)=%f\n",func(b));
  printf("func(b+1.0)=%f\n",func(b+1.0));
}
