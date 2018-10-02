#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//& obtains the address of a variable
//*obtains the value of the thing a pointer is pointing to

int main(int argc, char** argv)
{
	int length = 0;
	char* word = malloc(length*sizeof(char));
	for(int argument = 1; argument<argc;argument++)
	{
		length = strlen(argv[argument]);
		word = realloc(word,length*sizeof(char));
		memcpy(word,argv[argument],length*sizeof(char));
		if(word[0]+32=='a' || word[0]+32=='e' || word[0]+32=='i' || word[0]+32=='o' || word[0]+32=='u' ||
		word[0]=='a' || word[0]=='e' || word[0]=='i' || word[0]=='o' || word[0]=='u')
		{
			length+=3;
			word = realloc(word,length);
			word[length-1] = 'y';
			word[length-2]= 'a';
			word[length-3]= 'y';
		}
		else
		{
			length+=2;
			word = realloc(word,length);
			while(word[0]+32!='a' && word[0]+32!='e' && word[0]+32!='i' && word[0]+32!='o' && word[0]+32!='u' &&
				word[0]!='a' && word[0]!='e' && word[0]!='i' && word[0]!='o' && word[0]!='u')
			{
				word[length-2]=word[0];
				for(int pos=1;pos<length;pos++)
					word[pos-1]=word[pos];
			}
			word[length-2]='a';
			word[length-1]='y';
		}
		for(int pos = 0; pos< length;pos++)
			printf("%c",word[pos]);
		length = 0;
		word = realloc(word,length);
		if(argument<argc-1)
			printf(" ");
	}
	printf("\n");
	free(word);
	return 0;
}