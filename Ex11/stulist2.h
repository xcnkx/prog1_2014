
typedef struct{
  char class[5];
  int  ID;
  char name[20];
  int mathscore;
  int engscore;
} Record;

/* struct declaration */

typedef struct node *NodePointer;

struct node {

  Record data;

  NodePointer next;

};


/* prototype declaration */

NodePointer insert(Record);

NodePointer finditem(int);

void listprint(void);

NodePointer make_1node(Record, NodePointer);

NodePointer delete(int);


/* Global Variable head */

NodePointer head;

