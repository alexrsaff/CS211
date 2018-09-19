#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//& obtains the address of a vairable
//*obtains the value of the thing a pointer is pointing to
//www.pythontutor.com is useful
struct node
{
	float data;
	struct node* next;
};

int inList(float, struct node*);

struct node* add(float, struct node*);

struct node* delete(float, struct node*);

void data_cleanup(struct node*);

int main(int argc, char** argv)
{
	 if(argc != 2)
        return 0;
	struct node* table[10000];
	memset(table,0,sizeof(table));
	printf("LINE 25\n");
	FILE *fp;
    fp = fopen(argv[1], "r");
	if(fp==NULL)
	{
		printf("error\n");
		return 0;
	}
	return 0;
}

int inList(float data, struct node* start)
{
	struct node* currpoint = start;
	while(currpoint!=NULL)
	{
		if((*currpoint).data==data)
			return 1;
		currpoint = (*currpoint).next;
	}
	return 0;
}

struct node* add(float data, struct node* start)
{
	struct node* currpoint = start;
	struct node* prevpoint = currpoint;
	while(currpoint!=NULL && (*currpoint).data<data)
	{
		prevpoint = currpoint;
		currpoint = (*currpoint).next;
	}
	if(currpoint==start)
	{
		struct node* first = malloc(sizeof(struct node));
		(*first).data=data;
		(*first).next=currpoint;
		return first;
	}
	(*prevpoint).next=malloc(sizeof(struct node));
	prevpoint = (*prevpoint).next;
	(*prevpoint).next = currpoint;
	(*prevpoint).data = data;
	return start;
}

struct node* delete(float data, struct node* start)
{
	struct node* currpoint = start;
	struct node* prevpoint = currpoint;
	while(currpoint!=NULL && (*currpoint).data!=data)
	{
		prevpoint = currpoint;
		currpoint = (*currpoint).next;
	}
	if(currpoint==start)
	{
		start=(*currpoint).next;
		free(currpoint);
		return start;
	}
	(*prevpoint).next = (*currpoint).next;
	free(currpoint);
	return start;
}

void data_cleanup(struct node* start)
{
	if(start==NULL)
		return;
	while((*start).next!=NULL)
	{
		struct node* currpoint = start;
		struct node* prevpoint = start;
		while((*currpoint).next!=NULL)
		{
			prevpoint=currpoint;
			currpoint = (*currpoint).next;
		}
		free(currpoint);
		(*prevpoint).next=NULL;
	}
	free(start);
	return;
}