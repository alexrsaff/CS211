#include <stdio.h>
#include <stdlib.h>

//& obtains the address of a variable
//*obtains the value of the thing a pointer is pointing to

int main(int argc, char** argv)
{
	int size, data;
	if(argc != 2)
		return 0;
	FILE *fp;
    fp = fopen(argv[1], "r");
	if(fp==NULL)
		return 0;
	fscanf(fp, "%d", &size);
	int* array = malloc(sizeof(int)*size*size);
	int* numbers = malloc(sizeof(int)*size*size);
	for(int row_pos = 0; row_pos< size; row_pos++)
	{
		for(int col_pos = 0; col_pos< size; col_pos++)
		{
			fscanf(fp, "%d", &data);
			if(data>size*size)
			{
				printf("not-magic\n");
				free(array);
				free(numbers);
				return 0;
			}
			if(*(numbers+data-1)==1)
			{
				printf("not-magic\n");
				free(array);
				free(numbers);
				return 0;
			}
			else
				*(numbers+data-1)=1;
			*(array+(row_pos*size)+col_pos)=data;
		}
	}
	int target = 0;
	int diag_sum = 0;
	for(int row_pos = 0; row_pos< size; row_pos++)
	{
		diag_sum+=*(array+((size-row_pos-1)*size)+(size-row_pos-1));
		target+=*(array+(row_pos*size)+row_pos);
	}
	for(int row_pos = 0; row_pos< size; row_pos++)
	{
		int row_sum = 0;
		int col_sum = 0;
		for(int col_pos = 0; col_pos< size; col_pos++)
		{
			row_sum+=*(array+(row_pos*size)+col_pos);
			col_sum+=*(array+(col_pos*size)+row_pos);
		}
		if(row_sum!=target || col_sum!=target || diag_sum!=target)
		{
			printf("not-magic\n");
			free(array);
			free(numbers);
			return 0;
		}
	}
	printf("magic\n");
	fclose(fp);
	free(numbers);
	free(array);
	return 0;
}