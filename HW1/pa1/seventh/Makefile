#things to run when nothing is specified
all: seventh

#define "fucntion" one
seventh: seventh.c
	gcc -std=c99 -Wall -Werror -fsanitize=address seventh.c -o seventh

#only runs when clean is specified
clean:
	rm -rf seventh