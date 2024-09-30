all:
	clang -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -c -o calculator.o calculator.c
	clang -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -c -o functions.o functions.c
	clang -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -c -o test.o test.c
	clang -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -o calculator calculator.o functions.o test.o -lm

