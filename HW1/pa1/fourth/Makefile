#things to run when nothing is specified
all: fourth

#define "fucntion" one
fourth: fourth.c
	gcc -std=c99 -Wall -Werror -fsanitize=address fourth.c -o fourth

#only runs when clean is specified
clean:
	rm -rf fourth