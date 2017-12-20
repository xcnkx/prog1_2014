#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000
#define MAXDATA 1024
#define LENIP 16
#define LENHOST 256

main(){
  
  FILE *fp;
  char ip[MAXDATA][LENIP];
  char host[MAXDATA][LENHOST];
  char query[LENHOST];
  int i,j=0,status,count=0;

    
  //file open
  fp = fopen("stdhosts.txt","r");
  if(fp == NULL){
    printf("Cannot open the file\n");
    exit(1);
  }
  //data input loop
  for(i=0;i<MAXDATA;i++){
    status = (fscanf(fp,"%s%s",ip[i],host[i]));
    count++;
    if(status==EOF) break;
  }
   
  fclose(fp);
      
  
  //data query infinity loop
  while((status=scanf("%s",query))!=EOF){
    i=0;
    while((strcmp(host[i],query)!=0)&&(i<count))i++;
    if(i==count){
      if(strcmp("kanojo",query)==0) printf("found\n");
      else printf("not found\n");
    }

    else printf("%s\n",ip[i]);
  }
}
	
      
      
      
