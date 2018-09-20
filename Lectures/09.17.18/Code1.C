#include <stdio.h>
#include <stdlib.h>

void swap(int*,int*);

//& obtains the address of a vairable
//*obtains the value of the thing a pointer is pointing to
//www.pythontutor.com is useful

int main(int argc, char** argv)
{
    int c = 42, d = 7;
    printf("Enter the value of c: ");
    scanf("%d",&c);
     printf("Enter the value of d: ");
    scanf("%d",&d);
    int a = 42; //integer variable a
    int* q;//integer pointer
    q=&a; //assign the address of a to pointer q
    //& obtains address of variable
    *q = 54; //changes values of a
    printf("a is %d\n", a);
    printf("Value at the location pointed by q is %d\n", *q);//get value of what pointer q points to
    printf("Before Calling Swap: C=%d, D=%d\n", c, d);
    swap(&c,&d);//pass through address of c and d
    printf("Before Calling Swap: C=%d, D=%d\n", c, d);
    return 0;
}
void swap(int *a, int *b)
{
    printf("Before Swap: A=%d, B=%d\n", *a, *b);
    int temp = *a;//dereference to get value at variable pointed to by a
    *a = *b;
    *b = temp;
    printf("After Swap: A=%d, B=%d\n",*a,*b);
    return;
}