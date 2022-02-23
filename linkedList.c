#include "linkedList.h"
#include <stdlib.h>

struct node *addNode(struct node **head)
{
	struct node *newNode;
	newNode=malloc( sizeof(struct node) );

	if(*head!=NULL)
		newNode->next=*head;

	*head=newNode;
	return newNode;
}
struct node *getLastNode(struct node *head)
{
	while(head->next!=NULL)
		head=head->next;
	return head;
}

struct node * addNodeEnd(struct node *head)
{
	struct node *newNode;
	newNode=malloc( sizeof(struct node) );

	struct node *end=getLastNode(head);
	end->next=newNode;
	newNode->next=NULL;

	return newNode;
}

void removeLastNode(struct node *head)
{
	struct node *follower;
	while(!!head->next)
	{
		follower=head;
		head=head->next;
	}
	follower->next=NULL;
	free(head);
}

int terribleSearch(struct node *head,int x,int y)
{
	while(head->next!=NULL)
	{
		if(head->x==x && head->y==y)
			return 1;
		head=head->next;
	}
	return 0;
}
