#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tacs.h"


TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2){
	TAC* newTac = 0;
	newTac = calloc(1,sizeof(TAC));
	newTac->type = type;
	newTac->res = res;
	newTac->op1 = op1;
	newTac->op2 = op2;
	newTac->prev = 0;
	newTac->next = 0;
	return newTac;
}

TAC* tacJoin(TAC* l1, TAC* l2){
	TAC* tac;
	if(!l1) return l2;
	if(!l2) return l1;
	tac = l2;
	while(tac->prev){
		tac = tac->prev;
	}
	tac->prev = l1;
	return l2;
}

TAC* tacGenerate(ASTREE* node){
	int i=0;
	TAC* code[MAX_SONS];
	TAC* result = 0;

	if(!node) return 0;

	// processa o filho primeiro
	for(i=0; i<MAX_SONS; i++){
		code[i] = tacGenerate(node->son[i]);
	}

	// processa esse nodo
	switch(node->type){
		case ASTREE_SYMBOL: result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0); break;
		case ASTREE_LITERAL: result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0); break;
		case ASTREE_IDENTIFIER: result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0); break;
		case ASTREE_READ: result = tacCreate(TAC_READ, node->symbol, 0, 0); break;
		case ASTREE_ADD: result = tacJoin(code[0], tacJoin(code[1], tacCreate(TAC_ADD, makeTemp(), code[0] ? code[0]->res : 0, code[1]? code[1]->res : 0))); break;
		case ASTREE_SUB: result = tacJoin(code[0], tacJoin(code[1], tacCreate(TAC_SUB, makeTemp(), code[0] ? code[0]->res : 0, code[1]? code[1]->res : 0))); break;
		case ASTREE_MUL: result = tacJoin(code[0], tacJoin(code[1], tacCreate(TAC_MUL, makeTemp(), code[0] ? code[0]->res : 0, code[1]? code[1]->res : 0))); break;
		case ASTREE_DIV: result = tacJoin(code[0], tacJoin(code[1], tacCreate(TAC_DIV, makeTemp(), code[0] ? code[0]->res : 0, code[1]? code[1]->res : 0))); break;

		case ASTREE_LESS_THAN:  result = tacJoin(code[0], tacJoin(code[1], tacCreate(TAC_LT, makeTemp(), code[0] ? code[0]->res : 0, code[1]? code[1]->res : 0))); break;
		case ASTREE_GREATER_THAN:  result = tacJoin(code[0], tacJoin(code[1], tacCreate(TAC_GT, makeTemp(), code[0] ? code[0]->res : 0, code[1]? code[1]->res : 0))); break;
		case ASTREE_LE:  result = tacJoin(code[0], tacJoin(code[1], tacCreate(TAC_LE, makeTemp(), code[0] ? code[0]->res : 0, code[1]? code[1]->res : 0))); break;
		case ASTREE_GE:  result = tacJoin(code[0], tacJoin(code[1], tacCreate(TAC_GE, makeTemp(), code[0] ? code[0]->res : 0, code[1]? code[1]->res : 0))); break;
		case ASTREE_EQ:  result = tacJoin(code[0], tacJoin(code[1], tacCreate(TAC_EQ, makeTemp(), code[0] ? code[0]->res : 0, code[1]? code[1]->res : 0))); break;
		case ASTREE_NE:  result = tacJoin(code[0], tacJoin(code[1], tacCreate(TAC_NE, makeTemp(), code[0] ? code[0]->res : 0, code[1]? code[1]->res : 0))); break;
		case ASTREE_AND:  result = tacJoin(code[0], tacJoin(code[1], tacCreate(TAC_AND, makeTemp(), code[0] ? code[0]->res : 0, code[1]? code[1]->res : 0))); break;
		case ASTREE_OR:  result = tacJoin(code[0], tacJoin(code[1], tacCreate(TAC_OR, makeTemp(), code[0] ? code[0]->res : 0, code[1]? code[1]->res : 0))); break;
		case ASTREE_NEGATIVO:  result = tacJoin(code[0], tacCreate(TAC_NEGATIVO, makeTemp(), code[0] ? code[0]->res : 0, 0)); break;
		case ASTREE_NEGADO:  result = tacJoin(code[0], tacCreate(TAC_NEGADO, makeTemp(), code[0] ? code[0]->res : 0, 0)); break;
		case ASTREE_FOR: result = makeFor(node->symbol, code[0], code[1], code[2]); break;
		case ASTREE_WHILE: result = makeWhile(code[0], code[1]); break;
		case ASTREE_WHEN_THEN: result = makeWhenThen(code[0], code[1]); break;
		case ASTREE_WHEN_THEN_ELSE: result = makeWhenThenElse(code[0], code[1], code[2]); break;
		case ASTREE_PRINT_LISTA: result = tacJoin(tacCreate(TAC_PRINT, node->symbol, code[0]?code[0]->res:0, 0), code[1]?code[1]:0); break;
		case ASTREE_PRINT_ELEMENT: result = tacJoin(code[0], tacJoin(tacCreate(TAC_PRINT, node->symbol, code[0]?code[0]->res:0, code[1]?code[1]->res:0), code[1]?code[1]:0)); break;

		case ASTREE_ATRIBUICAO: 
				result = tacJoin(code[0], tacJoin(code[1], tacCreate(TAC_MOVE, node->symbol, code[0]?code[0]->res:0, code[1]?code[1]->res:0)));
				if(node->son[0]){ if(node->son[0]->symbol){ if(node->son[0]->symbol->nature == NATURE_FUNCTION){
						result = tacJoin(code[0], tacJoin(code[1], tacCreate(TAC_MOVE, node->symbol, node->son[0]->symbol, code[1]?code[1]->res:0)));
					}}}
					break;

		case ASTREE_ATRIBUICAO_VETOR: result = tacJoin(code[0], tacJoin(code[1], tacCreate(TAC_MOVE_VETOR, node->symbol, code[0]?code[0]->res:0, code[1]? code[1]->res:0))); break;

		case ASTREE_EXPRESSAO_VETOR: result = tacJoin(code[0], tacJoin(code[1], tacCreate(TAC_EXPRESSAO_VETOR, makeTemp(), node->symbol, code[0]? code[0]->res:0))); break;
		
		
		case ASTREE_RETURN: result = tacJoin(code[0], tacCreate(TAC_RETURN, node->symbol, code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;

		case ASTREE_FUNC_CABECALHO: result = tacJoin(tacCreate(TAC_FUNCPUSH, node->symbol, code[0]?code[0]->res:0, 0), tacJoin(code[0], code[1])); break;  

		case ASTREE_LISTA_PARAMETROS: result = tacJoin(tacCreate(TAC_PARAMETRO, node->symbol, 0, 0), tacJoin(code[0], code[1])); break;

		case ASTREE_MAIS_PARAMETROS: result = tacJoin(tacCreate(TAC_PARAMETRO, node->symbol, 0, 0), tacJoin(code[0], code[1])); break;
		
		case ASTREE_LISTA_FUNC_PARAMETROS: result = tacJoin(code[0], tacJoin(tacCreate(TAC_PARAMETRO_CALL, node->symbol, code[0]?code[0]->res:0, 0), code[1])); break;


		case ASTREE_LISTA_FUNC_MAIS_PARAMETROS: result = tacJoin(code[0], tacJoin(tacCreate(TAC_PARAMETRO_CALL, node->symbol, code[0]?code[0]->res:0, 0), code[1])); break;


		case ASTREE_FUNCAO: result = tacJoin(code[0], tacJoin(code[1], tacCreate(TAC_FUNCPOP, node->son[0]->symbol, 0, 0))); break; 

		case ASTREE_EXPRESSAO_FUNCAO: result = tacJoin(tacCreate(TAC_CALLFUNC, node->symbol, 0, 0), tacJoin(code[0], code[1])); break;
		
		default: result = tacJoin(tacJoin(tacJoin(code[0], code[1]), code[2]), code[3]);
	}

	// retorna o codigo desse nodo
	return result;
}




