#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//& obtains the address of a variable
//*obtains the value of the thing a pointer is pointing to

struct node
{
	int data;
	struct node* left;
	struct node* right;
};

int inTree(int, struct node*);

struct node* add(int, struct node*);

void data_cleanup(struct node*);

int treeHeight(struct node*);

int main(int argc, char** argv)
{
	if(argc != 2)
		return 0;
	//printf("MAIN\n");
	int data;
	char action;
	int first =1;
	struct node* start = malloc(sizeof(struct node));
	// (*start).data = 23;
	(*start).left = NULL;
	(*start).right = NULL;
	// printf("inserted %d\n", inTree(23,start));
	// start = add(4, start);
	// printf("inserted %d\n", inTree(4,start));
	// start = add(-5, start);
	// printf("inserted %d\n", inTree(-5,start));
	// start = add(9, start);
	// printf("inserted %d\n", inTree(9,start));
	FILE *fp;
    fp = fopen(argv[1], "r");
	if(fp==NULL)
	{
		printf("error\n");
		return 0;
	}
	while(fscanf(fp, "%c\t%d\n", &action, &data) == 2)
    {
		//printf("DATA: %d, COMMAND: %c\n", data, action);
        if(action=='i')
		{
			if(first)
			{
				(*start).data=data;
				(*start).right = NULL;
				(*start).left = NULL;
				first = 0;
				printf("inserted %d\n", inTree(data,start));
			}
			else if(inTree(data, start)==-1)
			{
				start = add(data,start);
				printf("inserted %d\n", inTree(data,start));
			}
			else if(inTree(data, start)!=-1)
				printf("duplicate\n");
		}
		else if(action=='s')
		{
			if((inTree(data, start)!=-1))
				printf("present %d\n",(inTree(data, start)));
			else
				printf("absent\n");
		}
    }
	data_cleanup(start);
	return 0;
}

int inTree(int data, struct node* start)
{
	if((*start).data==data)
		return 1;
	if((*start).right==NULL && (*start).left==NULL)
		return -1;
	if(data<(*start).data)
	{
		if((*start).left==NULL)
			return -1;
		if(inTree(data,(*start).left)==-1)
			return -1;
		return 1 + inTree(data,(*start).left);
	}
	if(data>(*start).data)
	{
		if((*start).right==NULL)
			return -1;
		if(inTree(data,(*start).right)==-1)
			return -1;
		return 1 + inTree(data,(*start).right);
	}
	return -100;
}

struct node* add(int data, struct node* start)
{
	if(data<(*start).data)
	{
		if((*start).left==NULL)
		{
			(*start).left=malloc(sizeof(struct node));
			(*(*start).left).left=NULL;
			(*(*start).left).right=NULL;
			(*(*start).left).data=data;
		}
		else
			(*start).left = add(data,(*start).left);
	}
	else if(data>(*start).data)
	{
		if((*start).right==NULL)
		{
			(*start).right=malloc(sizeof(struct node));
			(*(*start).right).left=NULL;
			(*(*start).right).right=NULL;
			(*(*start).right).data=data;
		}
		else
			(*start).right = add(data,(*start).right);
	}
	return start;
}

void data_cleanup(struct node* start)
{
	if(start==NULL)
	{
		free(start);
		return;
	}
	if((*start).right!=NULL)
	{
		data_cleanup((*start).right);
		(*start).right=NULL;
	}
	if((*start).left!=NULL)
	{
		data_cleanup((*start).left);
		(*start).left=NULL;
	}
	if((*start).right==NULL && (*start).left==NULL)
	{
		//printf("Freeing: %d\n", (*start).data);
		free(start);
	}
	return;
}