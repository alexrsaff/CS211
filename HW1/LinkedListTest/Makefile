#things to run when nothing is specified
all: second

#define "fucntion" one
second: LLTest.c
	gcc -std=c99 -Wall -Werror -fsanitize=address LLTest.c -o LLTest

#only runs when clean is specified
clean:
	rm -rf LLTest