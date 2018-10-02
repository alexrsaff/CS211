#things to run when nothing is specified
all: ninth

#define "fucntion" one
ninth: ninth.c
	gcc -std=c99 -Wall -Werror -fsanitize=address ninth.c -o ninth

#only runs when clean is specified
clean:
	rm -rf ninth