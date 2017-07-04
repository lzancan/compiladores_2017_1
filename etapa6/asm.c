#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asm.h"


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
