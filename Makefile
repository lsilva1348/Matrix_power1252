
test:test.c matrix.c

	gcc -Wall -W -g -Werror -std=gnu99 -o test test.c matrix.c -lcunit
