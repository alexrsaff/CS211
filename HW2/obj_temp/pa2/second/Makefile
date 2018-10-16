#things to run when nothing is specified
all: second

#define "fucntion" one
second: second.c
	gcc -std=c99 -Wall -Werror -fsanitize=address second.c -o second

#only runs when clean is specified
clean:
	rm -rf second