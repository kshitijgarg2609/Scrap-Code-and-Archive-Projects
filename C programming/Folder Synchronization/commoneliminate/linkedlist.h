#include <stdlib.h>
#include <string.h>

//Structures

int size;

typedef struct node
{
char *str;
struct node *next;
}node;

typedef struct linkedlist
{
node *head;
node *current;
}linkedlist;

linkedlist *list;

//Function Definition
void initializ(int);
void format();
void reset(int);
void resetall();
void display(int);
int search(int,char*);
int searchfrom(int,node*,char*);
void stack(int,char*);
void queue(int,char*);
int delete(int,char*);
int deletefrom(int,node*,char*);

//Functions

void initializ(int a)
{
if(a<=0)
{
printf("LINKED LIST UNALLOCATED\n",a);
return;
}
list=(linkedlist*)malloc(a*sizeof(linkedlist));
size=a;
resetall();
}

void format()
{
size=0;
list=NULL;
}

void reset(int a)
{
if(!(a>=0&&a<size))
{
printf("LIST NUMBER : %d DOES NOT EXISTS\n",a);
return;
}
list[a].head=NULL;
list[a].current=NULL;
}

void resetall()
{
int i;
for(i=0;i<size;i++)
{
reset(i);
}
}

void display(int a)
{
if(!(a>=0&&a<size))
{
printf("LIST NUMBER : %d DOES NOT EXISTS\n",a);
return;
}
node *ptr;
if(list[a].head==NULL)
{
printf("Empty List!\n");
return;
}
for(ptr=list[a].head;ptr!=NULL;ptr=ptr->next)
{
printf("%s\n",ptr->str);
}
}

int search(int a,char *data)
{
if(!(a>=0&&a<size))
{
printf("LIST NUMBER : %d DOES NOT EXISTS\n",a);
return -1;
}
node *ptr;
for(ptr=list[a].head;ptr!=NULL;ptr=ptr->next)
{
if(strcmp(data,ptr->str)==0)
{
return 1;
}
}
return 0;
}

int searchfrom(int a,node *n,char *data)
{
if(!(a>=0&&a<size))
{
printf("LIST NUMBER : %d DOES NOT EXISTS\n",a);
return -1;
}
node *ptr;
for(ptr=n;ptr!=NULL;ptr=ptr->next)
{
if(strcmp(data,ptr->str)==0)
{
return 1;
}
}
return 0;
}

void stack(int a,char *data)
{
if(!(a>=0&&a<size))
{
printf("LIST NUMBER : %d DOES NOT EXISTS\n",a);
return;
}
node *newnode=(struct node*)malloc(sizeof(node));
newnode->str=data;
if(list[a].head==NULL)
{
list[a].head=newnode;
newnode->next=NULL;
list[a].current=list[a].head;
return;
}
newnode->next=list[a].head;
list[a].head=newnode;
}

void queue(int a,char *data)
{
if(!(a>=0&&a<size))
{
printf("LIST NUMBER : %d DOES NOT EXISTS\n",a);
return;
}
node *newnode=(struct node*)malloc(sizeof(node));
newnode->str=data;
newnode->next=NULL;
if(list[a].head==NULL)
{
list[a].head=newnode;
list[a].current=list[a].head;
return;
}
list[a].current->next=newnode;
list[a].current=list[a].current->next;
}

int delete(int a,char *data)
{
if(!(a>=0&&a<size))
{
printf("LIST NUMBER : %d DOES NOT EXISTS\n",a);
return -1;
}
node *ptr;
node *prev;
for(ptr=list[a].head;ptr!=NULL;prev=ptr,ptr=ptr->next)
{
if(strcmp(ptr->str,data)==0)
{
if(ptr==list[a].head)
{
list[a].head=list[a].head->next;
list[a].current=(list[a].head==NULL)?NULL:list[a].current;
}
else if(ptr->next==NULL)
{
prev->next=NULL;
list[a].current=prev;
}
else
{
prev->next=ptr->next;
}
return 1;
}
}
return 0;
}

int deletefrom(int a,node *n,char *data)
{
if(!(a>=0&&a<size))
{
printf("LIST NUMBER : %d DOES NOT EXISTS\n",a);
return -1;
}
node *ptr;
node *prev;
for(ptr=n;ptr!=NULL;prev=ptr,ptr=ptr->next)
{
if(strcmp(ptr->str,data)==0)
{
if(ptr==list[a].head)
{
list[a].head=list[a].head->next;
list[a].current=(list[a].head==NULL)?NULL:list[a].current;
}
else if(ptr->next==NULL)
{
prev->next=NULL;
list[a].current=prev;
}
else
{
prev->next=ptr->next;
}
return 1;
}
}
return 0;
}