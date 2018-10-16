#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rowDivide(double**, int, double, int);//array, row #, divisor, columns

void rowMultiplyAndSubtract(double**, int, int, double, int); //array, minuend row, subtrahend row, divisor, columns

void invertArray(double**, double**, int);//array, output array, rows

void transpose(double**, double**, int, int);//matrix, transposed matrix, rows, columns

void DotProduct(double**, double**, double**, int, int, int);//matrix1, matrix2, output matrix, rows1, columns1, columns2

int main(int argc, char** argv)
{
    //===============================read in train file===============================
    if(argc != 3)
    {
        printf("Not enough arguments\n");
        return 0;
    }
    FILE *fp = fopen(argv[1],"r");
    int columns, rows;
    fscanf(fp,"%d\n", &columns);
    fscanf(fp,"%d\n", &rows);
    columns++;
    double* X = malloc(sizeof(double)*rows*(columns));
    double* Y = malloc(sizeof(double)*rows);
    for(int row  = 0; row < rows; row++)
    {
        for(int column = 0; column<columns+1;column++)
        {
            if(column==0)
            {
                *(X+row*(columns)+column) = 1;
                continue;
            }
            double data;
            fscanf(fp,"%lf,",&data);
            if(column==columns)
                *(Y+row) = data;
            else
                *(X+row*(columns)+column) = data;
        }
    }
    //===============================calculate weights===============================
    fclose(fp);
    double* T = malloc(sizeof(double)*rows*columns);
    transpose(&X,&T,rows,columns);
    double* D1 = malloc(sizeof(double)*columns*columns);
    DotProduct(&T,&X,&D1,columns,rows,columns);
    double* I = malloc(sizeof(double)*columns*columns);
    invertArray(&D1,&I,columns);
    double* D2 = malloc(sizeof(double)*columns*rows);
    DotProduct(&I,&T,&D2,columns,columns,rows);
    double* W = malloc(sizeof(double)*columns);
    DotProduct(&D2,&Y,&W,columns,rows,1);
    free(T);
    free(X);
    free(Y);
    free(D1);
    free(I);
    free(D2);
    //===============================read in test file===============================
    fp = fopen(argv[2],"r");
    fscanf(fp,"%d\n", &rows);
    double* X2 = malloc(sizeof(double)*rows*(columns));
    for(int row  = 0; row < rows; row++)
    {
        for(int column = 0; column<columns;column++)
        {
            if(column==0)
            {
                *(X2+row*(columns)+column) = 1;
                continue;
            }
            double data;
            fscanf(fp,"%lf,",&data);
            *(X2+row*(columns)+column) = data;
        }
    }
    //===============================Guess house prices in test data===============================
    double* Y2 = malloc(sizeof(double)*rows);
    DotProduct(&X2,&W,&Y2,rows,columns,1);
    for(int row = 0; row< rows; row++)
    {
        for(int column = 0; column<1;column++)
            printf("%0.0f",*(Y2+row*(1)+column));
        printf("\n");
    }
    free(X2);
    fclose(fp);
    free(W);
    free(Y2);
    return 0;
}

void rowDivide(double** ptr, int row, double num, int columns)
{
    double* array = *ptr;
    for(int column = 0; column < columns; column++)
        *(array+row*(columns)+column) = *(array+row*(columns)+column)/num;
    return;  
}

void rowMultiplyAndSubtract(double** ptr, int row1, int row2, double num, int columns)
{
    double* array = *ptr;
    for(int column = 0; column < columns; column++)
        *(array+row1*((columns))+column) = *(array+row1*((columns))+column) - (*(array+row2*((columns))+column)*num);
    return;  
}

void invertArray(double** arrayptr, double** inverseptr, int columns)
{
    double* inverseArray = *inverseptr;
    double* array = *arrayptr;
    int rows = columns;
    inverseArray = memset(inverseArray,0,sizeof(double)*rows*(columns));
    for(int row = 0; row<rows; row++)
        *(inverseArray+row*(columns)+row)=1;
    for(int column=0;column<columns;column++)
    {
        rowDivide(&inverseArray,column,*(array+column*(columns)+column),columns);
        rowDivide(&array,column,*(array+column*(columns)+column),columns);
        for(int row = 0; row<rows; row++)
        {
            if(row==column)
                continue;
            rowMultiplyAndSubtract(&inverseArray,row,column,*(array+row*(columns)+column),columns);
            rowMultiplyAndSubtract(&array,row,column,*(array+row*(columns)+column),columns);
        }
    }
    return;
}

void transpose(double** ptr, double** Tptr, int rows, int columns)
{
    double* array = *ptr;
    double* Tarray = *Tptr;
    for(int row = 0; row<rows; row++)
    {
        for(int column = 0; column < columns; column++)
            *(Tarray+column*((rows))+row) = *(array+row*((columns))+column);
    }
}

void DotProduct(double** ptr1, double** ptr2, double** ptrD, int rows, int columns1, int columns2)
{
    double* array1 = *ptr1;
    double* array2 = *ptr2;
    double* result = *ptrD;
    int rows1 = rows;
    int cols1 = columns1;
    int cols2 = columns2;
	for(int row_pos1 = 0; row_pos1< rows1; row_pos1++)
	{
		for(int col_pos2 = 0; col_pos2< cols2; col_pos2++)
		{
			double sum = 0;
			for(int col_pos1 = 0; col_pos1<cols1;col_pos1++)
				sum+=*(array1+(row_pos1*cols1)+col_pos1)**(array2+(col_pos1*cols2)+col_pos2);
			//printf("%f",sum);
            *(result+row_pos1*(cols2)+col_pos2) = sum;
			// if(col_pos2<cols2-1)
			// 	printf("\t");
			// else
			// 	printf("\n");
		}
	}
    return;
}