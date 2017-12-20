
#define myabs(x) ((x) > 0 ? (x): -(x)) 

typedef struct{
  int x;
  int y;
} Point;

typedef struct{
  Point p[3];
} Triangle;

double calcarea(Triangle);


