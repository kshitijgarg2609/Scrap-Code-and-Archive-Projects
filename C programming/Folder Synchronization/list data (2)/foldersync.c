#include <stdio.h>
#include <string.h>
#include "opfile.h"
#include <dirent.h>
#include "linkedlist.h"
#include "strutil.h"


char *src;
char *dest;
int slen;
int dlen;
int mode;

void init(char*,char*);
char* eliminatepdir(char*);
void traverse(char*);
void test();

int main()
{
char *s;
init("E:/Text/A/","E:/Text/B/");
mode=0;
traverse(src);
test();
mode=2;
traverse(dest);
test();
return 0;
}

void init(char *a,char *b)
{
initializ(5);
src=a;
dest=b;
slen=strlen(a);
dlen=strlen(b);
}

char* eliminatepdir(char *a)
{
return substring(a,(mode==0)?(slen-1):(dlen-1),strlen(a));
}

void traverse(char *n)
{
DIR *dir;
struct dirent *subd;
char *s,*q;
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
q=eliminatepdir(s);
queue(mode+1,q);
}
else if(stat==1)
{
q=eliminatepdir(s);
queue(mode,q);
traverse(s);
}
}
closedir(dir);
}
}

void test()
{
printf("######################  Label : %d : ###############\n",mode);
printf("Displaying folders : %d\n",mode);
printf("________________________________________________________________\n");
display(mode);
printf("________________________________________________________________\n\n\n");
printf("Displaying files : %d\n",(mode+1));
printf("________________________________________________________________\n");
display(mode+1);
printf("________________________________________________________________\n");
}