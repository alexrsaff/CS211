#things to run when nothing is specified
all: sixth

#define "fucntion" one
sixth: sixth.c
	gcc -std=c99 -Wall -Werror -fsanitize=address sixth.c -o sixth

#only runs when clean is specified
clean:
	rm -rf sixth