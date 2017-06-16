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
	new_node -> valueType = 0;

	return new_node;

}

int uncompile(ASTREE* node)
{
	if(!node) return 0;
	switch(node -> type){
		case ASTREE_DECLARACAO: {
			uncompile(node->son[0]);
			uncompile(node->son[1]);
		}; break;
		case ASTREE_SYMBOL: fprintf(outfile, "ASTREE_SYMBOL"); break; //????????
		case ASTREE_PROGRAMA: uncompile(node->son[0]); break;
		case ASTREE_FUNCAO:  {
			uncompile(node->son[0]);
			uncompile(node->son[1]);
			fprintf(outfile,";");
			fprintf(outfile,"\n");
		}; break;
		case ASTREE_VAR_GLOBAL: {
			fprintf(outfile,"%s", node->symbol->value); //não sei se é isso
			fprintf(outfile, ": ");
			uncompile(node->son[0]);
			fprintf(outfile, " ");
			uncompile(node->son[1]);
			fprintf(outfile, ";\n");
			} break;
		case ASTREE_VAR_GLOBAL_INIT_VEC: {
			fprintf(outfile, "[");
			fprintf(outfile,"%s", node->symbol->value); //não sei se é isso
			fprintf(outfile, "]");
			uncompile(node->son[0]);
			} break;
		case ASTREE_BYTE_TYPE: fprintf(outfile, "byte "); break;
		case ASTREE_SHORT_TYPE: fprintf(outfile, "short "); break;
		case ASTREE_LONG_TYPE:  fprintf(outfile, "long "); break;
		case ASTREE_FLOAT_TYPE:  fprintf(outfile, "float "); break;
		case ASTREE_DOUBLE_TYPE: fprintf(outfile, "double "); break;
		case ASTREE_FUNC_CABECALHO: {
			fprintf(outfile, "\n");
			uncompile(node->son[0]);
			fprintf(outfile, " ");
			if(node->symbol)
			fprintf(outfile,"%s", node->symbol->value); //não sei se é isso
			fprintf(outfile, "(");
			uncompile(node->son[1]);
			fprintf(outfile, ")\n");
			} break;
		case ASTREE_LISTA_PARAMETROS:  {
			uncompile(node->son[0]);
			if(node->symbol)
			fprintf(outfile,"%s", node->symbol->value); //não sei se é isso
			uncompile(node->son[1]);
		}; break;
		case ASTREE_MAIS_PARAMETROS:  {
			fprintf(outfile, ",");
			uncompile(node->son[0]);
			if(node->symbol)
			fprintf(outfile,"%s", node->symbol->value); //não sei se é isso
			uncompile(node->son[1]);
		}; break;
		case ASTREE_BLOCO_COMANDOS: {
			fprintf(outfile, "{\n");
			uncompile(node->son[0]);
			fprintf(outfile, "}\n");
		}; break;
		case ASTREE_LISTA_COMANDOS: {
			uncompile(node->son[0]);
			fprintf(outfile, ";\n");
			uncompile(node->son[1]);
			} break;
		case ASTREE_ATRIBUICAO: {
			if(node->symbol)
			fprintf(outfile,"%s", node->symbol->value); //não sei se é isso
			fprintf(outfile, "=");
			uncompile(node->son[0]);
			} break;
		case ASTREE_ATRIBUICAO_VETOR: {
			if(node->symbol)
			fprintf(outfile,"%s", node->symbol->value); //não sei se é isso
			fprintf(outfile, "#");
			uncompile(node->son[0]);
			fprintf(outfile, "=");
			uncompile(node->son[1]);
			} break;
		case ASTREE_READ:{
			fprintf(outfile, "read ");
			if(node->symbol)
			fprintf(outfile,"%s", node->symbol->value); //não sei se é isso
			} break;
		case ASTREE_PRINT: {
			fprintf(outfile, "print ");
			if(node->son[0]->type == ASTREE_LITERAL)
				fprintf (outfile,"\"");
			uncompile(node->son[0]);
			if(node->son[0]->type == ASTREE_LITERAL)
				fprintf (outfile,"\"");
			} break;
		case ASTREE_PRINT_LISTA: {
			if(node->son[0]->type == ASTREE_LITERAL)
				fprintf (outfile,"\"");
			uncompile(node->son[0]);
			if(node->son[0]->type == ASTREE_LITERAL)
				fprintf (outfile,"\"");
			if(node->son[1]->type == ASTREE_LITERAL)
				fprintf (outfile,"\"");
			uncompile(node->son[1]);
			if(node->son[1]->type == ASTREE_LITERAL)
				fprintf (outfile,"\"");
		} break;
		case ASTREE_RETURN: {
			fprintf(outfile, "return ");
			uncompile(node->son[0]);

			} break;
		case ASTREE_LISTA_FUNC_PARAMETROS: {
			uncompile(node->son[0]);
			uncompile(node->son[1]);
			} break;
		case ASTREE_LISTA_FUNC_MAIS_PARAMETROS:  {
			fprintf(outfile, ",");
			uncompile(node->son[0]);
			if(node->symbol)
			fprintf(outfile,"%s", node->symbol->value); //não sei se é isso
			uncompile(node->son[1]);
		}; break;
		case ASTREE_WHEN_THEN:  {
			fprintf(outfile, "when ");
			fprintf(outfile, "(");
			uncompile(node->son[0]);
			fprintf(outfile, ")");
			fprintf(outfile, "then ");
			uncompile(node->son[1]);
			fprintf(outfile, "\n");
			} break;
		case ASTREE_WHEN_THEN_ELSE: {
			fprintf(outfile, "when ");
			fprintf(outfile, "(");
			uncompile(node->son[0]);
			fprintf(outfile, ")");
			fprintf(outfile, "then ");
			uncompile(node->son[1]);
			fprintf(outfile, " else ");
			uncompile(node->son[2]);
			fprintf(outfile, "\n");
			} break;
		case ASTREE_WHILE: {
			fprintf(outfile, "while");
			fprintf(outfile, "(");
			uncompile(node->son[0]);
			fprintf(outfile, ")");
			uncompile(node->son[1]);
			} break;
		case ASTREE_FOR: {
			fprintf(outfile, "for");
			fprintf(outfile, "(");
			if(node->symbol)
			fprintf(outfile,"%s", node->symbol->value); //não sei se é isso
			fprintf(outfile, "=");
			uncompile(node->son[0]);
			fprintf(outfile, " to ");
			uncompile(node->son[1]);
			fprintf(outfile, ")");
			uncompile(node->son[2]);
			} break;
		case ASTREE_EXPRESSAO_FUNCAO: {
			if(node->symbol)
			fprintf(outfile,"%s", node->symbol->value); //não sei se é isso
			fprintf(outfile, "(");
			uncompile(node->son[0]);
			fprintf(outfile, ")");
			} break;
		case ASTREE_EXPRESSAO_VETOR: {
			if(node->symbol)
			fprintf(outfile,"%s", node->symbol->value); //não sei se é isso
			uncompile(node->son[0]);
			} break;
		case ASTREE_PARENTESES: {
			fprintf(outfile, "(");
			uncompile(node->son[0]);
			fprintf(outfile, ")");
			} break;
		case ASTREE_COLCHETES: {
			fprintf(outfile, "[");
			uncompile(node->son[0]);
			fprintf(outfile, "]");
			} break;
		case ASTREE_NEGATIVO: {
			fprintf(outfile, "-");
			uncompile(node->son[0]);
			} break;
		case ASTREE_NEGADO: {
			fprintf(outfile, "!");
			uncompile(node->son[0]);
			} break;
		case ASTREE_IDENTIFIER:
			if(node->symbol)
				fprintf(outfile,"%s", node->symbol->value); break; //não sei se é isso
		case ASTREE_LITERAL: {
			if(node->symbol)
				if(node->symbol->type == SYMBOL_LIT_CHAR)
					fprintf (outfile,"\'");
			fprintf(outfile,"%s", node->symbol->value);
			if(node->symbol->type == SYMBOL_LIT_CHAR)
				fprintf (outfile,"\'");
			} break;
		case ASTREE_ADD: {
			uncompile(node->son[0]);
			fprintf(outfile, "+");
			uncompile(node->son[1]);
			} break;
		case ASTREE_SUB: {
			uncompile(node->son[0]);
			fprintf(outfile, "-");
			uncompile(node->son[1]);
			} break;
		case ASTREE_MUL:  {
			uncompile(node->son[0]);
			fprintf(outfile, "*");
			uncompile(node->son[1]);
			} break;
		case ASTREE_DIV:  {
			uncompile(node->son[0]);
			fprintf(outfile, "/");
			uncompile(node->son[1]);
			} break;
		case ASTREE_LESS_THAN:  {
			uncompile(node->son[0]);
			fprintf(outfile, "<");
			uncompile(node->son[1]);
			} break;
		case ASTREE_GREATER_THAN:  {
			uncompile(node->son[0]);
			fprintf(outfile, ">");
			uncompile(node->son[1]);
			} break;
		case ASTREE_LE:  {
			uncompile(node->son[0]);
			fprintf(outfile, "<=");
			uncompile(node->son[1]);
			} break;
		case ASTREE_GE:  {
			uncompile(node->son[0]);
			fprintf(outfile, ">=");
			uncompile(node->son[1]);
			} break;
		case ASTREE_EQ:  {
			uncompile(node->son[0]);
			fprintf(outfile, "==");
			uncompile(node->son[1]);
			} break;
		case ASTREE_NE:  {
			uncompile(node->son[0]);
			fprintf(outfile, "!=");
			uncompile(node->son[1]);
			} break;
		case ASTREE_AND:  {
			uncompile(node->son[0]);
			fprintf(outfile, "&&");
			uncompile(node->son[1]);
			} break;
		case ASTREE_OR:  {
			uncompile(node->son[0]);
			fprintf(outfile, "||");
			uncompile(node->son[1]);
			} break;
		case ASTREE_VAR_GLOBAL_VEC_VALORES: {
			fprintf (outfile," ");
			uncompile(node->son[0]);
			uncompile(node->son[1]);
			} break;
		case ASTREE_DEBUG: break;
		default: fprintf(outfile, "\nDEFAULT\n");break;
	}
}
