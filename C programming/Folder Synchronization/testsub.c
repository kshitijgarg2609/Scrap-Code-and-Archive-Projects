#include <stdio.h>
#include "strutil.h"
#include <string.h>

int main()
{
char *k="fdrdfs";
char *s;
s=substring(k,0,strlen(k));
printf("Test 1 : %s\n",s);
s=substring(k,1,strlen(k));
printf("Test 2 : %s\n",s);
s=substring(k,2,strlen(k));
printf("Test 3 : %s\n",s);
s=substring(k,3,strlen(k));
printf("Test 4 : %s\n",s);
s=substring(k,4,strlen(k));
printf("Test 5 : %s\n",s);
printf("Test str : %s index of %c is %d\n",k,'d',indexof(k,'d'));
printf("Test str : %s last index of %c is %d\n",k,'d',lastindexof(k,'d'));
return 0;
}