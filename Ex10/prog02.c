#include <stdio.h>

typedef struct{
  int  id;       /* ID       */
  char name[20]; /* 名前     */
  int  score;    /* 点数     */
  char grade;    /* グレード */
} Record;


main(){
  
  Record data[2] = {{1220006,"Kamiya Cristian",100,'A'},
		      {1270007,"James Bond",69,'A'}};
  Record *p=data;
  int i;
  
  for(i=0;i<2;i++){
    printf("%d\n",(p+i)->id);
    printf("%s\n",(p+i)->name);
    printf("%d\n",(p+i)->score);
    printf("%c\n",(p+i)->grade);
    printf("data[%d] = %p\n",i,*(p+i));
    printf("sizeof(data[%d]) = %d\n\n",i,sizeof(data[i]));
  }
}
