#ifndef HASH
#define HASH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 997

#define SYMBOL_LIT_INTEGER 1
#define SYMBOL_LIT_REAL 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_STRING 4
#define SYMBOL_IDENTIFIER 7

#define NATURE_ESCALAR 10
#define NATURE_FUNCTION 11
#define NATURE_VECTOR 12

#define DATATYPE_BYTE 20
#define DATATYPE_SHORT 21
#define DATATYPE_LONG 22
#define DATATYPE_FLOAT 23
#define DATATYPE_DOUBLE 24

#define VALUETYPE_INTEGER 30
#define VALUETYPE_REAL 31
#define VALUETYPE_CHAR 32
#define VALUETYPE_BOOLEAN 33
#define VALUETYPE_STRING 34

int getLineNumber(void);
int yyerror(char *value);
int yylex(void);

// estrutura do nodo da hash

struct HASH_NODE{
	int type;
	char * value;
	int nature;
	int dataType;
	struct HASH_NODE * next;
	struct ASTREE* astreeNode;	
};
typedef struct HASH_NODE HASH_NODE;

// hash (array de nodos com o tamanho de HASH_SIZE)
HASH_NODE * hashTable[HASH_SIZE];


void initHash();// inicializa a hash, fazendo os nodos serem null
int hashAddress(char *value); // gera o endereço hash baseado no nome (char *value)
HASH_NODE *hashFind(char *value); // procura por um nodo na hash, retorna NULL se não encontrou
char * addStringTerminator(char* value); // adiciona "\0" ao final de uma string
HASH_NODE * insertHash(int type,char * value);
void printToken(int token);// imprime um token
void printHashNode(HASH_NODE * node); // imprime um nodo da hash
void printHash(); // imprime a hash toda
HASH_NODE* makeTemp();
HASH_NODE* makeLable();




#endif
