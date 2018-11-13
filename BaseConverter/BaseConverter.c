#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv)
{
	int number;
	printf("Enter number to be converted: ");
	scanf("%d",&number);
	printf("Base 10: %d\n",number);
	int remains = 0, quotient = number;
	printf("Hexadecimal: Ox");
	while(quotient!=0)
	{
		remains = quotient%16;
		quotient = quotient/16;
		switch(remains)
		{
			case 10: printf("A");break;
			case 11: printf("B");break;
			case 12: printf("C");break;
			case 13: printf("D");break;
			case 14: printf("E");break;
			case 15: printf("F");break;
			default: printf("%d",remains);
		}
	}
	printf("\n");
	remains = 0; quotient = number;
	printf("Binary: ");
	while(quotient!=0)
	{
		remains = quotient%2;
		quotient = quotient/2;
		printf("%d",remains);
	}
	printf("\n");
}