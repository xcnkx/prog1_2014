#include <stdio.h>

main()
{
  int i;
  int start, stop;
  char string[] = "to Advance Knowledge for Humanity";
  char *p, *q;
  
  printf("Please input start and stop numbers (1 - 33, start <= stop): ");
  scanf("%d%d", &start, &stop);

  /* 通常の配列添字を使い、配列要素を順次参照する方法 */
  for(i = start-1; i<stop; i++) {
    printf("%c",string[i]);
  }
  printf("\n");
  
  /* ポインタ演算で参照するアドレスを変えていく方法 */
  p = &string[0];
  for(i = start-1; i<stop; i++) {
    printf("%c",*(p + i));
  }
  printf("\n");

  /* ポインタ変数に格納されているアドレスそのものを変えていく方法 */
  for(q = p+start-1; q < p+stop; q++) {
    printf("%c",*q);
  }
  printf("\n");

}
