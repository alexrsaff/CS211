#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	int points[250];
	printf("How many elements? ");
	int num_elements;
	scanf("%d",&num_elements);
	for(int i=0; i<num_elements;i++)
	{
		printf("Enter points for exam %d: ",i);
		scanf("%d",&points[i]);
	}
	for(int i=0; i<num_elements;i++)
	{
		printf("Points for exam %d: %d\n",i,points[i]);
	}
	return 0;
}