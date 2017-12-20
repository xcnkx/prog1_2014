#include <stdio.h>
main()
{
  int x=3, y=5; /* この行は変更しない */
  int *px,*py;
  
  px = &x;
  py = &y;

  /* 課題では以下のprintf()の中をx,yを使わない形に書き換える */
  printf(" value 1: %d  (%p)\n", *px, px );
  printf(" value 2: %d  (%p)\n", *py, py );
  printf(" sum:     %d\n", (*px)+(*py) );
  printf(" product: %d\n", (*px)*(*py) );
}