TAC* makeWhenThen(TAC* code0, TAC* code1){
	TAC* ifTac;
	TAC* lableTac;
	HASH_NODE* newLable;
	newLable = makeLable();
	ifTac = tacCreate(TAC_IFZ, newLable, code0 ? code0->res : 0, 0);
	lableTac = tacCreate(TAC_LABEL, newLable, 0, 0);
	return tacJoin(tacJoin(tacJoin(code0, ifTac), code1), lableTac);
}
TAC* makeWhenThenElse(TAC* code0, TAC* code1, TAC* code2){
	TAC* ifTac;
	TAC* jumpTac;
	TAC* ifLabel;
	TAC* elseLabel;
	HASH_NODE* newifLabel = makeLable();
	HASH_NODE* newElseLabel = makeLable();
	jumpTac = tacCreate(TAC_GOTO, newElseLabel, 0, 0);
	elseLabel = tacCreate(TAC_LABEL, newElseLabel, 0, 0);
	ifTac = tacCreate(TAC_IFZ, newifLabel, code0?code0->res:0, 0);
	ifLabel = tacCreate(TAC_LABEL, newifLabel, 0, 0);
	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(code0, ifTac), code1), jumpTac),ifLabel),code2), elseLabel);
}

TAC* makeFor(HASH_NODE* nodeSymbol, TAC* code0, TAC* code1, TAC* code2){
	TAC* symbol = tacCreate(TAC_SYMBOL, nodeSymbol, 0, 0);
	TAC *move, *cond, *inc;
	move = tacCreate(TAC_MOVE, symbol->res, code0?code0->res:0,0);
	cond = tacCreate(TAC_LE, makeTemp(), symbol?symbol->res:0,code1?code1->res:0);
	inc = tacCreate(TAC_INC, symbol->res, symbol->res, 0);

	HASH_NODE *newForLabel = makeLable(), *newJumpLabel = makeLable();
	TAC *forLabel, *jumpLabel ;
	TAC* jumpTAC = tacCreate(TAC_GOTO, newForLabel, 0, 0);
	TAC* forTAC = tacCreate(TAC_IFZ, newJumpLabel, cond->res, 0);

	forLabel = tacCreate(TAC_LABEL, newForLabel, 0, 0);
	jumpLabel = tacCreate(TAC_LABEL, newJumpLabel, 0, 0);

	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(move, forLabel), cond ), forTAC), code2), inc), jumpTAC), jumpLabel);
}
TAC* makeWhile(TAC* code0, TAC* code1){
	TAC* loop;
	TAC *whileLabel, *jumpLabel;

	HASH_NODE *newWhileLabel = makeLable(), *newJumpLabel = makeLable();
	TAC* jump = tacCreate(TAC_GOTO, newWhileLabel, 0, 0);
	loop = tacCreate(TAC_IFZ, newJumpLabel, code0?code0->res:0, 0);

	whileLabel = tacCreate(TAC_LABEL, newWhileLabel, 0, 0);
	jumpLabel = tacCreate(TAC_LABEL, newJumpLabel, 0, 0);

	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(whileLabel, code0), loop), code1),jump), jumpLabel);
}

