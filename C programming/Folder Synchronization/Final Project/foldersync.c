#include <stdio.h>
#include <string.h>
#include <dirent.h>

#include "opfile.h"
#include "linkedlist.h"
#include "strutil.h"


char *src;
char *dest;
char *srca;
char *desta;

int slen;
int dlen;

int mode;
node *ptr;
linkedlist temp;

int syncf(char*,char*);

char* attach(char*,int);
char* eliminatepdir(char*);

void init(char*,char*);
void traverse(char*);
void eliminatorcommon();
void operate();

int main()
{
	char *s1;
	char *d1;
	int f;
	printf("F O L D E R    S Y N C H R O N I Z A T I O N    P R O G R A M\n");
	printf("_____________________________________________________\n");
	printf("Enter Source Directory :\n");
	s1=input();
	printf("Enter Destination Directory :\n");
	d1=input();
	printf("_____________________________________________________\n");
	f=syncf(s1,d1);
	if(f==1)
	{
		printf("SYNCHRONIZED !!!\n");
	}
	else
	{
		printf("SYNCHRONIZATION FAILED !!!\n");
	}
	return 0;
}

int syncf(char *a,char *b)
{
	if(a==NULL||b==NULL)
	{
		return 0;
	}
	else if(a[strlen(a)-1]!='/'||b[strlen(b)-1]!='/')
	{
		return 0;
	}
	else if(isdir(a)!=1||isdir(b)!=1)
	{
		return 0;
	}
	else
	{
		init(a,b);
		eliminatorcommon();
		operate();
		return 1;
	}
}

void init(char *a,char *b)
{
	initializ(4);
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

char* attach(char *a,int b)
{
	return concat((b==0)?srca:desta,a);
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

void eliminatorcommon()
{
	int stat;
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
	int stat;
	printf("_____________________________________________________\n");
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
	printf("_____________________________________________________\n");
}
