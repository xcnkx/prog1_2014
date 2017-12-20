#include <stdio.h>
#include <ctype.h> /* 関数toupperを使うため */

main() {
  char fruits[][10]={"apple", "orange", "grape"};
  int i;

  printf("Suppose that we now have (0) %s, (1) %s, (2) %s.\n",
                            fruits[0],fruits[1],fruits[2]);
  printf("Input 0, 1, or 2: ");
  scanf("%d",&i);

  fruits[i][0]=toupper(fruits[i][0]);

  printf("\n%s is your favorite fruit!\n",fruits[i]);
}
