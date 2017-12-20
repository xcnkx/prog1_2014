#include <stdio.h>
main()
{
   int i;
   char *array[] = {"ab","cd","ef","gh"};

   for(i = 0 ; i < 4 ; i++)
     printf( "%d %p %s\n",i,&array[i],array[i]);
   printf("\n%p\n",array);
}
