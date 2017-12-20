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
  t->p2.x = 0;
  t->p2.y = 0;
  t->p3.x = 0;
  t->p3.y = 0;
  
  *h = 2;
}
#endif
int IsTriangle(Triangle *t)
{
  if(((t->p1.x == t->p2.x)&&(t->p2.x == t->p3.x))||((t->p1.y == t->p2.y)&&(t->p2.y == t->p3.y))) return 0;
  else return 1;
}
#if defined TEST0
double CalcTriPrismSurface(Triangle *t, double *h)
{
  return 20;
}
double CalcTriPrismVolume(Triangle *t,double *h)
{
  return 12;
}
#endif
