#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkRow(int**, int, int);//arrayptr, row, data

int checkColumn(int**, int, int);//arrayptr, column, data

int checkBox(int**, int, int, int);//arrayptr, row, column, data

int solve(int**);

int main(int argc, char** argv)
{
	//===============================read in file===============================
	if(argc != 2)
    {
        printf("Not enough arguments\n");
        return 0;
    }
    FILE *fp = fopen(argv[1],"r");
	int size = 9;
	int* array = malloc(sizeof(int)*size*size);
	for(int row = 0; row<size; row++)
	{
		for(int column = 0; column<size; column++)
		{
			char data;
            fscanf(fp,"%c\t",&data);
			if(data=='-')
				*(array+row*(size)+column) = 0;
			else
				*(array+row*(size)+column) = data - '0';
		}
	}
	//===============================solve===============================
	if(solve(&array)==0)
	{
		printf("no-solution\n");
		return 0;
	}
	//===============================print===============================
	for(int row = 0; row<size; row++)
	{
		for(int column = 0; column<size; column++)
		{
			printf("%d\t", *(array+row*(size)+column));
		}
		printf("\n");
	}
	free(array);
	return 0;
}

int checkRow(int** arrayptr, int row, int data)
{
	int* array = *arrayptr;
	int size = 9;
	for(int column = 0; column< size; column++)
	{
		if(*(array+row*(size)+column)==data)
			return 0;
	}
	return 1;
}

int checkColumn(int** arrayptr, int column, int data)
{
	int* array = *arrayptr;
	int size = 9;
	for(int row = 0; row< size; row++)
	{
		if(*(array+row*(size)+column)==data)
			return 0;
	}
	return 1;
}

int checkBox(int** arrayptr, int row, int column, int data)
{
	int* array = *arrayptr;
	int size = 9, rowmin, rowmax, colmin, colmax;
	if(row==0 || row==3 || row==6)
	{
		rowmin = row;
		rowmax = row+2;
	}
	else if(row==1 || row==4 || row==7)
	{
		rowmin = row-1;
		rowmax = row+1;
	}
	else if(row==2 || row==5 || row==8)
	{
		rowmin = row-2;
		rowmax = row;
	}
	if(column==0 || column==3 || column==6)
	{
		colmin = column;
		colmax = column+2;
	}
	else if(column==1 || column==4 || column==7)
	{
		colmin = column-1;
		colmax = column+1;
	}
	else if(column==2 || column==5 || column==8)
	{
		colmin = column-2;
		colmax = column;
	}
	for(int rownum = rowmin; rownum<=rowmax; rownum++)
	{
		for(int colnum = colmin; colnum<=colmax; colnum++)
		{
			if(*(array+rownum*(size)+colnum)==data)
				return 0;
		}
	}
	return 1;
}

int solve(int** arrayptr)
{
	int size = 9;
	int* arrayorig = *arrayptr;
	int* array = malloc(sizeof(int)*size*size);
	memcpy(array,arrayorig,sizeof(int)*size*size);
	int row = 0, column = 0, found = 0;
	for(;row<size;row++)
	{
		for(column=0;column<size;column++)
		{
			if(*(array+row*(size)+column)==0)
			{
				found = 1;
				break;
			}
		}
		if(found == 1)
			break;
	}
	if(row==size && column ==size)
	{
		free(array);
		return 1;
	}
	for(int number =1; number<=size;number++)
	{
		if(checkRow(&array,row,number)==1 && checkColumn(&array,column,number)==1 && checkBox(&array,row,column,number)==1)
		{
			*(array+row*(size)+column)=number;
			if(solve(&array)==1)
			{
				memcpy(arrayorig,array,sizeof(int)*size*size);
				free(array);
				return 1;
			}
		}
	}
	free(array);
	return 0;
}