TAC* tacReverse(TAC* tac){
	TAC* t = 0;
	for( t = tac; t->prev; t = t->prev){
		t->prev->next = t;
	}
	return t;
}
	

void tacPrintBack(TAC* last){
	fprintf(stderr, "Imprimindo codigo gerado:\n");

	TAC* tac;
	for(tac = last; tac; tac = tac->prev){
		fprintf(stderr, "TAC(\n");
		switch(tac->type){
			case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL"); break;
			case TAC_ADD: fprintf(stderr, "TAC_ADD"); break;
			case TAC_SUB: fprintf(stderr, "TAC_SUB"); break;
			case TAC_MOVE: fprintf(stderr, "TAC_MOVE"); break;
			case TAC_MOVE_VETOR: fprintf(stderr, "TAC_MOVE_VETOR"); break;
			case TAC_EXPRESSAO_VETOR: fprintf(stderr, "TAC_EXPRESSAO_VETOR"); break;
			case TAC_RETURN: fprintf(stderr,"TAC_RETURN"); break;
			case TAC_CALLFUNC: fprintf(stderr,"TAC_CALLFUNC"); break;
			case TAC_PARAMETRO: fprintf(stderr,"TAC_PARAMETRO"); break;
			case TAC_PARAMETRO_CALL: fprintf(stderr,"TAC_PARAMETRO_CALL"); break;
			case TAC_READ: fprintf(stderr,"TAC_READ"); break;
			case TAC_IFZ: fprintf(stderr, "TAC_IFZ"); break;
			case TAC_LABEL: fprintf(stderr, "TAC_LABEL"); break;
			case TAC_MUL: fprintf(stderr, "TAC_MUL"); break;
			case TAC_DIV: fprintf(stderr, "TAC_DIV"); break;
			case TAC_GT: fprintf(stderr, "TAC_GT"); break;
			case TAC_LT: fprintf(stderr, "TAC_LT"); break;
			case TAC_LE: fprintf(stderr, "TAC_LE"); break;
			case TAC_GE: fprintf(stderr, "TAC_GE"); break;
			case TAC_EQ: fprintf(stderr, "TAC_EQ"); break;
			case TAC_NE: fprintf(stderr, "TAC_NE"); break;
			case TAC_AND: fprintf(stderr, "TAC_AND"); break;
			case TAC_FUNCPOP: fprintf(stderr, "TAC_FUNCPOP"); break;
			case TAC_FUNCPUSH: fprintf(stderr, "TAC_FUNCPUSH"); break;
			case TAC_OR: fprintf(stderr, "TAC_OR"); break;
			case TAC_NEGATIVO: fprintf(stderr, "TAC_NEGATIVO"); break;
			case TAC_NEGADO: fprintf(stderr, "TAC_NEGADO"); break;
			case TAC_RET: fprintf(stderr, "TAC_RET"); break;
			case TAC_INC: fprintf(stderr, "TAC_INC"); break;
			case TAC_GOTO: fprintf(stderr, "TAC_JUMP"); break;
			case TAC_PRINT: fprintf(stderr, "TAC_PRINT"); break;
			default: fprintf(stderr, "TAC_UNKNOWN!"); break;
		}
	
		if(tac->res) fprintf(stderr, ", %s", tac->res->value); else fprintf(stderr, ", 0");
		if(tac->op1) fprintf(stderr, ", %s", tac->op1->value); else fprintf(stderr, ", 0");
		if(tac->op2) fprintf(stderr, ", %s", tac->op2->value); else fprintf(stderr, ", 0");
		fprintf(stderr, ")\n");
	   

	}
}

