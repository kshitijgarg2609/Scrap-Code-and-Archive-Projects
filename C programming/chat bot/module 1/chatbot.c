#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "strutil.h"

void init();
char* finput();

FILE *f;

int main()
{
	init();
	fclose(f);
	return 0;
}

void init()
{
	int l,indx;
	char *tmp;
	f=fopen("data.txt","r");
	initializ(2);
	while(tmp=finput())
	{
		printf("%s\n",tmp);
		l=strlen(tmp);
		if(l!=0)
		{
			indx=indexof(tmp,'@');
			if(indx==0)
			{
				tmp=substring(tmp,1,l);
				queue(0,tmp);
			}
			indx=indexof(tmp,'#');
			if(indx==0)
			{
				tmp=substring(tmp,1,l);
				queue(1,tmp);
			}
		}
	}
	//testing
	printf("Printing list 1\n");
	display(0);
	printf("Printing list 2\n");
	display(1);
}

char* finput()
{
	char x,*y;
	char arr[1024];
	int i,s;
	i=0;
	while(x=fgetc(f))
	{
		if(x=='\n')
		{
			break;
		}
		arr[i++]=x;
		if(x==EOF)
		{
			return NULL;
		}
	}
	s=i;
	y=(char*)malloc((i+1)*sizeof(char));
	i--;
	while(i>=0)
	{
		y[i]=arr[i];
		i--;
	}
	y[s]='\0';
	return y;
}
