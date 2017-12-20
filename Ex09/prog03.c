#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

char grade_char(int);
void search(char);

typedef struct{
  char  sid[8];
  char  sname[10];
  int   score[5];
  char  grade;
  double average;
} Record;

int main(int argc,char *argv[]){
  
  Record data[MAX];
  int status,i=0,j;
  FILE *fp;
  char str[10];

  /*error process*/
  if(argc != 2){
    printf("Error!  Usage: ./a.out datafilename\n");
  }
  /*file open*/
    if((fp = fopen(argv[1],"r")) == NULL){
    printf("file open error !\n");
    exit(1);
  }
  
  /*data input*/

    while((status = fscanf(fp,"%s %s %d %d %d %d %d",data[i].sid,data[i].sname,&data[i].score[0],&data[i].score[1],&data[i].score[2],&data[i].score[3],&data[i].score[4])) != EOF){

    data[i].average = 0;
    for(j=0;j<5;j++){
      data[i].average += (double)data[i].score[j];
    }
      
    data[i].average /= 5;
      
    data[i].grade = grade_char(data[i].average);
    
    i++;
  }
    
  /*print data*/
  for(j=0;j<i;j++){
    printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\t%c\t%.2f\n",data[j].sid,data[j].sname,data[j].score[0],data[j].score[1],data[j].score[2],data[j].score[3],data[j].score[4],data[j].grade,data[j].average);
  }
  
  /*linear search*/
  while(1){
    printf("Input a student name/ID# :");
    if((status = scanf("%s",str)) == EOF) break;
    
    for(j=0;j<i;j++){
      if(strcmp(str,data[j].sid) == 0 || strcmp(str,data[j].sname) == 0){
	printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\t%c\t%.2f\n",data[j].sid,data[j].sname,data[j].score[0],data[j].score[1],data[j].score[2],data[j].score[3],data[j].score[4],data[j].grade,data[j].average);
	break;
      }      
    }
    if(j==i) printf("This student does not exist !\n");
    }
  /*file close*/
  fclose(fp);
}

char grade_char(int score)
{
  if(score>=0 && score<35) return 'F';
  else if(score>=35 && score<50) return 'D';
  else if(score>=50 && score<65) return 'C';
  else if(score>=65 && score<80) return 'B';
  else if(score>=80 && score<=100) return 'A';
  else return -1;
}
  
    
