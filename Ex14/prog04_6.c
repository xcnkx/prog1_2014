#include <stdio.h>
#include "prog04_1.h" /* (1) */
 /* 必要に応じてプログラムを追加、修正 */
 #if defined TEST0
 main () {

   Triangle t;
   double h;
   double surface,vol;

   InputTriPrism(&t,&h);

   /* IsTriangleの結果を元に先へ進むか，InputTriPrismで再入力へ */
   if(IsTriangle(&t)!=1){ 
     printf("These points can not form a triangle !\n");
     InputTriPrism(&t,&h);
   }
 
   surface = CalcTriPrismSurface(&t,&h);

   /* CalcTriPrismSurfaceで求めた三角柱の表面積を表示 */ 
   printf("Surface : %f\n",surface );

    /* 三角柱の体積を求める */
   vol = CalcTriPrismVolume(&t,&h);

   /* CalcTriPrismVolumeで求めた三角柱の体積を表示 */ 	
   printf("Volume : %f\n",vol);
   
}



void InputTriPrism(Triangle *t,double *h)
{
  t->p1.x = 0;
  t->p1.y = 0;
  t->p2.x = 3;
  t->p2.y = 0;
  t->p3.x = 0;
  t->p3.y = 4;
  
  *h = 2;
}

int IsTriangle(Triangle *t)
{
  return 1;
}

double CalcTriPrismSurface(Triangle *t, double *h)
{
  return 36;
}
#endif
double CalcTriPrismVolume(Triangle *t1,double *h)
{
  double l1,l2,l3,s,tarea,volume;
  
  l1 = sqrt(pow(fabs((t1->p1.x)-(t1->p2.x)),2)+pow(fabs((t1->p1.y)-(t1->p2.y)),2));
  l2 = sqrt(pow(fabs((t1->p1.x)-(t1->p3.x)),2)+pow(fabs((t1->p1.y)-(t1->p3.y)),2));
  l3 = sqrt(pow(fabs((t1->p2.x)-(t1->p3.x)),2)+pow(fabs((t1->p2.y)-(t1->p3.y)),2));
  
  s = (l1+l2+l3)/2;
  
  tarea = sqrt(s*(s-l1)*(s-l2)*(s-l3));
  
  volume = tarea*(*h);
  
  return volume;
}

