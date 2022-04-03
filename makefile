flags=-Wall -Wextra -Werror -pedantic -g

botstart: main.o tests.o makefile
	clang main.o tests.o -o botstart $(flags)

main: main.c tests.o
	clang -c main.c $(flags)

test: botstart
	./botstart ./bot.py ./dif/bot.py

tests.o: tests.c
	clang -c tests.c $(flags)

clean:
	rm *.o botstart
