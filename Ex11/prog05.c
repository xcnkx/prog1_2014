#include <stdio.h>
#include <stdlib.h>
#include "stulist.h"

main(int argc,char *argv[])
{
  int i, num,status;
  FILE *fp;
  Record head_data = {"\0",0,"\0"},new_data;
  //file open
  if(argc == 1){  
    fp = fopen("Student.dat","r");
    if(fp == NULL){
      printf("Cannot open file Student.dat\n");
      exit(1);
    }
  }
  else {
    fp = fopen(argv[1],"r");
    if(fp == NULL){
      printf("Cannot open file %s\n",argv[1]);
      exit(2);
    }
  }

  printf("[Initial]\n");
  head = make_1node(head_data , NULL);
  
  while((status = fscanf(fp,"%s%d%s",&new_data.class,&new_data.ID,&new_data.name))!= EOF){
    insert(new_data);
  }
  
  listprint();


  while(1){
    printf("[Insert] new data: (class ID name)->");
    if(scanf("%s%d%s",&new_data.class,&new_data.ID,&new_data.name ) ==EOF){
      printf("\n");
      break;
    }
    else {
      if (insert(new_data) == NULL) {
	printf("Data already exist !!\n");
      }
      listprint();
    }
  }
}

NodePointer insert(Record keydata)
{
  NodePointer newnode;

  if (finditem(keydata.ID) == NULL) {                 //keyがkeydataのノードを検索、あればNULLをリターンする、以下はない時の処理
    newnode = make_1node(keydata, head->next);      //keyがkeydataのノードnewnodeを作成、そしてnewnode->nextをhead->nextと同じにする
    head->next = newnode;                       //head->nextをnewnodeにする

    return newnode;
  }
  else {
    return NULL;
  }
}

void listprint(void)
{
  NodePointer n;

  printf("Head -\n");
  for (n = head->next; n != NULL; n = n->next) {           //headの次からスタートしNULLまでループし、リストを順にたどる
    printf("%10s %10d %10s\n", n->data.class,n->data.ID,n->data.name);
  }
  printf("\n");
}

NodePointer finditem(int id)
{
  NodePointer n;

  for (n = head; n->next != NULL; n = n->next) {       //リストをnがheadから、n->nextがNULLまでループし、リストを順にたどる
    if (n->next->data.ID == id) {                   //nの次のノードのkeyとvalueを比較し、見つかったらノード(n)をリターン
      return n;
    }
  }
  return NULL;
}

NodePointer make_1node(Record keydata, NodePointer p)  //ノードを動的メモリ割り当てで作成する
{
  NodePointer n;

  if ((n = malloc(sizeof(struct node))) == NULL) {
    printf("Error in memory allocation\n");           //何らかの理由でmallocが失敗したら終了する
    exit(8);
  }

  n->data = keydata;      //keyとnextに引数の値をセットする
  n->next = p;

  return n;
}
