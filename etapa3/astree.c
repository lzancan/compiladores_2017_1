#include <stdio.h>
#include <stdlib.h>
#include "astree.h"

ASTREE* astreeCreate (int type, HASH_NODE* symbol, ASTREE* son0, ASTREE* son1, ASTREE* son2, ASTREE* son3){
	ASTREE* new_node = 0;
	
	new_node = calloc(1,sizeof(ASTREE));
	new_node -> type = type;
	new_node -> symbol = symbol;
	new_node -> son[0] = son0;
	new_node -> son[1] = son1;
	new_node -> son[2] = son2;
	new_node -> son[3] = son3;

	return new_node;

}

void astreePrint(int level, ASTREE* node){
	int i =0;
	if(!node) return;
	for(i = 0; i < level; i++){
		fprint(	
	}

}
