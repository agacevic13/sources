all:
	clang -c -o calculator.o calculator.c
	clang -c -o functions.o functions.c
	clang -c -o test.o test.c
	clang -o calculator calculator.o functions.o test.o -lm

