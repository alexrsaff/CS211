#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node* next;
};

int inList(int, struct node*);

struct node* add(int, struct node*);

struct node* delete(int, struct node*);

void data_cleanup(struct node*);

int main(int argc, char** argv)
{
	struct node* first = malloc(sizeof(struct node));
	(*first).data=0;
	(*first).next=NULL;
	first = add(5,first);
	first = add(4,first);
	first = add(3,first);
	first = add(2,first);
	first = add(-1,first);
	printf("=======================\n");
	struct node* trackpoint = first;
	while(trackpoint!=NULL)
	{
		printf("Address:%p   Data:%d   Points to:%p\n",trackpoint,(*trackpoint).data,(*trackpoint).next);
		trackpoint = (*trackpoint).next;
	}
	//first = delete(1,first);
	//first = delete(0,first);
	//first = delete(5,first);
	printf("=======================\n");
	trackpoint = first;
	while(trackpoint!=NULL)
	{
		printf("Address:%p   Data:%d   Points to:%p\n",trackpoint,(*trackpoint).data,(*trackpoint).next);
		trackpoint = (*trackpoint).next;
	}
	data_cleanup(first);
	return 0;
}

int inList(int data, struct node* start)
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

struct node* add(int data, struct node* start)
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

struct node* delete(int data, struct node* start)
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