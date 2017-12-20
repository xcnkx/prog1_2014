#include <stdio.h>
#include <stdlib.h>
#include "prog01.h"

main()
{
  int i, num;

  printf("[Initial]\n");
  head = make_1node(0, NULL);
  for (i = 1; i <= 9; ++i) {
    insert(i);
  }
  listprint();

  printf("[Insert](enter number)\n");
  while (scanf("%d", &num) == 1) {
    if (insert(num) == NULL) {
      printf("Data %d is already on the list\n", num);
    }
    listprint();
  }
}

NodePointer insert(int keydata)
{
  NodePointer newnode;

  if (finditem(keydata) == NULL) {                 //keyがkeydataのノードを検索、あればNULLをリターンする、以下はない時の処理
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

  printf("Head");
  for (n = head->next; n != NULL; n = n->next) {           //headの次からスタートしNULLまでループし、リストを順にたどる
    printf(" - %d", n->key);
  }
  printf("\n");
}

NodePointer finditem(int keydata)
{
  NodePointer n;

  for (n = head; n->next != NULL; n = n->next) {       //リストをnがheadから、n->nextがNULLまでループし、リストを順にたどる
    if (n->next->key == keydata) {                   //nの次のノードのkeyとvalueを比較し、見つかったらノード(n)をリターン
      return n;
    }
  }
  return NULL;
}

NodePointer make_1node(int keydata, NodePointer p)  //ノードを動的メモリ割り当てで作成する
{
  NodePointer n;

  if ((n = malloc(sizeof(struct node))) == NULL) {
    printf("Error in memory allocation\n");           //何らかの理由でmallocが失敗したら終了する
    exit(8);
  }

  n->key = keydata;      //keyとnextに引数の値をセットする
  n->next = p;

  return n;
}
