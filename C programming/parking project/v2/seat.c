#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "strutil.h"

char *path="log.txt";

typedef struct data
{
int r,c,al;
char a,b;
}
park;

int p=3;
int q=5;
int ur=52;
int uc=48;
char lr=' ';
char lc=' ';
char s[3][5];
char UI[52][48];
park data[8][4];

char *cm;

void slot(char,char,int);
void reset();
void displayUI();
void allocate(int,int);
void display();
void allocatepark();
void parkUI(int,int,int);
void unpark(char,char);
void bestpark();
void writelog(int);

int main()
{
char r,c;
int i;
reset();
allocatepark();
printf("#####################Initial####################\n");
printf("___________________________________________________________________\n");
displayUI();
while(1)
{
printf("___________________________________________________________________\n");
cm=input();
printf("___________________________________________________________________\n");
if(strcmp(cm,"park")==0)
{
bestpark();
}
else if(strlen(cm)==9)
{
unpark(cm[7],cm[8]);
}
else if(strcmp(cm,"exit")==0)
{
printf("EXITING PROGRAM ...\n");
writelog(3);
break;
}
displayUI();
}
return 0;
}

void slot(char a,char b,int c)
{
s[0][0]=s[0][4]=s[1][0]=s[1][4]=s[2][0]=s[2][4]='|';
s[0][1]=s[0][2]=s[0][3]=s[2][1]=s[2][2]=s[2][3]='-';
s[1][1]=a;
s[1][2]=b;
s[1][3]=(c==1)?'*':' ';
}

void reset()
{
int i,j;
for(i=0;i<ur;i++)
{
for(j=0;j<uc;j++)
{
UI[i][j]='.';
}
}
}

void displayUI()
{
int i,j;
printf("check display : UI\n");
for(i=0;i<ur;i++)
{
for(j=0;j<uc;j++)
{
printf("%c ",UI[i][j]);
}
printf("\n");
}
}

void allocate(int a,int b)
{
int x,y,i,j;
x=0;y=0;
if(!(a>=0&&a<ur && b>=0&&b<uc && a+p<=ur&&b+q<=uc))
{
printf("Can't Allocate Slot\n");
return;
}
for(i=a;i<a+p;i++)
{
for(j=b;j<b+q;j++)
{
UI[i][j]=s[x][y];
y++;
}
y=0;
x++;
}
}

void display()
{
int i,j;
printf("check display : slot\n");
for(i=0;i<p;i++)
{
for(j=0;j<q;j++)
{
printf("%c ",s[i][j]);
}
printf("\n");
}
}

void allocatepark()
{
int i,j,k=0,x,indx;
int rp[8];

rp[0]=4;
rp[1]=8;
rp[2]=15;
rp[3]=19;
rp[4]=26;
rp[5]=30;
rp[6]=37;
rp[7]=41;

for(i=0;i<8;i++)
{
x=4;
indx=0;
k=(k==1)?0:1;
for(j=0;j<8;j++)
{
if(k==0&&(j%2)==0)
{
data[i][indx].r=rp[i];
data[i][indx].c=x;
data[i][indx].al=0;
data[i][indx].a=(char)('A'+i);
data[i][indx].b=(char)('0'+1+j);
indx++;
}
else if(k==1&&(j%2)==1)
{
data[i][indx].r=rp[i];
data[i][indx].c=x;
data[i][indx].al=0;
data[i][indx].a=(char)('A'+i);
data[i][indx].b=(char)('0'+1+j);
indx++;
}
//printf("check (r,c) -> (%d,%d)\t(a,b) -> (%d,%d)\n",data[i][j].r,data[i][j].c,i,j);
slot((char)('A'+i),(char)('0'+1+j),0);
allocate(rp[i],x);
x+=5;
}
}
/*
for(i=0;i<8;i++)
{
for(j=0;j<4;j++)
{
printf("check (r,c) -> (%d,%d) -> (%d,%d) %c%c \n",i,j,data[i][j].r,data[i][j].c,data[i][j].a,data[i][j].b);
}
}
*/
}

void parkUI(int a,int b,int c)
{
int xr,xc;
if(a<0||a>=8||b<0||b>=4)
{
printf("INCORRECT LOCATION !\n");
return;
}
data[a][b].al=c;
xr=data[a][b].r;
xc=data[a][b].c;
lr=data[a][b].a;
lc=data[a][b].b;
printf("check (r,c) -> (%d,%d)\t(a,b) -> (%d,%d)\tal=%d\n",xr,xc,a,b,data[a][b].al);
slot(data[a][b].a,data[a][b].b,c);
allocate(xr,xc);
writelog(1);
}

void unpark(char a,char b)
{
for(int i=0;i<8;i++)
{
for(int j=0;j<4;j++)
{
if(data[i][j].a==a && data[i][j].b==b)
{
parkUI(i,j,0);
writelog(2);
return;
}
}
}
printf("CAR MUST BE ALREADY PARKED OR WRONG PARKING SLOT IS ENTERED !\n");
}

void bestpark()
{
int i,j,k,l;
float h,md;
k=-1;
l=-1;
md=8;
for(i=0;i<8;i++)
{
for(j=0;j<4;j++)
{
h=sqrt((i*i)+(j*j));
if(data[i][j].al==0&&(h<md))
{
md=h;
k=i;
l=j;
}
}
}
if(k!=-1&&l!=-1)
{
parkUI(k,l,1);
}
else
{
printf("FULL PARKING!");
}
}

void writelog(int b)
{
char *log;
char tag[3];
FILE *f;
int i;
f=fopen(path,"a");
if(!f)
{
return;
}
log="ERROR!";
if(b==1)
{
tag[0]=lr;
tag[1]=lc;
tag[2]='\0';
log=concat("Parked at : ",tag);
lr=' ';
lc=' ';
}
else if(b==2)
{
sprintf(tag," %c%c",cm[7],cm[8]);
log=concat("Unparked from : ",tag);
}
else if(b==3)
{
log="EXIT";
}
fprintf(f,"%s\n",log);
fclose(f);
return;
}
