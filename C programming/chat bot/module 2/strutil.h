#include <string.h>
#include <stdlib.h>

char* input()
{	
	char x,*y;	
	char arr[1024];
	int i,s;
	i=0;
	while(x=getchar())
	{	
		if(x=='\n'||x==EOF)
		{	
			break;	
		}
		arr[i++]=x;
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

char* concat(char *a,char *b)
{
	int la,lb,loc,i,l;
	char *ab;
	la=strlen(a);
	lb=strlen(b);
	l=la+lb;
	loc=0;
	ab=(char*)malloc((l+1)*sizeof(char));
	for(i=0;i<la;i++)
	{
		ab[loc++]=a[i];
	}
	for(i=0;i<lb;i++)
	{
		ab[loc++]=b[i];
	}
	ab[loc]='\0';
	return ab;
}

char* substring(char *a,int b,int c)
{
	int l,n,i;
	char *subs;
	l=strlen(a);
	n=c-b;
	if(!((n>0)&&(b>=0&&b<l)&&(c>0&&c<=l)))
	{
		return NULL;
	}
	subs=(char*)malloc((n+1)*sizeof(char));
	for(i=0;i<n;i++)
	{
		subs[i]=a[b++];
	}
	subs[i]='\0';
	return subs;
}

int indexof(char *a,char b)
{
	int i;
	for(i=0;i<strlen(a);i++)
	{
		if(a[i]==b)
		{
			return i;
		}
	}
	return -1;
}

int lastindexof(char *a,char b)
{
	int i;
	for(i=strlen(a)-1;i>=0;i--)
	{
		if(a[i]==b)
		{
			return i;
		}
	}
	return -1;
}

int equals(char *a,char*b)
{
	int x,i,l;
	x=1;
	l=(strlen(a)<=strlen(b))?strlen(a):strlen(b);
	for(i=0;i<l;i++)
	{
		if(a[i]!=b[i])
		{
			return 0;
		}
	}
	return x;
}
