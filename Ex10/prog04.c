#include <stdio.h>
#include <math.h>

typedef struct{
  double  x; /* x座標 */
  double  y; /* y座標 */
} Point; 

typedef struct{
  Point p1; 
  Point p2;
  Point p3;
} Triangle; 

main(){
  
  Triangle t1;
  double l1,l2,l3,area,s;
  
  printf("三角形の3頂点の座標(x,y)を入れて下さい\n");
  scanf("%lf%lf%lf%lf%lf%lf",&t1.p1.x,&t1.p1.y,&t1.p2.x,&t1.p2.y,&t1.p3.x,&t1.p3.y);
  
  l1 = sqrt(pow(fabs((t1.p1.x)-(t1.p2.x)),2)+pow(fabs((t1.p1.y)-(t1.p2.y)),2));
  l2 = sqrt(pow(fabs((t1.p1.x)-(t1.p3.x)),2)+pow(fabs((t1.p1.y)-(t1.p3.y)),2));
  l3 = sqrt(pow(fabs((t1.p2.x)-(t1.p3.x)),2)+pow(fabs((t1.p2.y)-(t1.p3.y)),2));
  
  s = (l1+l2+l3)/2;
  
  area = sqrt(s*(s-l1)*(s-l2)*(s-l3));
  
  printf("点の座標(%f,%f)\n",t1.p1.x,t1.p1.y);
  printf("点の座標(%f,%f)\n",t1.p2.x,t1.p2.y);
  printf("点の座標(%f,%f)\n",t1.p3.x,t1.p3.y);
  printf("面積 %f\n",area);
}
