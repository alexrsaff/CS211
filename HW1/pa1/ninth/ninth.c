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

struct node* delete(int, struct node*);

int main(int argc, char** argv)
{
	if(argc != 2)
		return 0;
	int data;
	char action;
	struct node* start;
	start = NULL;
	FILE *fp;
    fp = fopen(argv[1], "r");
	if(fp==NULL)
	{
		printf("error\n");
		return 0;
	}
	while(fscanf(fp, "%c\t%d\n", &action, &data) == 2)
    {
		//printf("DATA: %d  |  COMMAND: %c\n",data, action);
        if(action=='i')
		{
			if(inTree(data, start)==-1)
			{
				start = add(data,start);
				printf("inserted %d\n", inTree(data,start));
				//printf("DATA: %d\n",(*start).data);
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
		else if(action=='d')
		{
			if((inTree(data, start)==-1))
				printf("fail\n");
			else
			{
				start = delete(data, start);
				printf("success\n");
			}
		}
		//printf("START: %d\n",(*start).data);
    }
	//printf("DONE?\n");
	data_cleanup(start);
	return 0;
}

int inTree(int data, struct node* start)
{
	if(start==NULL)
		return -1;
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
	if(start==NULL)
	{
		struct node* start = malloc(sizeof(struct node));
		(*start).data = data;
		(*start).right = NULL;
		(*start).left = NULL;
		return start;
	}
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
	//printf("FREEING: %d\n",(*start).data);
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
		free(start);
	return;
}

struct node* delete(int data, struct node* start)
{
	struct node* current = start;
	struct node* previous = start;
	int nodeData = (*start).data;
	//find node to delete
	while(nodeData!=data)
	{
		previous=current;
		if(data<(*current).data)
			current = (*current).left;
		else if(data>(*current).data)
			current = (*current).right;
		nodeData = (*current).data;
	}
	//printf("CURRENT: %d  |  PREVIOUS: %d\n",(*current).data, (*previous).data);
	//if it is leaf node
	if((*current).right == NULL && (*current).left==NULL)
	{
		if(data<(*previous).data)
		{
			(*previous).left=NULL;
			free(current);
		}
		else if(data>(*previous).data)
		{
			(*previous).right=NULL;
			free(current);
		}
		else if (start==current)
		{
			free(start);
			start = NULL;
		}
		return start;
	}
	//if it only has right child
	if((*current).left==NULL)
	{
		if(data<(*previous).data)
			(*previous).left=(*current).right;
		else if(data>(*previous).data)
			(*previous).right=(*current).right;
		else if (start==current)
			start = (*current).right;
		free(current);
		return start;
	}
	//if it only has left child
	if((*current).right==NULL)
	{
		if(data<(*previous).data)
			(*previous).left=(*current).left;
		else if(data>(*previous).data)
			(*previous).right=(*current).left;
		else if (start==current)
			start = (*current).left;
		free(current);
		return start;
	}
	//if it has two children
	if((*current).right!=NULL && (*current).left!=NULL)
	{
		struct node* replacement = (*current).right;
		struct node* replacementPrevious = current;
		while((*replacement).left!=NULL)
		{
			replacementPrevious = replacement;
			replacement = (*replacement).left;
		}
		//printf("REPLACEMENT: %d  |  PREV REPLACEMENT: %d  |  CURRENT:%d\n",(*replacement).data,(*replacementPrevious).data,(*current).data);	
		(*current).data = (*replacement).data;
		if(current == replacementPrevious)
		{
			(*replacementPrevious).right = (*replacement).right;
		}
		else
			(*replacementPrevious).left = (*replacement).right;
		free(replacement);
		return start;
	}
	return NULL;
}