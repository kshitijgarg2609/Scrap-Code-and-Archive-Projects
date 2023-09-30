#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutil.h"

typedef struct words
{
	int len;
	char *arr;
} words;
words qu[30];
int order[] = {9,1,3,4,5,6,25,19,20,7,8,21,22,23,24};

char* parserFunction(char*);

char* parserFunction(char *in)
{
	int cnt=0;
	int len=sizeof(in)/sizeof(char);
	char *token = strtok(in, ",");
	while (token != NULL)
    {
		int n=strlen(token);
        qu[cnt].arr=(char*)malloc((n+1)*sizeof(char));
		for(int i=0;i<n;i++)
		{
			qu[cnt].arr[i]=token[i];
		}
		qu[cnt].arr[n]='\0';
		qu[cnt].len=n;
		cnt++;
        token = strtok(NULL, ",");
    }
	char *comma;
	comma=(char*)malloc(2*sizeof(char));
	comma[0]=',';
	comma[1]='\0';
	char *res = qu[order[0]].arr;
	for(int i=1;i<15;i++)
	{
		res=concat(res,comma);
		if(order[i]<cnt && qu[order[i]].len>0)
		{
			res=concat(res,qu[order[i]].arr);
		}
	}
	return res;
}

int main()
{
	printf("Enter a string\n");
	char *inputStr = input();
	char * outputStr = parserFunction(inputStr);
	printf("output string is : %s ", outputStr);
	return 0;
}
	