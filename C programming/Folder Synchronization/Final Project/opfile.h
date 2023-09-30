#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

DIR* opendirectory(char*);
int isdir(char*);
int copy(char*,char*,int);
void deletedir(char*);
char* concatdir(char*,char*);

DIR* opendirectory(char *n)
{
	int i,l;
	l=strlen(n);
	char arr[l+1];
	for(i=0;i<l;i++)
	{
		arr[i]=n[i];
	}
	arr[l]='\0';
	return opendir(arr);
}

int isdir(char *name)
{
	DIR *dir;
	dir=opendirectory(name);
	if(dir!=NULL)
	{
		closedir(dir);
		return 1;
	}
	if(errno == ENOTDIR)
	{
		return 0;
	}
	return -1;
}

int copy(char *s,char *d,int b)
{
	FILE *src,*dest;
	int x,bfr,stat,i;
	if(isdir(s)!=0&&isdir(d)!=0)
	return 0;
	x=1;
	bfr=b;
	unsigned char data[bfr];
	src=fopen(s,"rb");
	dest=fopen(d,"wb+");
	while(1)
	{
		stat=fread(data,1,bfr,src);
		if(stat==0)
		{
			break;
		}
		else if(stat==-1)
		{
			x=0;
			break;
		}
		stat=fwrite(data,1,stat,dest);
		if(stat==-1)
		{
			x=0;
			break;
		}
	}
	fclose(src);
	fclose(dest);
	return x;
}

void deletedir(char *name)
{
	DIR *dir;
	struct dirent *subd;
	char *a,*t;
	if(isdir(name)==0)
	{
		remove(name);
	}
	else if(isdir(name)==1)
	{
		dir=opendirectory(name);
		while(subd=readdir(dir))
		{
			a=subd->d_name;
			if(strcmp(a,".")==0||strcmp(a,"..")==0)
			{
				continue;
			}
			t=concatdir(name,a);
			t=(isdir(t)==1)?concatdir(t,"/"):t;
			deletedir(t);
		}
		closedir(dir);
		rmdir(name);
	}
}

char* concatdir(char *a,char *b)
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
	if(isdir(ab)==1)
	{
		l=strlen(ab);
		a=ab;
		ab=NULL;
		ab=(char*)malloc((l+2)*sizeof(char));
		for(i=0;i<l;i++)
		{
			ab[i]=a[i];
		}
		ab[i++]='/';
		ab[i]='\0';
	}
	return ab;
}
