#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asm.h"


void asmGen(TAC* first){

	FILE* fout;
	fout = fopen("asm.s", "w");
	
	// print variaveis globais da hash
	
	fprintf(fout, "## VARIAVEIS_GLOBAIS\n");
	printHashAsm(fout); 
	
	//

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
			case TAC_MOVE: fprintf(fout, "## TAC_MOVE\n");
							if(tac->op1->nature == NATURE_FUNCTION){
								fprintf(fout, "\tmovl %%eax, %s(%%rip)\n", tac->res->value);
							}
							else{
								fprintf(fout, "\tmovl %s(%%rip), %s(%%rip)\n",
								tac->op1->value, tac->res->value); 
							}
							 break;
			case TAC_MOVE_VETOR: fprintf(fout, "## TAC_MOVE_VETOR\n");
							if(tac->op2->type == SYMBOL_IDENTIFIER && tac->op2->nature != NATURE_FUNCTION){
								fprintf(fout,
								"\tmovl	%s(%%rip), %%eax\n"
								"\tmovl	%%eax, %s+%d(%%rip)\n"
								, tac->op2->value, tac->res->value, atoi(tac->op1->value)*4); 
							}
							else if(tac->op2->nature == NATURE_FUNCTION){
								fprintf(fout, "\tmovl	%%eax, %s+%d(%%rip)\n"
									,tac->res->value, atoi(tac->op1->value)*4);
							}
							else {
								fprintf(fout, "\tmovl	$%s, %s+%d(%%rip)\n"
									, tac->op2->value, tac->res->value, atoi(tac->op1->value)*4);
							}
							break;
			case TAC_EXPRESSAO_VETOR: fprintf(fout, "## TAC_EXPRESSAO_VETOR\n"
								"\tmovl	%s+%d(%%rip), %%eax\n"
								"\tmovl	%%eax, %s(%%rip)\n"
								, tac->op1->value, atoi(tac->op2->value)*4 , tac->res->value); 
							break;
			case TAC_FUNCPUSH: fprintf(fout, "## TAC_FUNCPUSH\n"); funcPush(tac, fout); break;
			case TAC_FUNCPOP: fprintf(fout, "## TAC_FUNCPOP\n"); funcPop(tac, fout); break;
			case TAC_CALLFUNC: fprintf(fout, "## TAC_CALLFUNC\n");
								if(tac->next->type == TAC_CALLFUNC){
									fprintf(fout, "\tmovl	$0, %%eax\n"
										      "\tcall	%s\n"
										      "\tmovl	%%eax, %%ebx\n"
											, tac->res->value);
								}
								else{
								fprintf(fout, 		
								"\tmovl	$0, %%eax\n"
								"\tcall	%s\n", tac->res->value); 
								}	break;
					 			
						
			case TAC_PRINT: fprintf(fout, "## TAC_PRINT\n"); asmPrint(tac, fout); break;			
			default: break;	
		}	
	}
	
	fclose(fout);

}

void printHashAsm(FILE* fout){
	int i;
	HASH_NODE * node = NULL;

	//fprintf(stderr,"Hash printing:\nInicio de impressao\n");
	for(i=0 ; i < HASH_SIZE ; i++){
		for(node = hashTable[i] ; node ; node = node->next){
			if(node->nature == NATURE_ESCALAR){
				fprintf(fout,"\t.globl %s\n"
					     "\t.align 4\n"
					     "\t.type	%s, @object\n"
					     "\t.size	%s, 4\n"
					     "%s:\n"
					     "\t.long	45\n", node->value, node->value, node->value, node->value); 			
			}
			//printHashNode(node);
		}
	}
	fprintf(stderr,"Termino de impressao\n");
}


void asmPrint(TAC* tac,FILE* fout){
	if(tac->op1){
		if(tac->op1->type == SYMBOL_IDENTIFIER){
			fprintf(fout,"\tmovl	%s(%%rip), %%eax\n"
				     "\tmovl	%%eax, %%esi\n"
				     "\tmovl	$.%s, %%edi\n"
				     "\tmovl	$0, %%eax\n"
				     "\tcall	printf\n"
				     , tac->op1->value, tac->op2->value);		
		}
		else{
			fprintf(fout,"\tmovl	$.%s, %%edi\n"
				     "\tmovl	$0, %%eax\n"
				     "\tcall	printf\n"
				     , tac->op2->value);		
		}
	}
	
}

