#things to run when nothing is specified
all: one two

#define "fucntion" one
one: Code1.C
	gcc -Wall -Werror -fsanitize=address Code1.C -o Code1

#define "function" two
two: Code2.c
	gcc -Wall -Werror -fsanitize=address Code2.c -o Code2

#only runs when clean is specified
clean:
	rm -rf Code1
	rm -rf Code2