void tacPrintForward(TAC* first){
	fprintf(stderr, "Imprimindo codigo gerado:\n");

	TAC* tac;
	for(tac = first; tac; tac = tac-> next){
		if(tac->type == TAC_SYMBOL){
			continue;
		}
	  
		fprintf(stderr, "TAC(");
		switch(tac->type){
			case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL"); break;
			case TAC_ADD: fprintf(stderr, "TAC_ADD"); break;
			case TAC_SUB: fprintf(stderr, "TAC_SUB"); break;
			case TAC_MOVE: fprintf(stderr, "TAC_MOVE"); break;
			case TAC_MOVE_VETOR: fprintf(stderr, "TAC_MOVE_VETOR"); break;
			case TAC_EXPRESSAO_VETOR: fprintf(stderr, "TAC_EXPRESSAO_VETOR"); break;
			case TAC_RETURN: fprintf(stderr,"TAC_RETURN"); break;
			case TAC_CALLFUNC: fprintf(stderr,"TAC_CALLFUNC"); break;
			case TAC_PARAMETRO: fprintf(stderr,"TAC_PARAMETRO"); break;
			case TAC_PARAMETRO_CALL: fprintf(stderr,"TAC_PARAMETRO_CALL"); break;
			case TAC_READ: fprintf(stderr,"TAC_READ"); break;
			case TAC_IFZ: fprintf(stderr, "TAC_IFZ"); break;
			case TAC_LABEL: fprintf(stderr, "TAC_LABEL"); break;
			case TAC_MUL: fprintf(stderr, "TAC_MUL"); break;
			case TAC_DIV: fprintf(stderr, "TAC_DIV"); break;
			case TAC_GT: fprintf(stderr, "TAC_GT"); break;
			case TAC_LT: fprintf(stderr, "TAC_LT"); break;
			case TAC_LE: fprintf(stderr, "TAC_LE"); break;
			case TAC_GE: fprintf(stderr, "TAC_GE"); break;
			case TAC_EQ: fprintf(stderr, "TAC_EQ"); break;
			case TAC_NE: fprintf(stderr, "TAC_NE"); break;
			case TAC_AND: fprintf(stderr, "TAC_AND"); break;
			case TAC_FUNCPOP: fprintf(stderr, "TAC_FUNCPOP"); break;
			case TAC_OR: fprintf(stderr, "TAC_OR"); break;
			case TAC_NEGATIVO: fprintf(stderr, "TAC_NEGATIVO"); break;
			case TAC_NEGADO: fprintf(stderr, "TAC_NEGADO"); break;
			case TAC_FUNCPUSH: fprintf(stderr, "TAC_FUNCPUSH"); break;
			case TAC_RET: fprintf(stderr, "TAC_RET"); break;
			case TAC_INC: fprintf(stderr, "TAC_INC"); break;
			case TAC_GOTO: fprintf(stderr, "TAC_JUMP"); break;
			case TAC_PRINT: fprintf(stderr, "TAC_PRINT"); break;
			default: fprintf(stderr, "TAC_UNKNOWN!"); break;
		}
	 
		if(tac->res) fprintf(stderr, ", %s", tac->res->value); else fprintf(stderr, ", 0");
		if(tac->op1) fprintf(stderr, ", %s", tac->op1->value); else fprintf(stderr, ", 0");
		if(tac->op2) fprintf(stderr, ", %s", tac->op2->value); else fprintf(stderr, ", 0");
		fprintf(stderr, ")\n");
	   
	}
}

