#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define OUTPUT 1
#define INPUT 0
#define TEMP 2
#define UNUSED -1

#define MAX_VARS 100

struct var
{
	char* name;
	int value;
	int type;
};

int getWord(char**, FILE*);

int main(int argc, char** argv)
{
	int inputnum = 0, outputnum = 0, greycode_length = 0, total_vars = 0, tempnum = 0;
	struct var** variable_array;
	if(argc!=2)
		return 0;
	FILE *fp;
    fp = fopen(argv[1], "r");
	char* word = malloc(sizeof(char));
	word[0] = '\0';
	while(getWord(&word, fp)!=-1)
	{
		total_vars = tempnum + inputnum + outputnum;
		if(strcmp(word,"INPUTVAR")==0)
		{
			if(getWord(&word, fp)==-1)
				break;
			inputnum = atoi(word);
			greycode_length = 1 << inputnum;
			variable_array = malloc(sizeof(struct var*)*greycode_length);
			for(int row = 0; row < greycode_length; row ++)
			{
				variable_array[row]=malloc(sizeof(struct var)*MAX_VARS);
				for(int column = 0; column < MAX_VARS; column++)
				{
					variable_array[row][column].type=UNUSED;
					variable_array[row][column].value=UNUSED;
					variable_array[row][column].name=NULL;
				}
			}
			for(int varnum = 0; varnum< inputnum; varnum++)
			{
				if(getWord(&word,fp)==-1)
					return 0;
				int count =0;
				int zflag = -1;
				int fill_length = 1<<(inputnum-varnum-1);
				for(int combo = 0; combo < greycode_length; combo++)
				{
					variable_array[combo][varnum].name = malloc(sizeof(char)*(strlen(word)+1));
					memcpy(variable_array[combo][varnum].name,word,sizeof(char)*(strlen(word)+1));
					variable_array[combo][varnum].type = INPUT;
					if(combo<fill_length)
						variable_array[combo][varnum].value=0;
					if(combo==fill_length)
						zflag=0;
					if(zflag==0)
					{
						if(count<fill_length*2)
						{
							variable_array[combo][varnum].value=1;
							count++;
						}
						else
						{
							count=0;
							zflag=1;
						}
					}
					if(zflag==1)
					{
						if(count<fill_length*2)
						{
							variable_array[combo][varnum].value=0;
							count++;
						}
						if(count>=fill_length*2)
						{
							count=0;
							zflag=0;
						}
					}
				}
			}
			for(int row = 0; row < greycode_length; row++)
			{
				variable_array[row][inputnum].name = malloc(sizeof(char)*2);
				memcpy(variable_array[row][inputnum].name,&"1",sizeof(char)*2);
				variable_array[row][inputnum].value = 1;
				variable_array[row][inputnum].type = TEMP;
			}
			inputnum ++;
			for(int row = 0; row < greycode_length; row++)
			{
				variable_array[row][inputnum].name = malloc(sizeof(char)*2);
				memcpy(variable_array[row][inputnum].name,&"0",sizeof(char)*2);
				variable_array[row][inputnum].value = 0;
				variable_array[row][inputnum].type = TEMP;
			}
			inputnum++;
		}
		else if(strcmp(word,"OUTPUTVAR")==0)
		{
			if(getWord(&word, fp)==-1)
				break;
			outputnum = atoi(word);
			for(int varnum = inputnum; varnum < inputnum + outputnum; varnum++)
			{
				if(getWord(&word,fp)==-1)
						return 0;
				for(int combo = 0; combo < greycode_length; combo ++)
				{
					variable_array[combo][varnum].name = malloc(sizeof(char)*(strlen(word)+1));
					memcpy(variable_array[combo][varnum].name,word,sizeof(char)*(strlen(word)+1));
					variable_array[combo][varnum].type = OUTPUT;
				}
			}
		}
		else if(strcmp(word,"NOT")==0)
		{
			if(getWord(&word,fp)==-1)
				return 0;
			int input_location = 0;
			int found = 0;
			for(int varnum = 0; varnum < MAX_VARS; varnum++)
			{
				if(strcmp(variable_array[0][varnum].name,word)==0)
				{
					input_location=varnum;
					break;
				}
			}
			if(getWord(&word,fp)==-1)
				return 0;
			int output_location = 0;
			for(int varnum = 0; varnum < MAX_VARS; varnum++)
			{
				if(variable_array[0][varnum].name==NULL)
					continue;
				if(strcmp(variable_array[0][varnum].name,word)==0)
				{
					output_location=varnum;
					found = 1;
					break;
				}
			}
			if(found == 1)
			{
				for(int combo = 0; combo < greycode_length; combo++)
					variable_array[combo][output_location].value=!variable_array[combo][input_location].value;
			}
			else if(found==0)
			{
				tempnum ++;
				for(int combo = 0; combo < greycode_length; combo++)
				{
					variable_array[combo][total_vars].type=TEMP;
					variable_array[combo][total_vars].value=!variable_array[combo][input_location].value;
					variable_array[combo][total_vars].name = malloc(sizeof(char)*(strlen(word)+1));
					memcpy(variable_array[combo][total_vars].name,word,sizeof(char)*(strlen(word)+1));
				}
			}
		}
		else if(strcmp(word,"AND")==0)
		{
			if(getWord(&word,fp)==-1)
				return 0;
			int input_location1 = 0;
			for(int varnum = 0; varnum < MAX_VARS; varnum++)
			{
				if(strcmp(variable_array[0][varnum].name,word)==0)
				{
					input_location1=varnum;
					break;
				}
			}
			if(getWord(&word,fp)==-1)
				return 0;
			int input_location2 = 0;
			for(int varnum = 0; varnum < MAX_VARS; varnum++)
			{
				if(strcmp(variable_array[0][varnum].name,word)==0)
				{
					input_location2=varnum;
					break;
				}
			}
			if(getWord(&word,fp)==-1)
				return 0;
			int found = 0;
			int output_location = 0;
			for(int varnum = 0; varnum < MAX_VARS; varnum++)
			{
				if(variable_array[0][varnum].name==NULL)
					continue;
				if(strcmp(variable_array[0][varnum].name,word)==0)
				{
					output_location=varnum;
					found = 1;
					break;
				}
			}
			if(found == 1)
			{
				for(int combo = 0; combo < greycode_length; combo++)
					variable_array[combo][output_location].value=variable_array[combo][input_location1].value&variable_array[combo][input_location2].value;
			}
			else if(found==0)
			{
				tempnum ++;
				for(int combo = 0; combo < greycode_length; combo++)
				{
					variable_array[combo][total_vars].type=TEMP;
					variable_array[combo][total_vars].value=variable_array[combo][input_location1].value&variable_array[combo][input_location2].value;
					variable_array[combo][total_vars].name = malloc(sizeof(char)*(strlen(word)+1));
					memcpy(variable_array[combo][total_vars].name,word,sizeof(char)*(strlen(word)+1));
				}
			}
		}
		else if(strcmp(word,"OR")==0)
		{
			if(getWord(&word,fp)==-1)
				return 0;
			int input_location1 = 0;
			for(int varnum = 0; varnum < MAX_VARS; varnum++)
			{
				if(strcmp(variable_array[0][varnum].name,word)==0)
				{
					input_location1=varnum;
					break;
				}
			}
			if(getWord(&word,fp)==-1)
				return 0;
			int input_location2 = 0;
			for(int varnum = 0; varnum < MAX_VARS; varnum++)
			{
				if(strcmp(variable_array[0][varnum].name,word)==0)
				{
					input_location2=varnum;
					break;
				}
			}
			if(getWord(&word,fp)==-1)
				return 0;
			int found = 0;
			int output_location = 0;
			for(int varnum = 0; varnum < MAX_VARS; varnum++)
			{
				if(variable_array[0][varnum].name==NULL)
					continue;
				if(strcmp(variable_array[0][varnum].name,word)==0)
				{
					output_location=varnum;
					found = 1;
					break;
				}
			}
			if(found == 1)
			{
				for(int combo = 0; combo < greycode_length; combo++)
					variable_array[combo][output_location].value=variable_array[combo][input_location1].value|variable_array[combo][input_location2].value;
			}
			else if(found==0)
			{
				tempnum ++;
				for(int combo = 0; combo < greycode_length; combo++)
				{
					variable_array[combo][total_vars].type=TEMP;
					variable_array[combo][total_vars].value=variable_array[combo][input_location1].value|variable_array[combo][input_location2].value;
					variable_array[combo][total_vars].name = malloc(sizeof(char)*(strlen(word)+1));
					memcpy(variable_array[combo][total_vars].name,word,sizeof(char)*(strlen(word)+1));
				}
			}
		}
		else if(strcmp(word,"XOR")==0)
		{
			if(getWord(&word,fp)==-1)
				return 0;
			int input_location1 = 0;
			for(int varnum = 0; varnum < MAX_VARS; varnum++)
			{
				if(strcmp(variable_array[0][varnum].name,word)==0)
				{
					input_location1=varnum;
					break;
				}
			}
			if(getWord(&word,fp)==-1)
				return 0;
			int input_location2 = 0;
			for(int varnum = 0; varnum < MAX_VARS; varnum++)
			{
				if(strcmp(variable_array[0][varnum].name,word)==0)
				{
					input_location2=varnum;
					break;
				}
			}
			if(getWord(&word,fp)==-1)
				return 0;
			int found = 0;
			int output_location = 0;
			for(int varnum = 0; varnum < MAX_VARS; varnum++)
			{
				if(variable_array[0][varnum].name==NULL)
					continue;
				if(strcmp(variable_array[0][varnum].name,word)==0)
				{
					output_location=varnum;
					found = 1;
					break;
				}
			}
			if(found == 1)
			{
				for(int combo = 0; combo < greycode_length; combo++)
					variable_array[combo][output_location].value=variable_array[combo][input_location1].value^variable_array[combo][input_location2].value;
			}
			else if(found==0)
			{
				tempnum ++;
				for(int combo = 0; combo < greycode_length; combo++)
				{
					variable_array[combo][total_vars].type=TEMP;
					variable_array[combo][total_vars].value=variable_array[combo][input_location1].value^variable_array[combo][input_location2].value;
					variable_array[combo][total_vars].name = malloc(sizeof(char)*(strlen(word)+1));
					memcpy(variable_array[combo][total_vars].name,word,sizeof(char)*(strlen(word)+1));
				}
			}
		}
		else if(strcmp(word,"NAND")==0)
		{
			if(getWord(&word,fp)==-1)
				return 0;
			int input_location1 = 0;
			for(int varnum = 0; varnum < MAX_VARS; varnum++)
			{
				if(strcmp(variable_array[0][varnum].name,word)==0)
				{
					input_location1=varnum;
					break;
				}
			}
			if(getWord(&word,fp)==-1)
				return 0;
			int input_location2 = 0;
			for(int varnum = 0; varnum < MAX_VARS; varnum++)
			{
				if(strcmp(variable_array[0][varnum].name,word)==0)
				{
					input_location2=varnum;
					break;
				}
			}
			if(getWord(&word,fp)==-1)
				return 0;
			int found = 0;
			int output_location = 0;
			for(int varnum = 0; varnum < MAX_VARS; varnum++)
			{
				if(variable_array[0][varnum].name==NULL)
					continue;
				if(strcmp(variable_array[0][varnum].name,word)==0)
				{
					output_location=varnum;
					found = 1;
					break;
				}
			}
			if(found == 1)
			{
				for(int combo = 0; combo < greycode_length; combo++)
					variable_array[combo][output_location].value=!(variable_array[combo][input_location1].value&variable_array[combo][input_location2].value);
			}
			else if(found==0)
			{
				tempnum ++;
				for(int combo = 0; combo < greycode_length; combo++)
				{
					variable_array[combo][total_vars].type=TEMP;
					variable_array[combo][total_vars].value=!(variable_array[combo][input_location1].value&variable_array[combo][input_location2].value);
					variable_array[combo][total_vars].name = malloc(sizeof(char)*(strlen(word)+1));
					memcpy(variable_array[combo][total_vars].name,word,sizeof(char)*(strlen(word)+1));
				}
			}
		}
		else if(strcmp(word,"NOR")==0)
		{
			if(getWord(&word,fp)==-1)
				return 0;
			int input_location1 = 0;
			for(int varnum = 0; varnum < MAX_VARS; varnum++)
			{
				if(strcmp(variable_array[0][varnum].name,word)==0)
				{
					input_location1=varnum;
					break;
				}
			}
			if(getWord(&word,fp)==-1)
				return 0;
			int input_location2 = 0;
			for(int varnum = 0; varnum < MAX_VARS; varnum++)
			{
				if(strcmp(variable_array[0][varnum].name,word)==0)
				{
					input_location2=varnum;
					break;
				}
			}
			if(getWord(&word,fp)==-1)
				return 0;
			int found = 0;
			int output_location = 0;
			for(int varnum = 0; varnum < MAX_VARS; varnum++)
			{
				if(variable_array[0][varnum].name==NULL)
					continue;
				if(strcmp(variable_array[0][varnum].name,word)==0)
				{
					output_location=varnum;
					found = 1;
					break;
				}
			}
			if(found == 1)
			{
				for(int combo = 0; combo < greycode_length; combo++)
					variable_array[combo][output_location].value=!(variable_array[combo][input_location1].value|variable_array[combo][input_location2].value);
			}
			else if(found==0)
			{
				tempnum ++;
				for(int combo = 0; combo < greycode_length; combo++)
				{
					variable_array[combo][total_vars].type=TEMP;
					variable_array[combo][total_vars].value=!(variable_array[combo][input_location1].value|variable_array[combo][input_location2].value);
					variable_array[combo][total_vars].name = malloc(sizeof(char)*(strlen(word)+1));
					memcpy(variable_array[combo][total_vars].name,word,sizeof(char)*(strlen(word)+1));
				}
			}
		}
		else if(strcmp(word,"DECODER")==0)
		{
			if(getWord(&word, fp)==-1)
				break;
			int decoder_in_num = atoi(word);
			int decoder_greycode_length = 1 << decoder_in_num;
			struct var* output_array =  malloc(sizeof(struct var)*decoder_greycode_length);
			struct var* input_array = malloc(sizeof(struct var)*decoder_in_num);
			for(int count = 0; count<decoder_in_num;count++)
			{
				if(getWord(&word, fp)==-1)
					break;
				input_array[count].type = TEMP;
				input_array[count].name = malloc(sizeof(char)*(strlen(word)+1));
				memcpy(input_array[count].name,word,sizeof(char)*(strlen(word)+1));
				for(int varnum = 0; varnum < MAX_VARS; varnum++)
				{
					if(strcmp(variable_array[0][varnum].name,word)==0)
					{
						input_array[count].value =varnum;
						break;
					}
				}
			}
			for(int count = 0; count<decoder_greycode_length;count++)
			{
				if(getWord(&word, fp)==-1)
					break;
				output_array[count].type = TEMP;
				int found = 0;
				for(int varnum = 0; varnum < MAX_VARS; varnum++)
				{
					if(variable_array[0][varnum].name==NULL)
						continue;
					if(strcmp(variable_array[0][varnum].name,word)==0)
					{
						output_array[count].value = varnum;
						found = 1;
						break;
					}
				}
				if(found ==0)
				{
					tempnum++;
					for(int combo = 0; combo < greycode_length; combo++)
					{
						variable_array[combo][total_vars].type=TEMP;
						variable_array[combo][total_vars].value=UNUSED;
						variable_array[combo][total_vars].name = malloc(sizeof(char)*(strlen(word)+1));
						memcpy(variable_array[combo][total_vars].name,word,sizeof(char)*(strlen(word)+1));
					}
					output_array[count].value = total_vars;
					total_vars = tempnum + inputnum + outputnum;
				}
				output_array[count].name = malloc(sizeof(char)*(strlen(word)+1));
				memcpy(output_array[count].name,word,sizeof(char)*(strlen(word)+1));
			}
			for(int combo = 0; combo < greycode_length; combo++)
			{
				struct var** decoder_matrix = malloc(sizeof(struct var*)*decoder_greycode_length);
				for(int row = 0; row < decoder_greycode_length; row++)
				{
					decoder_matrix[row]=malloc(sizeof(struct var)*decoder_in_num);
					for(int column = 0; column < decoder_in_num; column++)
					{
						decoder_matrix[row][column].type = input_array[column].type;
						decoder_matrix[row][column].value = UNUSED;
					}
				}
				
				for(int varnum = 0; varnum< decoder_in_num; varnum++)
				{
					int count =0;
					int zflag = -1;
					int fill_length = 1<<(decoder_in_num-varnum-1);
					for(int decoder_combo = 0; decoder_combo < decoder_greycode_length; decoder_combo++)
					{
						decoder_matrix[decoder_combo][varnum].name = malloc(sizeof(char)*(strlen(input_array[varnum].name)+1));
						memcpy(decoder_matrix[decoder_combo][varnum].name,word,sizeof(char)*(strlen(input_array[varnum].name)+1));
						decoder_matrix[decoder_combo][varnum].type = INPUT;
						if(decoder_combo<fill_length)
							decoder_matrix[decoder_combo][varnum].value=!variable_array[combo][input_array[varnum].value].value;
						if(decoder_combo==fill_length)
							zflag=0;
						if(zflag==0)
						{
							if(count<fill_length*2)
							{
								decoder_matrix[decoder_combo][varnum].value=variable_array[combo][input_array[varnum].value].value;
								count++;
							}
							else
							{
								count=0;
								zflag=1;
							}
						}
						if(zflag==1)
						{
							if(count<fill_length*2)
							{
								decoder_matrix[decoder_combo][varnum].value=!variable_array[combo][input_array[varnum].value].value;
								count++;
							}
							if(count>=fill_length*2)
							{
								count=0;
								zflag=0;
							}
						}
					}
				}
				for(int row = 0; row < decoder_greycode_length; row++)
				{
					for(int column = 1; column < decoder_in_num; column++)
					{
						decoder_matrix[row][column].value = decoder_matrix[row][column].value & decoder_matrix[row][column-1].value;
					}
					variable_array[combo][output_array[row].value].value = decoder_matrix[row][decoder_in_num-1].value;
				}
				for(int row = 0; row < decoder_greycode_length; row++)
				{
					for(int column = 0; column < decoder_in_num; column++)
					{
						if(decoder_matrix[row][column].name!=NULL)
							free(decoder_matrix[row][column].name);
					}
					free(decoder_matrix[row]);
				}
				free(decoder_matrix);
			}
			for(int column = 0; column < decoder_in_num; column++)
			{
				if(input_array[column].name!=NULL)
					free(input_array[column].name);
			}
			free(input_array);
			for(int column = 0; column < decoder_greycode_length; column++)
			{
				if(output_array[column].name!=NULL)
					free(output_array[column].name);
			}
			free(output_array);
		}
		else if(strcmp(word, "MULTIPLEXER")==0)
		{
			if(getWord(&word, fp)==-1)
				break;
			int multi_in_num = atoi(word);
			struct var* input_array = malloc(sizeof(struct var)*multi_in_num);
			for(int count = 0; count<multi_in_num;count++)
			{
				if(getWord(&word, fp)==-1)
					break;
				input_array[count].type = TEMP;
				input_array[count].name = malloc(sizeof(char)*(strlen(word)+1));
				memcpy(input_array[count].name,word,sizeof(char)*(strlen(word)+1));
				for(int varnum = 0; varnum < MAX_VARS; varnum++)
				{
					if(strcmp(variable_array[0][varnum].name,word)==0)
					{
						input_array[count].value =varnum;
						break;
					}
				}
			}
			int selector_num = log(multi_in_num)/log(2);
			struct var* selector_array = malloc(sizeof(struct var)*selector_num);
			for(int count = 0; count < selector_num; count ++)
			{
				if(getWord(&word, fp)==-1)
					break;
				selector_array[count].type = TEMP;
				selector_array[count].name = malloc(sizeof(char)*(strlen(word)+1));
				memcpy(selector_array[count].name, word, sizeof(char)*(strlen(word)+1));
				for(int varnum = 0; varnum < MAX_VARS; varnum++)
				{
					if(strcmp(variable_array[0][varnum].name,word)==0)
					{
						selector_array[count].value =varnum;
						break;
					}
				}
			}
			if(getWord(&word, fp)==-1)
				break;
			struct var output;
			output.type = TEMP;
			output.name = malloc(sizeof(char)*(strlen(word)+1));
			memcpy(output.name,word,sizeof(char)*(strlen(word)+1));
			int found = 0;
			for(int varnum = 0; varnum < MAX_VARS; varnum++)
			{
				if(variable_array[0][varnum].name==NULL)
					continue;
				if(strcmp(variable_array[0][varnum].name,word)==0)
				{
					output.value = varnum;
					found = 1;
					break;
				}
			}
			if(found ==0)
			{
				tempnum++;
				for(int combo = 0; combo < greycode_length; combo++)
				{
					variable_array[combo][total_vars].type=TEMP;
					variable_array[combo][total_vars].value=UNUSED;
					variable_array[combo][total_vars].name = malloc(sizeof(char)*(strlen(word)+1));
					memcpy(variable_array[combo][total_vars].name,word,sizeof(char)*(strlen(word)+1));
				}
				output.value = total_vars;
				total_vars = tempnum + inputnum + outputnum;
			}
			int greycode_size = 1<< selector_num;
			int** greycode_array = malloc(sizeof(int*)*greycode_size);
			for(int row = 0; row < greycode_size; row++)
			{
				greycode_array[row]=malloc(sizeof(int)*selector_num);
				for(int column = 0; column < selector_num; column++)
				{
					greycode_array[row][column]=0;
				}
			}
			for(int column = 0; column< selector_num; column++)
			{
				int count =0;
				int zflag = -1;
				int fill_length = 1<<(selector_num-column-1);
				for(int row = 0; row < greycode_size; row++)
				{
					if(row<fill_length)
						greycode_array[row][column]=0;
					if(row==fill_length)
						zflag=0;
					if(zflag==0)
					{
						if(count<fill_length*2)
						{
							greycode_array[row][column]=1;
							count++;
						}
						else
						{
							count=0;
							zflag=1;
						}
					}
					if(zflag==1)
					{
						if(count<fill_length*2)
						{
							greycode_array[row][column]=0;
							count++;
						}
						if(count>=fill_length*2)
						{
							count=0;
							zflag=0;
						}
					}
				}
			}
			int* selection = malloc(sizeof(int)*selector_num);
			for(int combo = 0; combo < greycode_length; combo ++)
			{
				for(int count = 0; count < selector_num; count++)
					selection[count] = variable_array[combo][selector_array[count].value].value;
				for(int count = 0; count < greycode_size; count ++)
				{
					int match = 1;
					for(int column = 0; column < selector_num; column++)
					{
						if(greycode_array[count][column]!=selection[column])
							match =0;
					}
					if(match==1)
					{
						variable_array[combo][output.value].value = variable_array[combo][input_array[count].value].value;
						break;
					}
				}
				
			}
			//------------------------------------------------free stuff
			free(selection);
			for(int row = 0; row< greycode_size; row++)
				free(greycode_array[row]);
			free(greycode_array);
			for(int column = 0; column < multi_in_num; column++)
			{
				if(input_array[column].name != NULL)
					free(input_array[column].name);
			}
			free(input_array);
			for(int column = 0; column < selector_num; column++)
			{
				if(selector_array[column].name != NULL)
					free(selector_array[column].name);
			}
			free(selector_array);
			free(output.name);
		}
	}
	free(word);
	for(int row = 0; row < greycode_length; row++)
	{
		for( int column = 0; column< total_vars; column++)
		{
			if(variable_array[row][column].type == INPUT || variable_array[row][column].type == OUTPUT)
				printf("%d ",variable_array[row][column].value);
		}
		printf("\n");
	}
	for(int row = 0; row<greycode_length;row++)
	{
		for(int column = 0; column < MAX_VARS; column++)
		{
			if(variable_array[row][column].name!=NULL)
				free(variable_array[row][column].name);
		}
		free(variable_array[row]);
	}
	
	free(variable_array);
}

int getWord(char** wordptr, FILE *fp)
{
	char* word = malloc(sizeof(char));
	int word_length = 1;
	word[0] = '\0';
	char character = fgetc(fp);
	for(;character!='\n' && character != ' ';character = fgetc(fp))
	{
		if(feof(fp))
		{
			free(word);
			return -1;
		}
		char* temp = malloc(sizeof(char)*word_length);
		memcpy(temp,word,sizeof(char)*word_length);
		word_length++;
		free(word);
		word = malloc(sizeof(char)*word_length);
		memcpy(word,temp,sizeof(char)*(word_length-1));
		word[word_length-1] = '\0';
		word[word_length-2] = character;
		free(temp);
	}
	free(*wordptr);
	*wordptr = word;
	return 0;
}