void funcPush(TAC* tac, FILE* fout){
	//declara labels do print
	
	TAC* tacLabel;
	for(tacLabel=tac; tacLabel->type != TAC_FUNCPOP; tacLabel=tacLabel->next){
		if(tacLabel->type == TAC_PRINT){
			if(tacLabel->op1->type == SYMBOL_IDENTIFIER){
				tacLabel->op2 = makeLable();
				fprintf(fout,".%s:\n"
				     	     "\t.string \"%%d\"\n"
					    , tacLabel->op2->value);		
							
			}
			else{
				tacLabel->op2 = makeLable();
				fprintf(fout,".%s:\n"
				     	     "\t.string \"%s\"\n"
					    , tacLabel->op2->value,tacLabel->op1->value);	
			}
		}
	}
		
	//


	fprintf(fout,"\t.globl	%s\n"
		     "\t.type	%s, @function\n", tac->res->value, tac->res->value);
	fprintf(fout, "%s:\n"							
			".%s:\n", tac->res->value, makeLable()->value);
	fprintf(fout, "\t.cfi_startproc\n"
		      "\tpushq	%%rbp\n"
		      "\t.cfi_def_cfa_offset 16\n"
		      "\t.cfi_offset 6, -16\n"
		      "\tmovq	%%rsp, %%rbp\n"
		      "\t.cfi_def_cfa_register 6\n");
}

void funcPop(TAC* tac, FILE* fout){
	fprintf(fout, "\tpopq	%%rbp\n"
		      "\t.cfi_def_cfa 7, 8\n"
		      "\tret\n"
		      "\t.cfi_endproc\n");
	fprintf(fout, ".%s:\n", makeLable()->value);
	fprintf(fout, "\t.size	%s, .-%s\n", tac->res->value, tac->res->value);
				      


}


