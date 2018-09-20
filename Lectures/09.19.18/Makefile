all: ThisRule

ThisRule: Code1.c
	gcc -std=c99 -Wall -Werror -fsanitize=address Code1.c -o Code1

clean:
	rm -rf Code1