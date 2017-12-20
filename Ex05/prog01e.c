#include <stdio.h>
main()
{
   int i;
   char array[][10] = {"abc","def","ghi","lmn"}; 	

   for(i = 0 ; i < 4 ; i++)
     printf( "%d %p %c\n",i,&array[i],array[i]);
   printf("\n%p\n",array);
}