void asmGen(TAC* first){

	FILE* fout;
	fout = fopen("asm.s", "w");
	
	TAC* tac;
	for(tac = first; tac; tac = tac->next){
		if(tac->type == TAC_SYMBOL){
			continue;		
		}
		switch(tac->type){
			case TAC_ADD: fprintf(fout, "## TAC_ADD\n"); asmAdd(tac, fout);
							 break;
			case TAC_SUB: fprintf(fout, "## TAC_SUB\n"); asmSub(tac, fout);
							 break;
			case TAC_MUL: fprintf(fout, "## TAC_MUL\n"); asmMul(tac, fout);
							 break;
			case TAC_DIV: fprintf(fout, "## TAC_DIV\n"); asmDiv(tac, fout);
							 break;
			case TAC_MOVE: fprintf(fout, "## TAC_MOVE\n"
							"\tmovl %s(%%rip), %s(%%rip)\n",
							tac->op1->value, tac->res->value); 
							 break;
			default: break;	
		}	
	}
	
	fclose(fout);

}


void asmAdd(TAC* tac, FILE* fout){
	if(!tac->op1 || !tac ->op2) return;
	
	if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
		fprintf(fout,
		"\tmovl %s(%%rip), %%edx\n"
		"\tmovl %s(%%rip), %%eax\n"
		"\taddl %%edx, %%eax\n"
		"\tmovl %%eax, %s(%%rip)\n",
		tac->op1->value, tac->op2->value,
		tac->res->value);
	}
	if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
		fprintf(fout,
		"\tmovl %s(%%rip), %%eax\n"
		"\taddl $%s, %%eax\n"
		"\tmovl %%eax, %s(%%rip)\n",
		tac->op1->value, tac->op2->value,
		tac->res->value);
	}
	if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
		fprintf(fout,
		"\tmovl %s(%%rip), %%eax\n"
		"\taddl $%s, %%eax\n"
		"\tmovl %%eax, %s(%%rip)\n",
		tac->op2->value, tac->op1->value,
		tac->res->value);
	}
	if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
		int numero1 = atoi(tac->op1->value);
		int numero2 = atoi(tac->op2->value);
		int soma = numero1+numero2;
		fprintf(fout,
		"\tmovl $%d, %s(%%rip)\n",
		soma,
		tac->res->value);
	}
		
}

