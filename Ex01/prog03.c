#include <stdio.h>

main()
{
  char c,status;
  
  while(1){
    status = scanf("%c",&c);
    if(status!=1)break;
    if(c>='a' && c<'z'){
      printf("%c",c+1);
    }
    else if(c == 'z'){
      printf("%c",c-25);
    }
    else printf("%c",c);
  }
}
