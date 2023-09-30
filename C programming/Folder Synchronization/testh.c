#include <stdio.h>
#include "opfile.h"
#include "strutil.h"
#include "linkedlist.h"

void traverse(char*);

int main()
{
	char *str;
	int x;
	printf("#Testing#\n");
	printf("Enter a string\n");
	str=input();
	printf("check : %s\n",str);
	traverse("E:/Text/");
	//x=copy("E:/Text/A/G.exe","E:/Text/B/G.exe",8192);
	//printf("check : x : %d\n",x);
	
	return 0;
}

void traverse(char *n)
{
	DIR *dir;
	struct dirent *subd;
	char *dat,*s;
	int stat;
	dir=opendirectory(n);
	if(dir)
	{
		while(subd=readdir(dir))
		{
			s=subd->d_name;
			if(strcmp(s,".")==0||strcmp(s,"..")==0)
			continue;
			dat=concatdir(n,s);
			stat=isdir(dat);
			if(stat==1)
			{
				dat=concatdir(dat,"/");
				traverse(dat);
				printf("%s\n"dat);
			}
			else if(stat==0)
			{
				printf("%s\n"dat);
			}
		}
		closedir(dir);
	}
}
