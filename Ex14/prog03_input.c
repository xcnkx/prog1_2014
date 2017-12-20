#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prog03.h"

#ifdef TEST
main () {
int i;
Planet planets[NPLANETS];
    
if (input_planet(planets) != 0) {
fprintf(stderr,"Error has occurred!\n");
 exit(-1);
 }

 for (i = 0; i < NPLANETS; i++) {
   printf("Name: %s\n",planets[i].name);
   printf(" Radius: %.0f [km]\n", planets[i].radius);
   printf(" Density: %.2f [g/cc]\n", planets[i].density);
   printf(" Orbital Radius: %.3e [km]\n", planets[i].orbital_radius);
 }
    
}

#endif

int input_planet (Planet *planet){
  
  int i;
  FILE *fp;
  
  if((fp = fopen("planet.txt","r"))== NULL){
    printf("Cannot open the file.");
    return -1;
  }
  for (i = 0; i < NPLANETS; i++) {
  
    fscanf(fp,"%s%lf%lf%lf",planet[i].name,&planet[i].radius,&planet[i].density,&planet[i].orbital_radius);
  
  }
  
  fclose(fp);
  
  return 0;
}
     
  
