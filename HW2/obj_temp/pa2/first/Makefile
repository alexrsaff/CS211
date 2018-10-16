#things to run when nothing is specified
all: first

#define "fucntion" one
first: first.c
	gcc -std=c99 -Wall -Werror -fsanitize=address first.c -o first

#only runs when clean is specified
clean:
	rm -rf first