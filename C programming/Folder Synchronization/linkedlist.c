#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	char *str;
	struct node *next;
	}node;
	
	node *head=NULL;
	node *current=NULL;
	
	void display()
	{
		if(head==NULL)
		{
			printf("Empty List!\n");
			return;
		}
		node *ptr;
		for(ptr=head;ptr!=NULL;ptr=ptr->next)
		{
			printf("%s\n",ptr->str);
		}
	}
	
	int search(char *data)
	{
		node *ptr;
		for(ptr=head;ptr!=NULL;ptr=ptr->next)
		{
			if(strcmp(data,ptr->str)==0)
			{
				return 1;
			}
		}
		return 0;
	}
	
	int searchfrom(node *n,char *data)
	{
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
	
	void stack(char *data)
	{
		node *newnode=(struct node*)malloc(sizeof(node));
		newnode->str=data;
		if(head==NULL)
		{
			head=newnode;
			newnode->next=NULL;
			current=head;
			return;
		}
		newnode->next=head;
		head=newnode;
	}
	
	void queue(char *data)
	{
		node *newnode=(struct node*)malloc(sizeof(node));
		newnode->str=data;
		newnode->next=NULL;
		if(head==NULL)
		{
			head=newnode;
			current=head;
			return;
		}
		current->next=newnode;
		current=current->next;
	}
	
	void delete(char *data)
	{
		node *ptr;
		node *prev;
		for(ptr=head;ptr!=NULL;prev=ptr,ptr=ptr->next)
		{
			if(ptr->str==data)
			{
				if(ptr==head)
				{
					head=head->next;
					current=head==NULL?NULL:current;
				}
				else if(ptr->next==NULL)
				{
					prev->next=NULL;
					current=prev;
				}
				else
				{
					prev->next=ptr->next;
				}
				return;
			}
		}
		printf("Data not Found !");
	}
	
	void deletefrom(node *n,char *data)
	{
		node *ptr;
		node *prev;
		for(ptr=n;ptr!=NULL;prev=ptr,ptr=ptr->next)
		{
			if(ptr->str==data)
			{
				if(ptr==head)
				{
					head=head->next;
					current=head==NULL?NULL:current;
				}
				else if(ptr->next==NULL)
				{
					prev->next=NULL;
					current=prev;
				}
				else
				{
					prev->next=ptr->next;
				}
				return;
			}
		}
		printf("Data not Found !\n");
	}
	
	int main()
	{
		node *temp;
		queue("Testing 1");
		queue("Testing 2");
		temp=current;
		queue("Testing 3");
		//stack("Testing 4");
		queue("Testing 5");
		deletefrom(temp,"Testing 3");
		printf("Searching : Testing 5 : %d\n",searchfrom(temp,"Testing 5"));
		display();
		printf("check : %s\n",temp->str);
		printf("program compiled succesfully!\n");
		return 0;
	}
