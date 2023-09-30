#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "strutil.h"

void init();
char* lower(char*);
char* finput();
void display_normal();
void cbottalk();
void wordBreaker(char*,int);
int wordFinder(char*);
void searchEngine(char*);

FILE *f;

int main()
{
	init();
	cbottalk();
	//wordBreaker("Testing 1 2 3");
	//display(9);
	//printf("R=%d\n",wordFinder("Testing Account 2 3"));
	//printf("%s\n",lower("AbCdEf sdgfadsf AdskmHKHadn,b"));
	return 0;
}

void display_normal()
{
	printf("\n  Frequently Asked Questions (FAQ)");
	printf("\n\t1> Account Opening");
	printf("\n\t2> Account related query");
	printf("\n\t3> Balance related query");
	printf("\n\t4> Loan related query");
	printf("\n\t5> Offers");
	printf("\n\t6> Ask a different query");
	printf("\n\t0> EXIT\n");
}

void cbottalk()
{
	int flag =1;
	int srch=0;
	while(flag)
	{
		char *c;
		display_normal();
		printf("\nWould you like to ask a FAQ? (Y/N)\t");
		c=input();
		if(c[0]=='y'||c[0]=='Y')
		{
			printf("\nWhich FAQ would you like to ask?\t");
			c=input();
			if(c[0]>='1'&&c[0]<='5')
			{
				display(c[0]-'0'-1);
			}
			else if(c[0]=='6')
			{
				printf("Enter query\n");
				c=input();
				srch=wordFinder(c);
				if(srch==0)
				{
					printf("Couldn't find your query\n");
				}
			}
			else if(c[0]=='0')
			{
				printf("EXIT\n");
				break;
			}
			else
			{
				printf("Wring choice\n");
			}
			
			
			
		}
		else
		{
			printf("EXIT\n");
			break;
			
		}
	}
}

// DATA Search & Printing
void init()
{
	int l,indx;
	char *tmp;
	//f=fopen(fname,"r");
	initializ(10);
	//File data1
	char fname[9]="data .txt";
	for(int i=1;i<=5;i++)
	{
		fname[4]=(char)(48+i);
		f=fopen(fname,"r");
		while(tmp=finput())
		{
			queue(i-1,tmp);
		}
		fclose(f);
	}
	f=fopen("keyword.txt","r");
	while(tmp=finput())
	{
		queue(7,lower(tmp));
	}
	fclose(f);
	f=fopen("data6.txt","r");
	while(tmp=finput())
	{
		l=strlen(tmp);
		if(l!=0)
		{
			//printf("%s\n",tmp);
			indx=indexof(tmp,'@');
			if(indx==0)
			{
				tmp=substring(tmp,1,l);
				queue(5,tmp);
			}
			indx=indexof(tmp,'#');
			if(indx==0)
			{
				tmp=substring(tmp,1,l);
				queue(6,tmp);
			}
		}
	}
	fclose(f);
}

void wordBreaker(char *a,int b)
{
	int l,i,pre;
	reset(b);
	l=strlen(a);
	if(a[l-1]!=' ')
	{
		char *sp=(char*)malloc(2*sizeof(char));
		sp[0]=' ';
		sp[1]='\0';
		a=concat(a,sp);
		l++;
	}
	pre=0;
	for(i=0;i<l;i++)
	{
		if(a[i]==' ')
		{
			if(pre>=i)
			{
				continue;
			}
			char *w=substring(a,pre,i);
			queue(b,lower(w));
			pre=i+1;
		}
	}
}

int wordFinder(char *sen)
{
	node *k,*v;
	k=list[5].head;
	v=list[6].head;
	sen=lower(sen);
	while(k!=NULL)
	{
		if(equals(sen,lower(k->str))==1)
		{
			printf("_________________________________________________________________________\n");
			printf("%s\n",k->str);
			printf("%s\n",v->str);
			printf("_________________________________________________________________________\n");
			return 1;
		}
		k=k->next;
		v=v->next;
	}
	wordBreaker(sen,9);
	node *p;
	char *w;
	if(list[9].head==NULL)
	{
		return 0;
	}
	for(p=list[9].head;p!=NULL;p=p->next)
	{
		w=lower(p->str);
		if(search(7,w)==1)
		{
			searchEngine(w);
			return 1;
		}
	}
	return 0;
}

void searchEngine(char *w)
{
	node *k,*v;
	k=list[5].head;
	v=list[6].head;
	while(k!=NULL)
	{
		wordBreaker(k->str,8);
		//display(8);
		if(search(8,w)==1)
		{
			printf("_________________________________________________________________________\n");
			printf("%s\n",k->str);
			printf("%s\n",v->str);
			printf("_________________________________________________________________________\n");
		}
		k=k->next;
		v=v->next;
	}
}

char* lower(char *a)
{
	int i,l;
	char *ab;
	ab=(char*)malloc((l+1)*sizeof(char));
	l=strlen(a);
	for(i=0;i<l;i++)
	{
		ab[i]=(a[i]>='A'&&a[i]<='Z')?(char)(a[i]+32):a[i];
	}
	ab[l]='\0';
	return ab;
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
