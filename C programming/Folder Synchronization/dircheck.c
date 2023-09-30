#include <stdio.h>
#include <string.h>
#include "opfile.h"
#include <dirent.h>
#include "linkedlist.h"

void traverse(char*);
void test();

int main()
{
char *str,*s;
str="E:/Text/A/";
initializ(5);
traverse(str);
test();
return 0;
}

void traverse(char *n)
{
DIR *dir;
struct dirent *subd;
char *s;
int stat;
dir=opendirectory(n);
if(dir)
{
while(subd=readdir(dir))
{
s=subd->d_name;
if(strcmp(s,".")==0||strcmp(s,"..")==0)
continue;
s=concatdir(n,s);
stat=isdir(s);
if(stat==0)
{
queue(1,s);
}
else if(stat==1)
{
queue(0,s);
traverse(s);
}
}
closedir(dir);
}
}

void test()
{
printf("Displaying folders\n");
printf("________________________________________________________________\n");
display(0);
printf("________________________________________________________________\n\n\n");
printf("Displaying files\n");
printf("________________________________________________________________\n");
display(1);
printf("________________________________________________________________\n");
}