void asmSub(TAC* tac, FILE* fout){

	if(!tac->op1 || !tac ->op2) return;
	
	if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
		fprintf(fout,
		"\tmovl %s(%%rip), %%edx\n"
		"\tmovl %s(%%rip), %%eax\n"
		"\tsubl %%edx, %%eax\n"
		"\tmovl %%eax, %s(%%rip)\n",
		tac->op1->value, tac->op2->value,
		tac->res->value);
	}
	if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
		fprintf(fout,
		"\tmovl %s(%%rip), %%eax\n"
		"\tsubl $%s, %%eax\n"
		"\tmovl %%eax, %s(%%rip)\n",
		tac->op1->value, tac->op2->value,
		tac->res->value);
	}
	if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
		fprintf(fout,
		"\tmovl %s(%%rip), %%eax\n"
		"\tmovl $%s, %%edx\n"
		"\tsubl %%edx, %%eax\n"
		"\tmovl %%eax, %s(%%rip)\n",
		tac->op2->value, tac->op1->value,
		tac->res->value);
	}
	if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
		int numero1 = atoi(tac->op1->value);
		int numero2 = atoi(tac->op2->value);
		int soma = numero1-numero2;
		fprintf(fout,
		"\tmovl $%d, %s(%%rip)\n",
		soma,
		tac->res->value);
	}
}

void asmMul(TAC* tac, FILE* fout){
	
	if(!tac->op1 || !tac ->op2) return;
	
	if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
		fprintf(fout,
		"\tmovl %s(%%rip), %%edx\n"
		"\tmovl %s(%%rip), %%eax\n"
		"\timull %%edx, %%eax\n"
		"\tmovl %%eax, %s(%%rip)\n",
		tac->op1->value, tac->op2->value,
		tac->res->value);
	}
	if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
		fprintf(fout,
		"\tmovl %s(%%rip), %%eax\n"
		"\timull $%s, %%eax, %%eax\n"
		"\tmovl %%eax, %s(%%rip)\n",
		tac->op1->value, tac->op2->value,
		tac->res->value);
	}
	if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
		fprintf(fout,
		"\tmovl %s(%%rip), %%eax\n"	
		"\timull $%s, %%eax, %%eax\n"
		"\tmovl %%eax, %s(%%rip)\n",
		tac->op2->value, tac->op1->value,
		tac->res->value);
	}
	if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
		int numero1 = atoi(tac->op1->value);
		int numero2 = atoi(tac->op2->value);
		int soma = numero1*numero2;
		fprintf(fout,
		"\tmovl $%d, %s(%%rip)\n",
		soma,
		tac->res->value);
	}

}

void asmDiv(TAC* tac, FILE* fout){

	if(!tac->op1 || !tac ->op2) return;
	
	if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
		fprintf(fout,
		"\tmovl %s(%%rip), %%eax\n"
		"\tmovl %s(%%rip), %%ecx\n"
		"\tcltd\n"
		"\tidivl %%ecx\n"
		"\tmovl %%eax, %s(%%rip)\n",
		tac->op1->value, tac->op2->value,
		tac->res->value);
	}
	if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){ // rever
		fprintf(fout,
		"\tmovl %s(%%rip), %%ecx\n"
		"\tmovl $-1600085855, %%edx\n"
		"\tmovl %%ecx, %%eax\n"
		"\timull %%edx\n"
		"\tleal (%%rdx,%%rcx), %%eax\n"
		"\tsarl $%s, %%eax\n"
		"\tmovl %%eax, %%edx\n"
		"\tsarl $31, %%eax\n"
		"\tsubl %%eax, %%edx\n"
		"movl %%edx, %%eax\n"
		"\tmovl %%eax, %s(%%rip)\n",
		tac->op1->value, tac->op2->value,
		tac->res->value);
	}
	if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
		fprintf(fout,
		"\tmovl %s(%%rip), %%ecx\n"
		"\tmovl $%s, %%eax\n"
		"\tcltd\n"
		"\tidivl %%ecx\n"
		"\tmovl %%eax, %s(%%rip)\n",
		tac->op2->value, tac->op1->value,
		tac->res->value);
	}
	if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
		int numero1 = atoi(tac->op1->value);
		int numero2 = atoi(tac->op2->value);
		int soma = numero1/numero2;
		fprintf(fout,
		"\tmovl $%d, %s(%%rip)\n",
		soma,
		tac->res->value);
	}

}

