#things to run when nothing is specified
all: BaseConverter

#define "fucntion" one
BaseConverter: BaseConverter.c
	gcc -std=c99 -Wall -Werror -fsanitize=address BaseConverter.c -o BaseConverter

#only runs when clean is specified
clean:
	rm -rf BaseConverter