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

void astreePrint(ASTREE* node){
	int i =0;
	if(!node) return;
	fprintf(stderr, "ASTREE(");

	switch(node -> type){

		case ASTREE_VAR_GLOBAL: fprintf(stderr, "ASTREE_VAR_GLOBAL"); break;
		case ASTREE_EXPRESSAO: fprintf(stderr, "ASTREE_EXPRESSAO"); break;
		case ASTREE_ATRIBUICAO: fprintf(stderr, "ASTREE_ATRIBUICAO"); break;
		case ASTREE_BLOCO_COMANDOS: fprintf(stderr, "ASTREE_BLOCO_COMANDOS"); break;
		case ASTREE_LISTA_COMANDOS: fprintf(stderr, "ASTREE_LISTA_COMANDOS"); break;
		case ASTREE_LITERAL: fprintf(stderr, "ASTREE_LITERAL"); break;
		case ASTREE_FUNCAO: fprintf(stderr, "ASTREE_FUNCAO"); break;	
		
		case ASTREE_ADD: fprintf(stderr, "ASTREE_ADD"); break;
		case ASTREE_SUB: fprintf(stderr, "ASTREE_SUB"); break;
		case ASTREE_MUL: fprintf(stderr, "ASTREE_MUL"); break;
		case ASTREE_DIV: fprintf(stderr, "ASTREE_DIV"); break;
		case ASTREE_LESS_THAN: fprintf(stderr, "ASTREE_LESS_THAN"); break;
		case ASTREE_GREATER_THAN: fprintf(stderr, "ASTREE_GREATER_THAN"); break;
		case ASTREE_LE: fprintf(stderr, "ASTREE_LE"); break;
		case ASTREE_GE: fprintf(stderr, "ASTREE_GE"); break;
		case ASTREE_EQ: fprintf(stderr, "ASTREE_EQ"); break;
		case ASTREE_NE: fprintf(stderr, "ASTREE_NE"); break;
		case ASTREE_AND: fprintf(stderr, "ASTREE_AND"); break;
		case ASTREE_OR: fprintf(stderr, "ASTREE_OR"); break;
		

		
	}
	
	if(node -> symbol){
		fprintf(stderr, ", %s]\n", node->symbol->value);	
	} else{
		fprintf(stderr, ",)\n");	
	}

	for(i = 0; i < MAX_SONS; i++){
		astreePrint(node -> son[i]);
	}

}
