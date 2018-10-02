#include <stdio.h>
#include <stdlib.h>

//& obtains the address of a variable
//*obtains the value of the thing a pointer is pointing to

int main(int argc, char** argv)
{
	int rows1, cols1, data, rows2,cols2;
	if(argc != 2)
		return 0;
	FILE *fp;
    fp = fopen(argv[1], "r");
	if(fp==NULL)
		return 0;
	fscanf(fp, "%d%d", &rows1, &cols1);
	int* array1 = malloc(sizeof(int)*rows1*cols1);
	for(int row_pos = 0; row_pos< rows1; row_pos++)
	{
		for(int col_pos = 0; col_pos< cols1; col_pos++)
		{
			fscanf(fp, "%d", &data);
			*(array1+(row_pos*cols1)+col_pos)=data;
		}
	}
	fscanf(fp, "%d%d", &rows2, &cols2);
	int* array2 = malloc(sizeof(int)*rows2*cols2);
	for(int row_pos = 0; row_pos< rows2; row_pos++)
	{
		for(int col_pos = 0; col_pos< cols2; col_pos++)
		{
			fscanf(fp, "%d", &data);
			*(array2+(row_pos*cols2)+col_pos)=data;
		}
	}
	if(cols1!=rows2)
	{
		printf("bad-matrices\n");
		fclose(fp);
		free(array1);
		free(array2);
		return 0;
	}
	//multiply the two matrices
	int* result = malloc(sizeof(int)*rows1*cols2);
	for(int row_pos1 = 0; row_pos1< rows1; row_pos1++)
	{
		for(int col_pos2 = 0; col_pos2< cols2; col_pos2++)
		{
			int sum = 0;
			for(int col_pos1 = 0; col_pos1<cols1;col_pos1++)
				sum+=*(array1+(row_pos1*cols1)+col_pos1)**(array2+(col_pos1*cols2)+col_pos2);
			printf("%d",sum);
			if(col_pos2<cols2-1)
				printf("\t");
			else
				printf("\n");
		}
	}
	fclose(fp);
	free(array1);
	free(array2);
	free(result);
	return 0;
}