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
/*
void astreePrint(int level, ASTREE* node){
	int i =0;
	if(!node) return;
	
	switch (level){
		case 0: break;
		case 1: fprintf(stderr, "   "); break;
		case 2: fprintf(stderr, "      "); break;
		case 3: fprintf(stderr, "         "); break;
		case 4: fprintf(stderr, "            "); break;
		default: break;
	}

	fprintf(stderr, "ASTREE(");
	switch(node -> type){
		case ASTREE_DECLARACAO: fprintf (stderr, "ASTREE_DECLARACAO"); break;
		case ASTREE_SYMBOL: fprintf(stderr, "ASTREE_SYMBOL"); break;	
		case ASTREE_PROGRAMA: fprintf(stderr, "ASTREE_PROGRAMA"); break;
		case ASTREE_FUNCAO: fprintf(stderr, "ASTREE_FUNCAO"); break;
		case ASTREE_VAR_GLOBAL: fprintf(stderr, "ASTREE_VAR_GLOBAL"); break;
		case ASTREE_VAR_GLOBAL_INIT_VEC: fprintf(stderr, "ASTREE_VAR_GLOBAL_INIT_VEC"); break;
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
		case ASTREE_ATRIBUICAO_VETOR: fprintf(stderr, "ASTREE_ATRIBUICAO_VETOR"); break;

		case ASTREE_READ: fprintf(stderr, "ASTREE_READ"); break;
		case ASTREE_PRINT: fprintf(stderr, "ASTREE_PRINT"); break;
		case ASTREE_RETURN: fprintf(stderr, "ASTREE_RETURN"); break;
		
	
		case ASTREE_LISTA_FUNC_PARAMETROS: fprintf(stderr, "ASTREE_LISTA_FUNC_PARAMETROS"); break;
		case ASTREE_WHEN_THEN: fprintf(stderr, "ASTREE_WHEN_THEN"); break;
		case ASTREE_WHEN_THEN_ELSE: fprintf(stderr, "ASTREE_WHEN_THEN_ELSE"); break;
		case ASTREE_WHILE: fprintf(stderr, "ASTREE_WHILE"); break;
		case ASTREE_FOR: fprintf(stderr, "ASTREE_FOR"); break;

		// expressão:
		case ASTREE_EXPRESSAO_FUNCAO: {
			fprintf(stderr, "ASTREE_EXPRESSAO_FUNCAO");
			} break;
		case ASTREE_EXPRESSAO_VETOR: fprintf(stderr, "ASTREE_EXPRESSAO_VETOR");break;
		case ASTREE_PARENTESES:	fprintf(stderr, "ASTREE_PARENTESES"); break;
		case ASTREE_COLCHETES: fprintf(stderr, "ASTREE_COLCHETES"); break;
		case ASTREE_NEGATIVO: fprintf(stderr, "ASTREE_NEGATIVO"); break;
		case ASTREE_NEGADO: fprintf(stderr, "ASTREE_NEGADO	"); break;
		case ASTREE_IDENTIFIER: fprintf(stderr, "ASTREE_IDENTIFIER"); break;
		case ASTREE_LITERAL: fprintf(stderr, "ASTREE_LITERAL"); break;
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
		default: break;
	}
	
	if(node -> symbol){
		fprintf(stderr, ", [%s] )\n", node->symbol->value);	
	} else{
		fprintf(stderr, ")\n");	
	}

	for(i = 0; i <= MAX_SONS; i++){
		astreePrint(i, node -> son[i]);
	}

}
*/
int uncompile(ASTREE* node)
{
	if(!node) return;
	switch(node -> type){
		case ASTREE_DECLARACAO: {
			uncompile(node->son[0]);
			uncompile(node->son[1]);
		}; break;
		case ASTREE_SYMBOL: fprintf(stderr, "ASTREE_SYMBOL"); break; //????????
		case ASTREE_PROGRAMA: uncompile(node->son[0]); break;
		case ASTREE_FUNCAO:  {
			uncompile(node->son[0]);
			uncompile(node->son[1]);
		}; break;
		case ASTREE_VAR_GLOBAL: {
			fprintf(stderr, node->symbol->value); //não sei se é isso
			fprintf(stderr, ": ");
			uncompile(node->son[0]);
			fprintf(stderr, " ");
			uncompile(node->son[1]);
			fprintf(stderr, ";\n");
			} break;
		case ASTREE_VAR_GLOBAL_INIT_VEC: {
			fprintf(stderr, "[");
			fprintf(stderr, node->symbol->value); //não sei se é isso
			fprintf(stderr, "]");
			uncompile(node->son[0]);
			} break;
		case ASTREE_BYTE_TYPE: fprintf(stderr, "byte"); break;
		case ASTREE_SHORT_TYPE: fprintf(stderr, "short"); break;
		case ASTREE_LONG_TYPE:  fprintf(stderr, "long"); break;
		case ASTREE_FLOAT_TYPE:  fprintf(stderr, "float"); break;
		case ASTREE_DOUBLE_TYPE: fprintf(stderr, "double"); break;
		case ASTREE_FUNC_CABECALHO: {
			uncompile(node->son[0]);
			fprintf(stderr, " ");
			if(node->symbol)
			fprintf(stderr, node->symbol->value); //não sei se é isso
			fprintf(stderr, "(");
			uncompile(node->son[1]);
			fprintf(stderr, ")\n");
			} break;
		case ASTREE_LISTA_PARAMETROS:  {
			uncompile(node->son[0]);
			if(node->symbol)
			fprintf(stderr, node->symbol->value); //não sei se é isso
			uncompile(node->son[1]);
		}; break;
		case ASTREE_MAIS_PARAMETROS:  {
			fprintf(stderr, ",");
			uncompile(node->son[0]);
			if(node->symbol)
			fprintf(stderr, node->symbol->value); //não sei se é isso
			uncompile(node->son[1]);
		}; break;
		case ASTREE_BLOCO_COMANDOS: {
			fprintf(stderr, "{");
			uncompile(node->son[0]);
			fprintf(stderr, "}");
		}; break;
		case ASTREE_LISTA_COMANDOS: {
			uncompile(node->son[0]);
			fprintf(stderr, ";");
			uncompile(node->son[1]);
			} break;
		case ASTREE_ATRIBUICAO: {
			if(node->symbol)
			fprintf(stderr, node->symbol->value); //não sei se é isso
			fprintf(stderr, "=");
			uncompile(node->son[0]);
			} break;
		case ASTREE_ATRIBUICAO_VETOR: {
			if(node->symbol)
			fprintf(stderr, node->symbol->value); //não sei se é isso
			fprintf(stderr, "#");
			uncompile(node->son[0]);
			fprintf(stderr, "=");
			uncompile(node->son[1]);
			} break;
		case ASTREE_READ:{
			fprintf(stderr, "read");
			if(node->symbol)
			fprintf(stderr, node->symbol->value); //não sei se é isso
			} break;
		case ASTREE_PRINT: {
			fprintf(stderr, "print \"");
			uncompile(node->son[0]);
			fprintf(stderr, "\"");
			} break;
		case ASTREE_RETURN: {
			fprintf(stderr, "return");
			uncompile(node->son[0]);
			} break;
		case ASTREE_LISTA_FUNC_PARAMETROS: {
			uncompile(node->son[0]);
			fprintf(stderr, ",");
			uncompile(node->son[1]);
			} break;
		case ASTREE_WHEN_THEN:  {
			fprintf(stderr, "when");
			fprintf(stderr, "(");
			uncompile(node->son[0]);
			fprintf(stderr, ")");
			fprintf(stderr, "then");
			uncompile(node->son[1]);
			} break;
		case ASTREE_WHEN_THEN_ELSE: {
			fprintf(stderr, "when");
			fprintf(stderr, "(");
			uncompile(node->son[0]);
			fprintf(stderr, ")");
			fprintf(stderr, "then");
			uncompile(node->son[1]);
			fprintf(stderr, "else");
			uncompile(node->son[2]);
			} break;
		case ASTREE_WHILE: {
			fprintf(stderr, "while");
			fprintf(stderr, "(");
			uncompile(node->son[0]);
			fprintf(stderr, ")");
			uncompile(node->son[1]);
			} break;
		case ASTREE_FOR: {
			fprintf(stderr, "for");
			fprintf(stderr, "(");
			if(node->symbol)
			fprintf(stderr, node->symbol->value); //não sei se é isso
			fprintf(stderr, "=");
			uncompile(node->son[0]);
			fprintf(stderr, "to");
			uncompile(node->son[1]);
			fprintf(stderr, ")");
			uncompile(node->son[2]);
			} break;
		case ASTREE_EXPRESSAO_FUNCAO: {
			if(node->symbol)
			fprintf(stderr, node->symbol->value); //não sei se é isso
			fprintf(stderr, "(");
			uncompile(node->son[0]);
			fprintf(stderr, ")");
			} break;
		case ASTREE_EXPRESSAO_VETOR: {
			if(node->symbol)
			fprintf(stderr, node->symbol->value); //não sei se é isso
			uncompile(node->son[0]);
			} break;
		case ASTREE_PARENTESES: {
			fprintf(stderr, "(");
			uncompile(node->son[0]);
			fprintf(stderr, ")");
			} break;
		case ASTREE_COLCHETES: {
			fprintf(stderr, "[");
			uncompile(node->son[0]);
			fprintf(stderr, "]");
			} break;
		case ASTREE_NEGATIVO: {
			fprintf(stderr, "-");
			uncompile(node->son[0]);
			} break;
		case ASTREE_NEGADO: {
			fprintf(stderr, "!");
			uncompile(node->son[0]);
			} break;
		case ASTREE_IDENTIFIER: 			
			if(node->symbol) 
				fprintf(stderr, node->symbol->value); break; //não sei se é isso
		case ASTREE_LITERAL: 			
			if(node->symbol) 
				fprintf(stderr, node->symbol->value); break; //não sei se é isso
		case ASTREE_ADD: {
			uncompile(node->son[0]);
			fprintf(stderr, "+");
			uncompile(node->son[1]);
			} break;
		case ASTREE_SUB: {
			uncompile(node->son[0]);
			fprintf(stderr, "-");
			uncompile(node->son[1]);
			} break;
		case ASTREE_MUL:  {
			uncompile(node->son[0]);
			fprintf(stderr, "*");
			uncompile(node->son[1]);
			} break;
		case ASTREE_DIV:  {
			uncompile(node->son[0]);
			fprintf(stderr, "/");
			uncompile(node->son[1]);
			} break;
		case ASTREE_LESS_THAN:  {
			uncompile(node->son[0]);
			fprintf(stderr, "<");
			uncompile(node->son[1]);
			} break;
		case ASTREE_GREATER_THAN:  {
			uncompile(node->son[0]);
			fprintf(stderr, ">");
			uncompile(node->son[1]);
			} break;
		case ASTREE_LE:  {
			uncompile(node->son[0]);
			fprintf(stderr, "<=");
			uncompile(node->son[1]);
			} break;
		case ASTREE_GE:  {
			uncompile(node->son[0]);
			fprintf(stderr, ">=");
			uncompile(node->son[1]);
			} break;
		case ASTREE_EQ:  {
			uncompile(node->son[0]);
			fprintf(stderr, "==");
			uncompile(node->son[1]);
			} break;
		case ASTREE_NE:  {
			uncompile(node->son[0]);
			fprintf(stderr, "!=");
			uncompile(node->son[1]);
			} break;
		case ASTREE_AND:  {
			uncompile(node->son[0]);
			fprintf(stderr, "&&");
			uncompile(node->son[1]);
			} break;
		case ASTREE_OR:  {
			uncompile(node->son[0]);
			fprintf(stderr, "||");
			uncompile(node->son[1]);
			} break;
		case ASTREE_DEBUG: break;
		default: fprintf(stderr, "\nDEFAULT\n");break;
	}
}
