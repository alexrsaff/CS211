#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 10000
//& obtains the address of a variable
//*obtains the value of the thing a pointer is pointing to
//www.pythontutor.com is useful
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
	int key;
	 if(argc != 2)
        return 0;
	struct node* table[LENGTH];
	memset(table,0,sizeof(table));
	FILE *fp;
    fp = fopen(argv[1], "r");
	if(fp==NULL)
	{
		printf("error\n");
		return 0;
	}
	int data;
	struct node* start;
	 while(fscanf(fp, "%c\t%d\n", &action, &data) == 2)
    {
		//printf("COMMAND: %c  |  DATA: %d\n", action,data);
		key = data%LENGTH;
		if(key<0)
			key=key*-1;
		start = table[key];
		//printf("DATA: %d  |  KEY: %d\n",data,key);
        if(action=='i')//add
		{
			if(start == NULL)
			{
				table[key] = malloc(sizeof(struct node));
				(*table[key]).data = data;
				(*table[key]).next = NULL;
				printf("inserted\n");
			}
			else if (inList(data,start)==0)
			{
				start=add(data,start);
				printf("inserted\n");
			}
			else if(inList(data,start)==1)
				printf("duplicate\n");
		}
		else if(action=='s')//lookup
		{
			if(inList(data,start)==1)
				printf("present\n");
			else if(inList(data,start)==0)
				printf("absent\n");
		}
		//printf("AT END\n");
    }
	//printf("\nCLEANING...\n");
	for(int count = 0; count < LENGTH; count++)
		if(table[count]!=NULL)
			data_cleanup(table[count]);
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