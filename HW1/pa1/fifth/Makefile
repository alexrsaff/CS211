#things to run when nothing is specified
all: fifth

#define "fucntion" one
fifth: fifth.c
	gcc -std=c99 -Wall -Werror -fsanitize=address fifth.c -o fifth

#only runs when clean is specified
clean:
	rm -rf fifth