#include <stdio.h>
#include <math.h>

typedef struct {
  double  x; /* x座標 */
  double  y; /* y座標 */
} Point;

Point rotate_90_1(Point, Point);
Point rotate_90_2(Point *);
void  rotate_90_3(Point, Point *);
void  rotate_90_4(Point, Point);


Point p4;


main()
{
  Point p[2] = {{2.0, 2.0},{4.0, 3.0}}, p1,p2,p3;
  
  p1 = rotate_90_1(p[0],p[1]);
  p2 = rotate_90_2(p);
  rotate_90_4(p[0],p[1]);
  rotate_90_3(p[0],&p[1]);
  p3 = p[1];
  
  printf("rotate_90(1): %f %f\n",p1.x,p1.y);
  printf("rotate_90(2): %f %f\n",p2.x,p2.y);
  printf("rotate_90(3): %f %f\n",p3.x,p3.y);
  printf("rotate_90(4): %f %f\n",p4.x,p4.y);
}

Point rotate_90_1(Point center, Point p)
{
  Point temp,rotp;

  temp.x = p.x - center.x;
  temp.y = p.y - center.y;
  
  rotp.x = temp.x * cos(M_PI/2) + temp.y * (-sin(M_PI/2)) + center.x;
  rotp.y = temp.x * sin(M_PI/2) + temp.y * cos(M_PI/2) + center.y;
  
  return rotp;
}

Point rotate_90_2(Point *p)
{
  Point temp,rotp;
  
  temp.x = p[1].x - p[0].x;
  temp.y = p[1].y - p[0].y;
  
  rotp.x = temp.x * cos(M_PI/2) + temp.y * (-sin(M_PI/2)) + p[0].x;
  rotp.y = temp.x * sin(M_PI/2) + temp.y * cos(M_PI/2) + p[0].y;
  
  return rotp;
}

void rotate_90_3(Point center, Point *p)
{
  Point temp;
  
  temp.x = p->x - center.x;
  temp.y = p->y - center.y;
  
  p->x = temp.x * cos(M_PI/2) + temp.y * (-sin(M_PI/2)) + center.x;
  p->y = temp.x * sin(M_PI/2) + temp.y * cos(M_PI/2) + center.y;
  
}

void rotate_90_4(Point center, Point p)
{
  Point temp;
  
  temp.x = p.x - center.x;
  temp.y = p.y - center.y;
  
  p4.x = temp.x * cos(M_PI/2) + temp.y * (-sin(M_PI/2)) + center.x;
  p4.y = temp.x * sin(M_PI/2) + temp.y * cos(M_PI/2) + center.y;
}
