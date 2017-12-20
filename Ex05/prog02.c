#include <stdio.h>

main()
{
    int a[ ] = {12, 10, 4, 23, 2, -5 };
    int *ptr = a; 

    /* この時点で，ptr は配列 a の 0番目の要素のアドレスを持つ． */

    /* アドレスが示す値だから*/
    printf("*ptr=%d\n",*ptr);

    /* アドレスを２個分だけずらしたから*/
    printf("*(ptr + 2)=%d\n",*(ptr + 2));

    /* ptr配列の２番目の要素だから*/
    printf("ptr[2]=%d\n",ptr[2]);

    /* ptr配列の２番目の要素を出力してから＋１している */
    printf("ptr[2]++=%d\n",ptr[2]++);

    /*ポインタが示すアドレスを＋１ずらしているから */
    printf("*++ptr=%d\n",*++ptr);

    /*出力の後にポインタが示すアドレスを-１ずらしている */
    printf("*ptr--=%d\n",*ptr--);

    /* 元のアドレスに戻ったから*/
    printf("*ptr=%d\n",*ptr);

    /* 以上の変更により配列 a の内容は 12, 10, 5, 23, 2, -5 となる */
    printf("a[0]=%d\n",a[0]);
    printf("a[1]=%d\n",a[1]);
    printf("a[2]=%d\n",a[2]);
    printf("a[3]=%d\n",a[3]);
    printf("a[4]=%d\n",a[4]);
    printf("a[5]=%d\n",a[5]);
}

/*
実行結果：

./a.out
*ptr=12
*(ptr + 2)=4
ptr[2]=4
ptr[2]++=4
*++ptr=10
*ptr--=10
*ptr=12
a[0]=12
a[1]=10
a[2]=5
a[3]=23
a[4]=2
a[5]=-5
*/
