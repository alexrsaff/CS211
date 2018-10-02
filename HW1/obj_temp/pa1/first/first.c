#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	int length, number;
    //Argument checking
    if(argc != 2)
    {
        printf("Not enough arguments\n");
        return 0;
    }
    //reading in file
    FILE *fp; //filepointer
    fp = fopen(argv[1], "r");//write, read, append 
	fscanf(fp, "%d\n", &length);
    int* arr = malloc(sizeof(int)*length);
    for(int count = 0; count < length; count++)
    {
        fscanf(fp,"%d", &number);
        arr[count]=number;
    }
    //sorting
    for(int count = 0;count< length; count++)
    {
    
        int position = count - 1;
        while(position>-1 && (arr[position]>arr[position+1]))
        {
            int temp = arr[position];
            arr[position]=arr[position+1];
            arr[position+1]=temp;
            position--;
            count = 0;
        }
    }
    //seperate evens and odds
    for(int count = 0;count< length; count++)
    {
        if(arr[count]%2==0)
        {
            //printf("%d\n",arr[count]);
            //printf("Modulared: %d\n",arr[count-1]%2);
            int position = count - 1;
            while(position>-1 && !(arr[position]%2 == 0))
            {
                //printf("Howdy");
                int temp = arr[position];
                arr[position]=arr[position+1];
                arr[position+1]=temp;
                position--;
            }
        }
    }
    printf("%d", arr[0]);
    for(int count = 1; count<length; count++)
    {
        printf("\t");
        printf("%d", arr[count]);
    }
    printf("\n");
    free(arr);
    return 0;
}