#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "strutil.h"

char *path="log.txt";

typedef struct data
{
	int r,c,al;
}park;

int p=3;
int q=5;
int ur=26;
int uc=44;
int lr=-1;
int lc=-1;
char s[3][5];
char UI[26][44];
park data[4][8];

char *cm;

void slot1(char,char,int);
void slot2(char,char,int);
void reset();
void displayUI();
void allocate(int,int);
void display();
void allocatepark();
void parkUI(int,int,int);
void bestpark();
void writelog(int);

int main()
{
	char r,c;
	int f,l;
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
			if(lr!=-1&&lc!=-1)
			{
				writelog(1);
			}
		}
		else if(strlen(cm)==9)
		{
			f=cm[7]-'a';
			l=cm[8]-'1';
			if((f>=0&&f<4)&&(l>=0&&l<8)&&data[f][l].al==1)
			{
				parkUI(f,l,0);
				writelog(2);
			}
			else
			{
				printf("CAR MUST BE ALREADY PARKED OR WRONG PARKING SLOT IS ENTERED !\n");
			}
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

void slot1(char a,char b,int c)
{
	int i,j;
	for(i=0;i<p;i++)
	{
		for(j=0;j<q;j++)
		{
			s[i][j]=((j==0)||(j==q-1))?'|':((i==p-1)?'_':' ');
		}
	}
	s[1][1]=a;
	s[1][2]=b;
	s[1][3]=(c==1)?'*':' ';
}

void slot2(char a,char b,int c)
{
	int i,j;
	for(i=0;i<p;i++)
	{
		for(j=0;j<q;j++)
		{
			s[i][j]=((j==0)||(j==q-1))?'|':((i==0)?'-':' ');
		}
	}
	s[1][1]=a;
	s[1][2]=b;
	s[1][3]=(c==1)?'*':' ';
}

void reset()
{
	int i,j;
	for(i=0;i<p;i++)
	{
		for(j=0;j<q;j++)
		{
			UI[i][j]=' ';
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
	int i,j,x;
	int rp[4];
	rp[0]=4;
	rp[1]=8;
	rp[2]=15;
	rp[3]=19;
	for(i=0;i<4;i++)
	{
		x=4;
		for(j=0;j<8;j++)
		{
			data[i][j].r=rp[i];
			data[i][j].c=x;
			data[i][j].al=0;
			printf("check (r,c) -> (%d,%d)\t(a,b) -> (%d,%d)\n",data[i][j].r,data[i][j].c,i,j);
			if((i%2)==0)
			{
				slot1((char)('A'+i),(char)('0'+1+j),0);
				allocate(rp[i],x);
			}
			else
			{
				slot2((char)('A'+i),(char)('0'+1+j),0);
				allocate(rp[i],x);
			}
			x+=5;
		}
	}
}

void parkUI(int a,int b,int c)
{
	int xr,xc;
	if(a<0||a>=4||b<0||a>=8)
	{
		printf("INCORRECT LOCATION !\n");
		return;
	}
	data[a][b].al=c;
	xr=data[a][b].r;
	xc=data[a][b].c;
	printf("check (r,c) -> (%d,%d)\t(a,b) -> (%d,%d)\tal=%d\n",xr,xc,a,b,data[a][b].al);
	if((a%2)==0)
	{
		slot1((char)('A'+a),(char)('0'+b+1),c);
		allocate(xr,xc);
	}
	else
	{
		slot2((char)('A'+a),(char)('0'+b+1),c);
		allocate(xr,xc);
	}
}

void bestpark()
{
	int i,j,k,l;
	float h,md;
	k=-1;
	l=-1;
	md=8;
	for(i=0;i<4;i++)
	{
		for(j=0;j<8;j++)
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
		lr=k;
		lc=l;
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
		sprintf(tag," %c%c",(char)(lr+'A'),(char)(lc+'0'+1));
		log=concat("Parked at : ",tag);
		lr=-1;
		lc=-1;
	}
	else if(b==2)
	{
		sprintf(tag," %c%c",(char)(cm[7]-32),cm[8]);
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
