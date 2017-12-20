#include <stdio.h>
#include <stdlib.h>

int main()
{
  char *str1="programming-c";
  char str2[]="PROGRAMMING-C";
  char *str3[]={"abcde","fghij","klmno"};
  char str4[3][6]={"ABCDE","FGHIJ","KLMNO"};
  char (*str5)[6];
  int  arr1[5];
  int  *arr2;


  str5 = str4;              /* str5はstr4の先頭を指す */

  printf( "size of str1:    %d\n", sizeof(str1) );

  printf( "size of str2:    %d\n", sizeof(str2) );

  printf( "size of str3:    %d\n", sizeof(str3) );
  /* 説明：  *str1はポインタの文字列だから、最初の文字を示すアドレスのメモリを確保しているから４バイト
            str2はただの文字列だから、ヌル文字を含む総文字数の分だけのメモリを確保しているから１４バイト
	    *str3 ポインタ配列であるから、先頭の文字のアドレスのメモリ×配列数のメモりを確保しているから１２バイト
   */

  printf( "size of str3[0]: %d\n", sizeof(str3[0]) );
  /* 説明：0番目の配列の先頭のアドレスが入るから４バイト                                        */

  printf( "size of str4:    %d\n", sizeof(str4) );

  printf( "size of str4[0]: %d\n", sizeof(str4[0]) );
  /* 説明： str4 は配列数×文字数だから、１８バイト
           str4[0] ヌル文字を含む０番目の配列の文字数だから、６バイト
   */


  printf( "size of str5:    %d\n", sizeof(str5) );
  /* 説明： str４の先頭を示すポインタだから、４バイト                                        */

  printf( "\n" );


  printf( "str3[0][1]: %c\n", str3[0][1] );

  printf( "*(str4+2)   %s\n", *(str4+2) );
  /* 説明：  *(str4+2) = *str[0+2]だから                                     */

  str5++;
  printf( "str5[0][3]: %c\n", str5[0][3] );
  /* 説明：  str5++しているから、これはstr4[1][3]を指すから。                                     */

  printf( "*str5:      %s\n", *str5 );
  /* 説明： 同じくstr5++しているから、str4[1]を指すから。                                       */

  printf( "(*str5)[2]: %c\n", (*str5)[2] );
  /* 説明：（難しいので、どうしても分らなければ飛ばしてよい）*/

  printf( "*(*str5+1): %c\n", *(*str5+1) );
  /* 説明：（難しいので、どうしても分らなければ飛ばしてよい）*/

  printf( "\n" );


  printf( "size of arr1:    %d\n", sizeof(arr1) );
  /* 説明： int型だから４×５で２０バイトだから                                       */

  arr2 = (int *) malloc( 5 * sizeof(int) );
  printf( "size of arr2:    %d\n", sizeof(arr2) );
  /* 説明：  ポインタだから４バイト                                     */

  free( arr2 );
  return 0;
}
