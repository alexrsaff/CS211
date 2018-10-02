#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//& obtains the address of a variable
//*obtains the value of the thing a pointer is pointing to

int main(int argc, char** argv)
{
	int length = argc-1;
	int word_len = 0;
	char* word = malloc(length*sizeof(char));
	for(int argument = 1; argument<argc;argument++)
	{
		word_len = strlen(argv[argument]);
		word[argument-1] = argv[argument][word_len-1];
	}
	for(int position = 0; position < length; position++)
		printf("%c",word[position]);
	printf("\n");
	free(word);
	return 0;
}