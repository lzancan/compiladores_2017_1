#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
#
# Makefile for three compiler calls
# Read the comments on Makefile2. All of them apply here too.
# But now the hash table is compiled in a separate gcc call
# Therefore, there must be a header of it to be included in scanner.l
#

etapa3: y.tab.o lex.yy.o main.o hash.o astree.o semantic.o tacs.o exemplo.o
	gcc -o etapa6 lex.yy.o main.o hash.o astree.o semantic.o tacs.o y.tab.o
	gcc -o exemplo exemplo.o
main.o: main.c
	gcc -c main.c
hash.o: hash.c
	gcc -c hash.c
astree.o: astree.c
	gcc -c astree.c
semantic.o: semantic.c
	gcc -c semantic.c
tacs.o: tacs.c
	gcc -c tacs.c
y.tab.o: y.tab.c
	gcc -c y.tab.c
y.tab.c: parser.y
	yacc -d parser.y -v
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l 
#para o exemplo em c para codigo asm
exemplo.o: exemplo.c
	gcc -S exemplo.c
	gcc -c exemplo.s

clean:
	rm *.o lex.yy.c etapa6 y.tab.c y.tab.h exemplo

