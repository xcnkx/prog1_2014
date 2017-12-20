#include <stdio.h>
#include <stdlib.h>
#define NUM 4

void reverse(char *);

int main()
{
  char *array[NUM] = {"abcd","efgh","lmnopqr","stuvw"};
  int i;

  for(i = 0; i < NUM; i++){
    printf("[%2d] : %s -> ", i, array[i]);
    reverse(array[i]);
    printf("\n");
  }
}

void reverse(char *str)
{
  static int i;

  if(str[i] == '\0') return;
  else {
    reverse(&str[i+1]);
    printf("%c",str[i]);
  }
}
