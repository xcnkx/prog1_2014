#include <stdio.h>
void swap(int * , int *);
main()
{
  int x = 5, y = 3;
  printf("start: x=%d\ty=%d\n", x, y);
  printf("&x=%p\t&y=%p\n",&x,&y);
  swap(&x, &y);
  printf("end: x=%d\ty=%d\n", x, y);
}

void swap(int *p, int *q)
{
  int temp;

  printf("p=%d\t q=%d\n",*p,*q);
  temp = *p;
  *p = *q;  
  *q = temp; 
  printf("p=%d\t q=%d\n",*p,*q);
  printf("p=%p\tq=%p\n",p,q);
}
