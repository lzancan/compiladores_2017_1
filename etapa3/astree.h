#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

#define MAX_SONS 4

enum astreeNodeType
{
	ASTREE_VAR_GLOBAL,
	ASTREE_EXPRESSAO,
	ASTREE_FUNCAO,
	ASTREE_LITERAL,
	ASTREE_BLOCO_COMANDOS,
	ASTREE_LISTA_COMANDOS,
	ASTREE_ATRIBUICAO,
	ASTREE_ADD,
	ASTREE_SUB,
	ASTREE_MUL,
	ASTREE_DIV,
	ASTREE_LESS_THAN,
	ASTREE_GREATER_THAN,
	ASTREE_LE,
	ASTREE_GE,
	ASTREE_EQ,
	ASTREE_NE,
	ASTREE_AND,
	ASTREE_OR
};


struct ASTREE
{
	int type;
	HASH_NODE* symbol;
	struct ASTREE* son[MAX_SONS];
};
typedef struct ASTREE ASTREE;


ASTREE* astreeCreate (int type, HASH_NODE* symbol, ASTREE* son0, ASTREE* son1, ASTREE* son2, ASTREE* son3);
void astreePrint(ASTREE* node);