void asmAdd(TAC* tac, FILE* fout){
	if(!tac->op1 || !tac ->op2) return;
		if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION && tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\taddl	%%ebx, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->res->value);
			}
			else if(tac->op1->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tmovl %%eax, %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\taddl %%edx, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value,
				tac->res->value);			
			}
			else if (tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tmovl %%eax, %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\taddl %%edx, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,
				tac->res->value);			
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\taddl %%edx, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value, tac->op2->value,
				tac->res->value);
			}
		}
		if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\taddl $%s, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value,
				tac->res->value);
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\taddl $%s, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value, tac->op2->value,
				tac->res->value);
			}
		}
		if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
			if(tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\taddl $%s, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,
				tac->res->value);
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\taddl $%s, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value, tac->op1->value,
				tac->res->value);
			}
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
		if(tac->op1->nature == NATURE_FUNCTION && tac->op2->nature == NATURE_FUNCTION){
			fprintf(fout,
			"\tsubl	%%eax, %%ebx\n"
			"\tmovl %%ebx, %%eax\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->res->value);
		}
		else if(tac->op1->nature == NATURE_FUNCTION){
			fprintf(fout,
			"\tmovl %%eax, %%edx\n"
			"\tmovl %s(%%rip), %%eax\n"
			"\tsubl %%eax, %%edx\n"
			"\tmovl %%edx, %%eax\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op2->value,
			tac->res->value);			
		}
		else if (tac->op2->nature == NATURE_FUNCTION){
			fprintf(fout,
			"\tmovl %s(%%rip), %%ebx\n"
			"\tsubl %%eax, %%ebx\n"
			"\tmovl %%ebx, %%eax\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op1->value,
			tac->res->value);			
		}
		else{
			fprintf(fout,
			"\tmovl %s(%%rip), %%edx\n"
			"\tmovl %s(%%rip), %%eax\n"
			"\tsubl %%edx, %%eax\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op1->value, tac->op2->value,
			tac->res->value);
		}
	}
	if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
		if(tac->op1->nature == NATURE_FUNCTION){
			fprintf(fout,
			"\tsubl $%s, %%eax\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op2->value,
			tac->res->value);
		}
		else{
			fprintf(fout,
			"\tmovl %s(%%rip), %%eax\n"
			"\tsubl $%s, %%eax\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op1->value, tac->op2->value,
			tac->res->value);
		}
	}
	if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
		if(tac->op2->nature == NATURE_FUNCTION){
			fprintf(fout,
			"\tmovl	$%s, %%edx\n"
			"\tsubl	%%eax, %%edx\n"
			"\tmovl	%%edx, %%eax\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op1->value,
			tac->res->value);
		}
		else{
			fprintf(fout,
			"\tmovl %s(%%rip), %%eax\n"
			"\tmovl $%s, %%edx\n"
			"\tsubl %%edx, %%eax\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op2->value, tac->op1->value,
			tac->res->value);
		}
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
		if(tac->op1->nature == NATURE_FUNCTION && tac->op2->nature == NATURE_FUNCTION){
			fprintf(fout,
			"\timull	%%ebx, %%eax\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->res->value);
		}
		else if(tac->op1->nature == NATURE_FUNCTION){
			fprintf(fout,
			"\tmovl %%eax, %%edx\n"
			"\tmovl %s(%%rip), %%eax\n"
			"\timull %%edx, %%eax\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op2->value,
			tac->res->value);			
		}
		else if (tac->op2->nature == NATURE_FUNCTION){
			fprintf(fout,
			"\tmovl %%eax, %%edx\n"
			"\tmovl %s(%%rip), %%eax\n"
			"\timull %%edx, %%eax\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op1->value,
			tac->res->value);			
		}
		else{
			fprintf(fout,
			"\tmovl %s(%%rip), %%edx\n"
			"\tmovl %s(%%rip), %%eax\n"
			"\timull %%edx, %%eax\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op1->value, tac->op2->value,
			tac->res->value);
		}
	}
	if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
		if(tac->op1->nature == NATURE_FUNCTION){
			fprintf(fout,
			"\timull $%s, %%eax, %%eax\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op2->value,
			tac->res->value);
		}
		else{
			fprintf(fout,
			"\tmovl %s(%%rip), %%eax\n"
			"\timull $%s, %%eax, %%eax\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op1->value, tac->op2->value,
			tac->res->value);
}
	}
	if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
		if(tac->op2->nature == NATURE_FUNCTION){
			fprintf(fout,
			"\timull $%s, %%eax, %%eax\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op1->value,
			tac->res->value);
		}
		else{
			fprintf(fout,
			"\tmovl %s(%%rip), %%eax\n"	
			"\timull $%s, %%eax, %%eax\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op2->value, tac->op1->value,
			tac->res->value);
		}
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
		if(tac->op1->nature == NATURE_FUNCTION && tac->op2->nature == NATURE_FUNCTION){
			fprintf(fout,
			"\tmovl %%eax, %%ecx\n"
			"\tmovl %%ebx, %%eax\n"
			"\tcltd\n"
			"\tidivl %%ecx\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->res->value);
		}
		else if(tac->op1->nature == NATURE_FUNCTION){
			fprintf(fout,
			"\tmovl %s(%%rip), %%ecx\n"
			"\tcltd\n"
			"\tidivl %%ecx\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op2->value,
			tac->res->value);			
		}
		else if (tac->op2->nature == NATURE_FUNCTION){
			fprintf(fout,
			"\tmovl %s(%%rip), %%ebx\n"
			"\tmovl %%eax, %%ecx\n"
			"\tmovl %%ebx, %%eax\n"
			"\tcltd\n"
			"\tidivl %%ecx\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op1->value,
			tac->res->value);			
		}
		else{
			fprintf(fout,
			"\tmovl %s(%%rip), %%eax\n"
			"\tmovl %s(%%rip), %%ecx\n"
			"\tcltd\n"
			"\tidivl %%ecx\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op1->value, tac->op2->value,
			tac->res->value);
		}
	}
	if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){ // rever
		if(tac->op1->nature == NATURE_FUNCTION){
			fprintf(fout,
			"\tmovl $%s, %%ebx\n"
			"\tmovl %%eax, %%ecx\n"
			"\tmovl %%ebx, %%eax\n"
			"\tcltd\n"
			"\tidivl %%ecx\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op2->value,
			tac->res->value);				
		}
		else{
			fprintf(fout,
			"\tmovl %s(%%rip), %%eax\n"
			"\tmovl $%s, %%ecx\n"
			"\tcltd\n"
			"\tidivl %%ecx\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op1->value,
			tac->op2->value,
			tac->res->value);
		}
	}
	if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
		if(tac->op2->nature == NATURE_FUNCTION){
			fprintf(fout,
			"\tmovl $%s, %%ebx\n"
			"\tmovl %%eax, %%ecx\n"
			"\tmovl %%ebx, %%eax\n"
			"\tcltd\n"
			"\tidivl %%ecx\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op1->value,
			tac->res->value);	
		}
		else{
			fprintf(fout,
			"\tmovl %s(%%rip), %%ecx\n"
			"\tmovl $%s, %%eax\n"
			"\tcltd\n"
			"\tidivl %%ecx\n"
			"\tmovl %%eax, %s(%%rip)\n",
			tac->op2->value,
			tac->op1->value,
			tac->res->value);	
}
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