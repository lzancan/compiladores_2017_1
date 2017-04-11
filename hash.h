#ifndef HASH
#define HASH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"

#define HASH_SIZE 997

/* estrutura para o nodo da hash */

struct hashNode;
struct hashNode
{
	int type;
	char * value;
	struct hashNode * next;
	
};
typedef struct hashNode hashNode;

// hash global
hashNode * hashTable[HASH_SIZE];


void initHash();// inicializa a hash, fazendo os nodos serem null
void printHash(); // imprime a hash toda
void printToken(int token);// imprime um token
int hashAddress(char *value); // gera o endereço hash baseado no nome (char *value)
hashNode * insertHash(char * value, int type);
void printNode(hashNode * node); // imprime um nodo da hash
hashNode *getNode(char *value); // procura por um nodo na hash, retorna null se não encontrou
char * addTerminator(char* value); // adiciona "\0" ao final de uma string




#endif
