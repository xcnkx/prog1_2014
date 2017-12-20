#include <stdio.h>
main()
{
   int i;
   int array[] = {11,22,33,44};

   for(i = 0 ; i < 4 ; i++)
     printf( "%d %p %d\n",i,&array[i],array[i]);
   printf("\n%p\n",array);
}
