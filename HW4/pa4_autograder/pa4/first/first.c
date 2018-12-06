#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CACHE_SIZE argv[1]
#define ASSOCIATIVITY argv[2]
#define CACHE_POLICY argv[3]
#define BLOCK_SIZE argv[4]
#define TRACE_FILE argv[5]

struct block
{
	long address;
	long tag;
	long set;
	long age;
};

int InputCheck(int, char**);

void no_prefetch(int ,int ,int , int , int , char** );

void with_prefetch(int ,int ,int , int , int , int, char**, int);

int main(int argc, char** argv)
{
	if(InputCheck(argc,argv)==0)
	{
		printf("error\n");
		return 0;
	}
	int cache_size = atoi(CACHE_SIZE);
	int associativity = 0;
	int block_size = atoi(BLOCK_SIZE);
	if(strcmp(ASSOCIATIVITY,"direct")!=0 && strcmp(ASSOCIATIVITY,"assoc")!=0)
	{
		char* size = malloc(sizeof(char)*(strlen(ASSOCIATIVITY)-5));
		for(int position = 0; position<strlen(ASSOCIATIVITY)-6;position++)
			size[position] = ASSOCIATIVITY[position+6];
		size[strlen(ASSOCIATIVITY)-6] = '\0';
		associativity = atoi(size);
		free(size);
	}
	else if(strcmp(ASSOCIATIVITY,"direct")==0)
		associativity=1;
	else
		associativity = cache_size/block_size;
	int sets = cache_size/(associativity*block_size);
	int offset_bits = log(block_size)/log(2);
	int index_bits = log(sets)/log(2);
	with_prefetch(sets, associativity, cache_size, offset_bits, index_bits, block_size, argv, 0);
	with_prefetch(sets, associativity, cache_size, offset_bits, index_bits, block_size, argv, 1);

}

int InputCheck(int argc, char** argv)
{
	if(argc != 6)
		return 0;
	int cache_size = atoi(CACHE_SIZE);
	if(cache_size==0 || cache_size%2!=0)
		return 0;
	if(strcmp(ASSOCIATIVITY,"direct")!=0 && strcmp(ASSOCIATIVITY,"assoc")!=0)
	{
		if(strncmp(ASSOCIATIVITY,"assoc:",6)!=0)
			return 0;
		char* size = malloc(sizeof(char)*(strlen(ASSOCIATIVITY)-5));
		for(int position = 0; position<strlen(ASSOCIATIVITY)-6;position++)
			size[position] = ASSOCIATIVITY[position+6];
		size[strlen(ASSOCIATIVITY)-6] = '\0';
		int associativity = atoi(size);
		free(size);
		if(associativity%2!=0)
			return 0;
	}
	if(strcmp(CACHE_POLICY,"fifo")!=0 && strcmp(CACHE_POLICY,"lru")!=0)
		return 0;
	int block_size = atoi(BLOCK_SIZE);
	if(block_size==0 || (block_size%2!=0 && block_size!=1))
		return 0;
	FILE *fp;
    fp = fopen(TRACE_FILE, "r");
	if(fp==NULL)
		return 0;
	fclose(fp);
	return 1;
}

void with_prefetch(int sets,int associativity,int cache_size, int offset_bits, int index_bits, int block_size, char** argv, int prefetch)
{
	
	FILE *fp;
    fp = fopen(TRACE_FILE, "r");
	char program_counter[16];
	char address_string[16];
	char action;
	int cache_hits = 0, cache_misses = 0, memory_reads = 0, memory_writes = 0;
	struct block** set_array = malloc(sizeof(struct block*)*sets);
	for(int count=0; count < sets; count++)
	{
		set_array[count] = malloc(sizeof(struct block)*associativity);
		for(int block_num = 0; block_num<associativity; block_num++)
		{
			set_array[count][block_num].tag=-1;
			set_array[count][block_num].set=-1;
			set_array[count][block_num].address=-1;
			set_array[count][block_num].age=-1;
		}
	}
	if(prefetch==1)
		printf("with-prefetch\n");
	else
		printf("no-prefetch\n");
	for(long counter = 1; fscanf(fp, "%s %c %s\n", program_counter, &action, address_string) == 3; counter++)
    {
		if(action=='W')
			memory_writes++;
		long address = strtol(address_string, NULL, 0);
		long tag = address>>(offset_bits+index_bits);
		long set = (address>>offset_bits)%tag;
		int hit = 0;
		for(int block_num = 0; block_num < associativity; block_num ++)
		{
			if(set_array[set][block_num].tag==tag)
			{
				hit = 1;
				cache_hits++;
				if(strcmp(CACHE_POLICY,"lru")==0)
					set_array[set][block_num].age = counter;
			}
		}
		if(hit == 0)
		{
			cache_misses++;
			int full = 1;
			memory_reads++;
			for(int block_num = 0; block_num < associativity; block_num ++)
			{
				if(set_array[set][block_num].tag==-1)
				{
					full=0;
					set_array[set][block_num].tag=tag;
					set_array[set][block_num].set=set;
					set_array[set][block_num].address=address;
					set_array[set][block_num].age=counter;
					break;
				}
			}
			if(full==1)
			{
				long lowest_age = counter+1;
				int lowest_block_num;
				for(int block_num = 0; block_num < associativity; block_num ++)
				{
					if(set_array[set][block_num].age<lowest_age)
					{
						lowest_age = set_array[set][block_num].age;
						lowest_block_num = block_num;
					}
				}
				set_array[set][lowest_block_num].tag = tag;
				set_array[set][lowest_block_num].set=set;
				set_array[set][lowest_block_num].address = address;
				set_array[set][lowest_block_num].age = counter;
			}
			//----------------------------------------------------------------START PREFETCH
			if(prefetch==1)
			{
				counter++;
				address = address+block_size;
				tag = address>>(offset_bits+index_bits);
				set = (address>>offset_bits)%tag;
				int prefetch_hit = 0;
				for(int block_num = 0; block_num < associativity; block_num ++)
				{
					if(set_array[set][block_num].tag==tag)
						prefetch_hit = 1;
				}
				if(prefetch_hit == 0)
				{
					int prefetch_full = 1;
					memory_reads++;
					for(int block_num = 0; block_num < associativity; block_num ++)
					{
						if(set_array[set][block_num].tag==-1)
						{
							prefetch_full=0;
							set_array[set][block_num].tag=tag;
							set_array[set][block_num].set=set;
							set_array[set][block_num].address=address;
							set_array[set][block_num].age=counter;
							break;
						}
					}
					if(prefetch_full==1)
					{
						long lowest_age = counter+1;
						int lowest_block_num;
						for(int block_num = 0; block_num < associativity; block_num ++)
						{
							if(set_array[set][block_num].age<lowest_age)
							{
								lowest_age = set_array[set][block_num].age;
								lowest_block_num = block_num;
							}
						}
						set_array[set][lowest_block_num].tag = tag;
						set_array[set][lowest_block_num].set=set;
						set_array[set][lowest_block_num].address = address;
						set_array[set][lowest_block_num].age = counter;
					}
				}
			}
			//----------------------------------------------------------------END PREFETCH
		}
	}
	printf("Memory reads: %d\n",memory_reads);
	printf("Memory writes: %d\n",memory_writes);
	printf("Cache hits: %d\n",cache_hits);
	printf("Cache misses: %d\n", cache_misses);
	fclose(fp);
	for(int count=0; count < sets; count++)
		free(set_array[count]);
	free(set_array);
	return;
}