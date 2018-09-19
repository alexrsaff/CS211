#things to run when nothing is specified
all: third

#define "fucntion" one
third: third.c
	gcc -std=c99 -Wall -Werror -fsanitize=address third.c -o third

#only runs when clean is specified
clean:
	rm -rf third