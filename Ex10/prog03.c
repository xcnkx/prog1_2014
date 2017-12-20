#include <stdio.h>
#include <math.h>

struct xy {
  double  x; /* x座標 */
  double  y; /* y座標 */
};

struct rect {
  struct xy p1;
  struct xy p2;
};

main(){
  
  struct rect rect1;
  double diag,width,height,area;
  
  printf("Enter x and y axix value of two points :");
  scanf("%lf%lf%lf%lf",&rect1.p1.x,&rect1.p1.y,&rect1.p2.x,&rect1.p2.y);
  
  width = fabs(rect1.p1.x - rect1.p2.x);
  height = fabs(rect1.p1.y - rect1.p2.y);
  
  diag = sqrt(pow(width,2)+pow(height,2));
  area = width * height;

  printf("The width of the rectangle is :%f\n",width);
  printf("The height of the rectangle is :%f\n",height);
  printf("The area of the rectangle is :%f\n",area);
  printf("The lenght of the diagonal line of the rectangle is :%f\n",diag);
}
  
  
  
  
