#include <stdio.h>
/*
 login: ars369@ilab.cs.rutgers.edu
 compile:  gcc -Wall -Werror -fsanitize=address Name.c -o Name
 transfer: scp File ars369@ilab.cs.rutgers.edu:/ilab/users/ars369
 run: ./File
*/
int main()
{
    int i = 1;
    printf("%d",i);
    printf("Hello World!\n");
    return 1;
}