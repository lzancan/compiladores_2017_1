#include <stdio.h>
#include <stdlib.h>

#include "tacs.h"



TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2){
	TAC* newTac;
	newTac = (TAC*) calloc(1,sizeof(TAC*));
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
	// para debug:
	if(!l1 && !l2) fprintf(stderr,"tacJoin: nenhum dos tacs existem!\n");

	if(!l1) return l2;
	if(!l2) return l1;
	for(tac=l1; tac->prev; tac=tac->prev){
		;	
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
		case ASTREE_ADD: result = tacJoin(code[0], tacJoin(code[1], 
					tacCreate(TAC_ADD, makeTemp(), code[0] ? code[0]->res : 0, code[1]? code[1]->res : 0))); break;
		case ASTREE_WHEN_THEN: result = makeWhenThen(code[0], code[1]); break;
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
	lableTac = tacCreate(TAC_LABLE, newLable, 0, 0);
	return tacJoin(tacJoin(tacJoin(code0, ifTac), code1), lableTac);

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
			case TAC_ADD: fprintf(stderr, "TAC_SYMBOL"); break;
			case TAC_SUB: fprintf(stderr, "TAC_SYMBOL"); break;
			case TAC_IFZ: fprintf(stderr, "TAC_SYMBOL"); break;
			case TAC_LABLE: fprintf(stderr, "TAC_SYMBOL"); break;
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
			case TAC_ADD: fprintf(stderr, "TAC_SYMBOL"); break;
			case TAC_SUB: fprintf(stderr, "TAC_SYMBOL"); break;
			case TAC_IFZ: fprintf(stderr, "TAC_SYMBOL"); break;
			case TAC_LABLE: fprintf(stderr, "TAC_SYMBOL"); break;
			default: fprintf(stderr, "TAC_UNKNOWN!"); break; 
		}
		if(tac->res) fprintf(stderr, ", %s", tac->res->value); else fprintf(stderr, ", 0");
		if(tac->op1) fprintf(stderr, ", %s", tac->op1->value); else fprintf(stderr, ", 0");
		if(tac->op2) fprintf(stderr, ", %s", tac->op2->value); else fprintf(stderr, ", 0");
		fprintf(stderr, ")\n");	
	}
}



