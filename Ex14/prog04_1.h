#include <math.h>
typedef struct {
  double x;
  double y;
} Point;

typedef struct{
  Point p1;
  Point p2;
  Point p3;
} Triangle;

void InputTriPrism(Triangle *,double *);

int IsTriangle(Triangle *);

double CalcTriPrismSurface(Triangle *, double *);

double CalcTriPrismVolume(Triangle *,double *);
