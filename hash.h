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


void startHash();
void printHash();
hashNode * insertHash(char * text, int type);




#endif
