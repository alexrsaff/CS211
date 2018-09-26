#things to run when nothing is specified
all: eighth

#define "fucntion" one
eighth: eighth.c
	gcc -std=c99 -Wall -Werror -fsanitize=address eighth.c -o eighth

#only runs when clean is specified
clean:
	rm -rf eighth