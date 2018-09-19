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
	char action;
	int data;
	int first = 1;
	int count = 0;
    if(argc != 2)
        return 0;
    FILE *fp;
    fp = fopen(argv[1], "r");
	if(fp==NULL)
	{
		printf("error\n");
		return 0;
	}
	struct node* start = malloc(sizeof(struct node));
    while(fscanf(fp, "%c\t%d\n", &action, &data) == 2)
    {
        if(action=='i')
		{
			if(first)
			{
				count++;
				(*start).data=data;
				(*start).next=NULL;
				first = 0;
			}
			else if(inList(data, start)==0)
			{
				count++;
				start = add(data,start);
			}
		}
		else if(action=='d')
		{
			if((first ==0) && (inList(data, start)==1))
			{
				count--;
				start = delete(data,start);
			}
		}
    }
	printf("%d\n",count);
	if(count>0)
	{
		struct node* trackpoint = start;
		printf("%d", (*trackpoint).data);
		trackpoint = (*trackpoint).next;
		while(trackpoint!=NULL)
		{
			printf("\t%d",(*trackpoint).data);
			trackpoint = (*trackpoint).next;
		}
		printf("\n");
		data_cleanup(start);
	}
	else free(start);
	
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