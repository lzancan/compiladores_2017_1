#ifndef HASH
#define HASH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"

#define HASH_SIZE 997

// estrutura do nodo da hash

struct HASH_NODE{
	int type;
	char * value;
	struct HASH_NODE * next;	
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




#endif
