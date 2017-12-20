#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 9

double ecl_dis(double,double,double);

main(){
  
  FILE *fpin,*fpout;
  double data[10][4],max=0,min;
  int i,i_max,i_min,d,status;
  
  fpin = fopen("coord.in","r");
  if(fpin == NULL){
    printf("read file open error\n");
    exit(1);
  }

  fpout = fopen("coord.out","w");
  if(fpout == NULL){
    printf("write file open error\n");
    fclose(fpin);
    exit(2);
  }
   
  //reading data
  for(i=0;i<MAX;i++){
    status = fscanf(fpin,"%lf%lf%lf",&data[i][0],&data[i][1],&data[i][2]);
    if(status=!3)break;
  }
   
  //calculing the Euclid distance
  
  for(i=0;i<MAX;i++){
    
     data[i][3] = ecl_dis(data[i][0],data[i][1],data[i][2]);
    if(max<data[i][3]){
      max = data[i][3];
      i_max = i;
    }
    if(i==0) min = data[i][3];
    if(min>data[i][3]){
      min = data[i][3];
      i_min = i;
    }      
  }
  //output
  fprintf(fpout,"max : %.1f %.1f %.1f (%.1f)\nmin : %.1f %.1f %.1f (%.1f)\n",data[i_max][0],data[i_max][1],data[i_max][2],max,data[i_min][0],data[i_min][1],data[i_min][2],min);

  fclose(fpin);
  fclose(fpout);
}
  
double ecl_dis(double x,double y,double z){
  
  double d;
  d = x*x+y*y+z*z;
  return  sqrt(d);

}
  
