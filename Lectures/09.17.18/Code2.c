#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char a;
    int b;
    if(argc != 2)
    {
        printf("Not enough arguments\n");
        return 0;
    }
    FILE *fp; //filepointer
    fp = fopen(argv[1], "r");//write, read, append
    while(fscanf(fp, "%c %d\n", &a, &b) == 2)
    {
        printf("%c %d\n", a, b);
    }
    return 0;
}