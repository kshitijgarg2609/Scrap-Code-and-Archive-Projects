#include <stdio.h>
#include <string.h>
#include "opfile.h"
#include <dirent.h>
#include "linkedlist.h"
#include "strutil.h"


char *src;
char *dest;
char *srca;
char *desta;
int slen;
int dlen;
int mode;

void init(char*,char*);
char* eliminatepdir(char*);
char* attach(char*,int);
void traverse(char*);
void eliminatorcommon();
void operate();
void test();

int main()
{
char *s;
init("E:/Text/A/","E:/Text/B/");
printf("check src : %s\ncheck dest : %s\n",srca,desta);
printf("check src attach : %s\ncheck dest a: %s\n",attach("/43/",0),attach("/43/",1));
mode=0;
test();
mode=2;
test();
eliminatorcommon();
operate();
return 0;
}

void init(char *a,char *b)
{
initializ(5);
src=a;
dest=b;
srca=substring(src,0,strlen(src)-1);
desta=substring(dest,0,strlen(dest)-1);
slen=strlen(a);
dlen=strlen(b);
mode=0;
traverse(src);
mode=2;
traverse(dest);
}

char* eliminatepdir(char *a)
{
return substring(a,(mode==0)?(slen-1):(dlen-1),strlen(a));
}

char* attach(char *a,int b)
{
return concat((b==0)?srca:desta,a);
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

void eliminatorcommon()
{
int stat;
node *ptr;
linkedlist temp;
temp=list[0];
for(ptr=temp.head;ptr!=NULL;ptr=ptr->next)
{
stat=delete(2,ptr->str);
if(stat==1)
{
stat=delete(0,ptr->str);
}
}
temp=list[1];
for(ptr=temp.head;ptr!=NULL;ptr=ptr->next)
{
stat=delete(3,ptr->str);
if(stat==1)
{
stat=delete(1,ptr->str);
}
}
}

void operate()
{
node *ptr;
int stat;
linkedlist temp;
temp=list[2];
for(ptr=temp.head;ptr!=NULL;ptr=ptr->next)
{
printf("Deleting folders : %s\n",attach(ptr->str,1));
deletedir(attach(ptr->str,1));
}
temp=list[3];
for(ptr=temp.head;ptr!=NULL;ptr=ptr->next)
{
printf("Deleting files : %s\n",attach(ptr->str,1));
deletedir(attach(ptr->str,1));
}
temp=list[0];
for(ptr=temp.head;ptr!=NULL;ptr=ptr->next)
{
printf("Making dir : %s\n",attach(ptr->str,1));
mkdir(attach(ptr->str,1));
}
temp=list[1];
for(ptr=temp.head;ptr!=NULL;ptr=ptr->next)
{
printf("Copying file from : %s to :%s\n",attach(ptr->str,0),attach(ptr->str,1));
copy(attach(ptr->str,0),attach(ptr->str,1),8192);
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