#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
#
# Makefile for three compiler calls
# Read the comments on Makefile2. All of them apply here too.
# But now the hash table is compiled in a separate gcc call
# Therefore, there must be a header of it to be included in scanner.l
#

etapa2: y.tab.o lex.yy.o main.o hash.o
	gcc -o etapa2 lex.yy.o main.o hash.o y.tab.o
main.o: main.c
	gcc -c main.c
hash.o: hash.c
	gcc -c hash.c
y.tab.o: y.tab.c
	gcc -c y.tab.c
y.tab.c: parser.y
	yacc -d parser.y -v
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l 
clean:
	rm *.o lex.yy.c etapa2 y.tab.c y.tab.h
