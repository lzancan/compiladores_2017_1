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
		case ASTREE_SYMBOL: fprintf(stderr, "ASTREE_SYMBOL"); break;	
		case ASTREE_PROGRAMA: fprintf(stderr, "ASTREE_PROGRAMA"); break;
		case ASTREE_DECLARACAO_VAR_GLOBAL: fprintf(stderr, "ASTREE_DECLARACAO_VAR_GLOBAL"); break;
		case ASTREE_VAR_GLOBAL_INIT_VEC: fprintf(stderr, "ASTREE_VAR_GLOBAL_INIT_VEC"); break;
		case ASTREE_LITERAL: fprintf(stderr, "ASTREE_LITERAL"); break;
		case ASTREE_BYTE_TYPE: fprintf(stderr, "ASTREE_BYTE_TYPE"); break;
		case ASTREE_SHORT_TYPE: fprintf(stderr, "ASTREE_SHORT_TYPE"); break;
		case ASTREE_LONG_TYPE:  fprintf(stderr, "ASTREE_LONG_TYPE"); break;
		case ASTREE_FLOAT_TYPE:  fprintf(stderr, "ASTREE_FLOAT_TYPE"); break;
		case ASTREE_DOUBLE_TYPE: fprintf(stderr, "ASTREE_DOUBLE_TYPE"); break;
		case ASTREE_FUNC_CABECALHO: fprintf(stderr, "ASTREE_FUNC_CABECALHO"); break;
		case ASTREE_LISTA_PARAMETROS: fprintf(stderr, "ASTREE_LISTA_PARAMETROS"); break;
		case ASTREE_MAIS_PARAMETROS: fprintf(stderr, "ASTREE_MAIS_PARAMETROS"); break;
		case ASTREE_BLOCO_COMANDOS: fprintf(stderr, "ASTREE_BLOCO_COMANDOS"); break;
		case ASTREE_LISTA_COMANDOS: fprintf(stderr, "ASTREE_LISTA_COMANDOS"); break;
		case ASTREE_ATRIBUICAO: fprintf(stderr, "ASTREE_ATRIBUICAO"); break;
		case ASTREE_READ: fprintf(stderr, "ASTREE_READ"); break;
		case ASTREE_PRINT: fprintf(stderr, "ASTREE_PRINT"); break;
		case ASTREE_RETURN: fprintf(stderr, "ASTREE_RETURN"); break;
		case ASTREE_EXPRESSAO: fprintf(stderr, "ASTREE_EXPRESSAO"); break;
		case ASTREE_EXPRESSAO_IDENTIFIER: fprintf(stderr, "ASTREE_EXPRESSAO_IDENTIFIER"); break;
		case ASTREE_EXPRESSAO_LITERAL: fprintf(stderr, "ASTREE_EXPRESSAO_LITERAL"); break;
		case ASTREE_EXPRESSAO_ADD: fprintf(stderr, "ASTREE_EXPRESSAO_ADD"); break;
		case ASTREE_EXPRESSAO_SUB: fprintf(stderr, "ASTREE_EXPRESSAO_SUB"); break;
		case ASTREE_EXPRESSAO_MUL: fprintf(stderr, "ASTREE_EXPRESSAO_MUL"); break;
		case ASTREE_EXPRESSAO_DIV: fprintf(stderr, "ASTREE_EXPRESSAO_DIV"); break;
		case ASTREE_EXPRESSAO_LESS_THAN: fprintf(stderr, "ASTREE_EXPRESSAO_LESS_THAN"); break;
		case ASTREE_EXPRESSAO_GREATER_THAN: fprintf(stderr, "ASTREE_EXPRESSAO_GREATER_THAN"); break;
		case ASTREE_EXPRESSAO_LE: fprintf(stderr, "ASTREE_EXPRESSAO_LE"); break;
		case ASTREE_EXPRESSAO_GE: fprintf(stderr, "ASTREE_EXPRESSAO_GE"); break;
		case ASTREE_EXPRESSAO_EQ: fprintf(stderr, "ASTREE_EXPRESSAO_EQ"); break;
		case ASTREE_EXPRESSAO_NE: fprintf(stderr, "ASTREE_EXPRESSAO_NE"); break;
		case ASTREE_EXPRESSAO_AND: fprintf(stderr, "ASTREE_EXPRESSAO_AND"); break;
		case ASTREE_EXPRESSAO_OR: fprintf(stderr, "ASTREE_EXPRESSAO_OR"); break;
		case ASTREE_EXPRESSAO_NEG: fprintf(stderr, "ASTREE_EXPRESSAO_NEG"); break;
		case ASTREE_LISTA_FUNC_PARAMETROS: fprintf(stderr, "ASTREE_LISTA_FUNC_PARAMETROS"); break;
		case ASTREE_WHEN_THEN: fprintf(stderr, "ASTREE_WHEN_THEN"); break;
		case ASTREE_WHEN_THEN_ELSE: fprintf(stderr, "ASTREE_WHEN_THEN_ELSE"); break;
		case ASTREE_WHILE: fprintf(stderr, "ASTREE_WHILE"); break;
		case ASTREE_FOR: fprintf(stderr, "ASTREE_FOR"); break;
	}
	
	if(node -> symbol){
		fprintf(stderr, ", %s]\n", node->symbol->value);	
	} else{
		fprintf(stderr, ",]\n");	
	}

	for(i = 0; i < MAX_SONS; i++){
		astreePrint(node -> son[i]);
	}

}
