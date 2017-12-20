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
#endif


void InputTriPrism(Triangle *t1,double *h)
{  
  printf("1st vertex:");
  scanf("%lf%lf",&t1->p1.x,&t1->p1.y);
  printf("2st vertex:");
  scanf("%lf%lf",&t1->p2.x,&t1->p2.y);
  printf("3st vertex:");
  scanf("%lf%lf",&t1->p3.x,&t1->p3.y);
  printf("height:");
  scanf("%lf",h);
  
}
#if defined TEST0
int IsTriangle(Triangle *t)
{
  return 1;
}

double CalcTriPrismSurface(Triangle *t, double *h)
{
  return 20;
}
double CalcTriPrismVolume(Triangle *t,double *h)
{
  return 12;
}
#endif
