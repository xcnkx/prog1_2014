#include <stdio.h>
#include <string.h>

int checkString(char *);

main()
{
  int i;
  char basestr[7][15]={"Good News","Bad News","Happy News","Sad News",
                       "Sweet News","Cool News","Wonderful News"};

  for(i = 0; i < 7; i++) {
    /* If a string contains the patterns "Bad" or "Sad", 
       replace it with the new string "GOOD News". */
    if(checkString(basestr[i]) == 1){
      strcpy(basestr[i],"GOOD News");
    }
  }
  /* Print out the result */
  printf("--\n");
  for(i = 0; i < 7; i++) printf("%2d %s\n",i ,basestr[i]);
  printf("--\n");
}


/* Check whether a string contains the patterns "Bad" or "Sad" 
   at the first 3 characters using strncmp function */
/* Refer to the command "man strcmp" for the strncmp function. */
int checkString(char *str)
{
  if((strncmp(str,"Bad",3) == 0 )||(strncmp(str,"Sad",3)==0)) return 1;
  else return 0;
}
