#include <stdlib.h>
#include <stdio.h>
#include "hash.h"


#define MAXSONS 4

struct ASTREE
{
	int type;
	HASH_NODE* node;
	struct ASTREE* son[MAXSONS];
};
typedef struct ASTREE ASTREE;


ASTREE* astreeCreate (int type, HASH_NODE* symbol, ASTREE* son0, ASTREE* son1, ASTREE* son2, ASTREE* son3);
void astreePrint(int level, ASTREE* node);
