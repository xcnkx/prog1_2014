#include <stdio.h>
main()
{
   int i;
   char array[] = {'a','b','c','d'};

   for(i = 0 ; i < 4 ; i++)
     printf( "%d %p %c\n",i,&array[i],array[i]);
   printf("\n%p\n",array);
}
