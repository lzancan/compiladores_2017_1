#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asm.h"

int flagVarTemp = 0;

void asmGen(TAC* first){

	FILE* fout;
	fout = fopen("asm.s", "w");
	
	
	TAC* tac;
	for(tac = first; tac; tac = tac->next){
		if(tac->type == TAC_SYMBOL){
			continue;		
		}
		switch(tac->type){
			case TAC_PARAMETRO_CALL: fprintf(fout, "## TAC_PARAMETRO_CALL\n"); parametrosFunc(tac, fout); 
							break;
			case TAC_VAR_GLOBAL: fprintf(fout, "## VARIAVEIS_GLOBAIS\n");
						printVarGlobal(tac, fout); break;
			case TAC_ADD: fprintf(fout, "## TAC_ADD\n"); asmAdd(tac, fout);
							 break;
			case TAC_SUB: fprintf(fout, "## TAC_SUB\n"); asmSub(tac, fout);
							 break;
			case TAC_MUL: fprintf(fout, "## TAC_MUL\n"); asmMul(tac, fout);
							 break;
			case TAC_DIV: fprintf(fout, "## TAC_DIV\n"); asmDiv(tac, fout);
							 break;
			case TAC_RETURN: fprintf(fout, "## TAC_RETURN\n"); if(tac->op1->type == SYMBOL_LIT_INTEGER || 
										tac->op1->type == SYMBOL_LIT_REAL){
											fprintf(fout, "\tmovl $%s, %%eax\n",
											tac->op1->value);
										}
							 break;
			case TAC_GT: fprintf(fout, "## TAC_GT\n"); asmGt(tac, fout); break;
			case TAC_LT: fprintf(fout, "## TAC_LT\n"); asmLt(tac, fout);break;
			case TAC_LE: fprintf(fout, "## TAC_LE\n"); asmLe(tac, fout);break;
			case TAC_GE: fprintf(fout, "## TAC_GE\n"); asmGe(tac, fout);break;
			case TAC_EQ: fprintf(fout, "## TAC_EQ\n"); asmEq(tac, fout);break;
			case TAC_NE: fprintf(fout, "## TAC_NE\n"); asmNe(tac, fout);break;
			case TAC_AND: fprintf(fout, "## TAC_AND\n"); asmAnd(tac, fout);break;
			case TAC_OR: fprintf(fout, "## TAC_OR\n"); asmOr(tac, fout);break;
			case TAC_READ: fprintf(fout, "## TAC_READ\n"
						"\tmovl $%s, %%esi\n"
						"\tmovl $.%s, %%edi\n"
						"\tmovl $0, %%eax\n"
						"\tcall __isoc99_scanf\n"
						,tac->res->value, tac->op2->value);break;
			case TAC_IFZ: fprintf(fout, "## TAC_IFZ\n");fprintf(fout,
									"\tmovl %s(%%rip), %%eax\n"
									"\ttestl %%eax, %%eax\n"
									"\tje  .%s\n",
									tac->op1->value,
									tac->res->value); break;
			case TAC_LABEL: fprintf(fout, "## TAC_LABEL\n");fprintf(fout, ".%s:\n",	tac->res->value); break;
			case TAC_GOTO: fprintf(fout, "## TAC_GOTO\n");fprintf(fout, "\tjmp  .%s\n",	tac->res->value); break;
			case TAC_INC: fprintf(fout, "## TAC_INC\n");fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\taddl $1, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,
				tac->res->value); break;
			case TAC_MOVE: fprintf(fout, "## TAC_MOVE\n");
							if(tac->op1->nature == NATURE_FUNCTION){
								fprintf(fout, "\tmovl %%eax, %s(%%rip)\n", tac->res->value);
							}
							else if(tac->op1->type == SYMBOL_IDENTIFIER){
								fprintf(fout, "\tmovl %s(%%rip), %%eax\n"
												"\tmovl %%eax, %s(%%rip)\n",
								tac->op1->value, tac->res->value); 
							}
							else{
								fprintf(fout, "\tmovl $%s, %s(%%rip)\n",
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
			case TAC_FUNCPUSH: funcPush(tac, fout); break;
			case TAC_FUNCPOP: fprintf(fout, "## TAC_FUNCPOP\n"); funcPop(tac, fout); break;
			case TAC_CALLFUNC: 	parametrosFunc(tac, fout); 
						fprintf(fout, "## TAC_CALLFUNC\n");
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


void parametrosFunc(TAC* tac, FILE* fout){
		TAC* tacPercorre1 = tac;
		TAC* tacPercorre2 = tac;
		int flag=0;

		while(tacPercorre1->type != TAC_CALLFUNC){
			tacPercorre1 = tacPercorre1 -> next;
		}
		do{
			tacPercorre2 = tacPercorre2 -> prev;
			flag=0;
			if(tacPercorre2->type == TAC_FUNCPUSH){
				if(tacPercorre2->res){
					if(strcmp(tacPercorre1->res->value,tacPercorre2->res->value)==0){
						flag = 1;
						fprintf(stderr,"%s e %s\n", tacPercorre1->res->value, tacPercorre2->res->value);
					}
					else flag=0;
				}
			}	
		}while(flag!=1);
	
		//tacPercorre2 = tacPercorre2->next;
		/*
		TAC* tacPercorre3 = tac; 
		
		fprintf(fout, "## TAC_MOVE\n");
							if(tac->op1->nature == NATURE_FUNCTION){
								fprintf(fout, "\tmovl %%eax, %s(%%rip)\n", tac->res->value);
							}
							else{
								fprintf(fout, "\tmovl %s(%%rip), %s(%%rip)\n",
								tac->op1->value, tac->res->value); 
							}
							
		do{
			if(tacPercorre3->op2 == NULL){
				if(tacPercorre2->res){
					if(tacPercorre2->res->nature == NATURE_ESCALAR){
						if(tacPercorre3->op1 == NULL){
							tacPercorre3 = tacPercorre3->next;
						}
						if(tacPercorre3->op2 == NULL){
							//fprintf(stderr, "(TAC_MOVE, %s, %s, %s)\n", tacPercorre2->res? tacPercorre2->res->value:0, tacPercorre3->op1?tacPercorre3->op1->value:0, tacPercorre3->op2?tacPercorre3->op2->value:0 );
							fprintf(fout, "## TAC_MOVE\n");
							if(tacPercorre3->op1->nature == NATURE_FUNCTION){
								fprintf(fout, "\tmovl %%eax, %s(%%rip)\n", tacPercorre2->res->value);
							}
							else if (tacPercorre3->op1->type==SYMBOL_IDENTIFIER){
								fprintf(fout, "\tmovl %s(%%rip), %%eax\n",
											  "\tmovl %%eax, %s(%%rip)\n",
											tacPercorre3->op1->value, tacPercorre2->res->value); 
							}
							else{
								fprintf(fout, "\tmovl $%s, %s(%%rip)\n",
								tacPercorre3->op1->value, tacPercorre2->res->value); 
							}
							tacPercorre3->op2 = makeTemp();
						}
						
					}
				}
				//tacPercorre3 = tacPercorre3->next;
			}
			tacPercorre2 = tacPercorre2->next;
			tacPercorre3 = tacPercorre3->next;
		}
		while(tacPercorre3->type != TAC_CALLFUNC);*/
		
		
}

void printVarGlobal(TAC* tac, FILE* fout){
	//if(tac->res->dataType == DATATYPE_BYTE || tac->res->dataType == DATATYPE_SHORT || tac->res->dataType == DATATYPE_SHORT){
		fprintf(fout,"\t.globl %s\n"
			     "\t.data\n"
		     	     "\t.align 4\n"
		             "\t.type	%s, @object\n"
		             "\t.size	%s, 4\n"
		             "%s:\n"
		             "\t.long	%d\n", tac->res->value, tac->res->value, tac->res->value, tac->res->value, atoi(tac->op1->value));
}


void asmPrint(TAC* tac,FILE* fout){
	if(tac->op1){
		if(tac->op1->type == SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION){
				fprintf(fout,
				     "\tmovl	%%eax, %%esi\n"
				     "\tmovl	$.%s, %%edi\n"
				     "\tmovl	$0, %%eax\n"
				     "\tcall	printf\n",
				     tac->op2->value);
			}
			else{
				fprintf(fout,"\tmovl	%s(%%rip), %%eax\n"
				     "\tmovl	%%eax, %%esi\n"
				     "\tmovl	$.%s, %%edi\n"
				     "\tmovl	$0, %%eax\n"
				     "\tcall	printf\n"
				     , tac->op1->value, tac->op2->value);			
			}		
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

	if (flagVarTemp == 0){
		int i;
		HASH_NODE * node = NULL;
		// declara todas as variaveis temporarias...
		for(i=0 ; i < HASH_SIZE ; i++){
			for(node = hashTable[i] ; node ; node = node->next){
				if(node -> nature == 0 && node -> type == SYMBOL_IDENTIFIER && node->value[0]=='t'){
					fprintf(fout, "\t.comm	%s,4,4\n", node->value);				
				}
			}
		}		

		flagVarTemp=1;
	}	

	//declara labels do print (printf) e read (scanf)	
	TAC* tacLabel;
	for(tacLabel=tac; tacLabel->type != TAC_FUNCPOP; tacLabel=tacLabel->next){
		if(tacLabel->type == TAC_PRINT ){
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
		if(tacLabel->type == TAC_READ ){
			tacLabel->op2 = makeLable();
			fprintf(fout,".%s:\n"
				     	    "\t.string \"%%d\"\n"
					   , tacLabel->op2->value);	
		}
	
	}
		
	//

	fprintf(fout, "\t.text\n");
	fprintf(fout, "## TAC_FUNCPUSH\n");

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
	if(!tac->op1 || !tac->op2) return;
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
			"\tmovl $%d, %%eax\n",
			soma
			);
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
void asmGt(TAC* tac, FILE* fout){
	if(!tac->op1 || !tac ->op2) return;
		if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION && tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tcmpl	%%eax, %%ebx\n"
				"\tsetg %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->res->value);
			}
			else if(tac->op1->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tmovl %%eax, %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl	%%eax, %%edx\n"
				"\tsetg %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value,
				tac->res->value);			
			}
			else if (tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tmovl %%eax, %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl %%eax, %%edx\n"
				"\tsetg	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,
				tac->res->value);		
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl %%eax, %%edx\n"
				"\tsetg	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value, tac->op2->value,
				tac->res->value);
			}
		}
		if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tcmpl $%s, %%eax\n"
				"\tsetg	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value,
				tac->res->value);
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl $%s, %%eax\n"
				"\tsetg	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value, tac->op2->value,
				tac->res->value);
			}
		}
		if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
			if(tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tcmpl %%eax,$%s \n"
				"\tsetg	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,
				tac->res->value);
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl %%eax,$%s\n"
				"\tsetg	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value, tac->op1->value,
				tac->res->value);
			}
		}
		if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
			int numero1 = atoi(tac->op1->value);
			int numero2 = atoi(tac->op2->value);
			int res = numero1>numero2;
			fprintf(fout,
			"\tmovl $%d, %s(%%rip)\n",
			res,
			tac->res->value);
		}
		
}
void asmLt(TAC* tac, FILE* fout){
	if(!tac->op1 || !tac ->op2) return;
		if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION && tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tcmpl	%%eax, %%ebx\n"
				"\tsetl %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->res->value);
			}
			else if(tac->op1->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tmovl %%eax, %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl	%%eax, %%edx\n"
				"\tsetl %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value,
				tac->res->value);			
			}
			else if (tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tmovl %%eax, %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl %%eax, %%edx\n"
				"\tsetl	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,
				tac->res->value);		
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl %%eax, %%edx\n"
				"\tsetl	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value, tac->op2->value,
				tac->res->value);
			}
		}
		if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tcmpl $%s, %%eax\n"
				"\tsetl	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value,
				tac->res->value);
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl $%s, %%eax\n"
				"\tsetl	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value, tac->op2->value,
				tac->res->value);
			}
		}
		if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
			if(tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tcmpl %%eax,$%s \n"
				"\tsetl	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,
				tac->res->value);
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl %%eax,$%s\n"
				"\tsetl	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value, tac->op1->value,
				tac->res->value);
			}
		}
		if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
			int numero1 = atoi(tac->op1->value);
			int numero2 = atoi(tac->op2->value);
			int res = numero1<numero2;
			fprintf(fout,
			"\tmovl $%d, %s(%%rip)\n",
			res,
			tac->res->value);
		}
		
}
void asmLe(TAC* tac, FILE* fout){
	if(!tac->op1 || !tac ->op2) return;
		if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION && tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tcmpl	%%eax, %%ebx\n"
				"\tsetle %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->res->value);
			}
			else if(tac->op1->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tmovl %%eax, %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl	%%eax, %%edx\n"
				"\tsetle %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value,
				tac->res->value);			
			}
			else if (tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tmovl %%eax, %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl %%eax, %%edx\n"
				"\tsetle	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,
				tac->res->value);		
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl %%eax, %%edx\n"
				"\tsetle	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value, tac->op2->value,
				tac->res->value);
			}
		}
		if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tcmpl $%s, %%eax\n"
				"\tsetle	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value,
				tac->res->value);
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl $%s, %%eax\n"
				"\tsetle	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value, tac->op2->value,
				tac->res->value);
			}
		}
		if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
			if(tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tcmpl %%eax,$%s \n"
				"\tsetle	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,
				tac->res->value);
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl %%eax,$%s\n"
				"\tsetle	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value, tac->op1->value,
				tac->res->value);
			}
		}
		if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
			int numero1 = atoi(tac->op1->value);
			int numero2 = atoi(tac->op2->value);
			int res = numero1<=numero2;
			fprintf(fout,
			"\tmovl $%d, %s(%%rip)\n",
			res,
			tac->res->value);
		}
		
}
void asmGe(TAC* tac, FILE* fout){
	if(!tac->op1 || !tac ->op2) return;
		if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION && tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tcmpl	%%eax, %%ebx\n"
				"\tsetge %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->res->value);
			}
			else if(tac->op1->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tmovl %%eax, %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl	%%eax, %%edx\n"
				"\tsetge %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value,
				tac->res->value);			
			}
			else if (tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tmovl %%eax, %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl %%eax, %%edx\n"
				"\tsetge %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,
				tac->res->value);		
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl %%eax, %%edx\n"
				"\tsetge %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value, tac->op2->value,
				tac->res->value);
			}
		}
		if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tcmpl $%s, %%eax\n"
				"\tsetge %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value,
				tac->res->value);
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl $%s, %%eax\n"
				"\tsetge %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value, tac->op2->value,
				tac->res->value);
			}
		}
		if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
			if(tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tcmpl %%eax,$%s \n"
				"\tsetge %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,
				tac->res->value);
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl %%eax,$%s\n"
				"\tsetge %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value, tac->op1->value,
				tac->res->value);
			}
		}
		if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
			int numero1 = atoi(tac->op1->value);
			int numero2 = atoi(tac->op2->value);
			int res = numero1>=numero2;
			fprintf(fout,
			"\tmovl $%d, %s(%%rip)\n",
			res,
			tac->res->value);
		}
		
}
void asmEq(TAC* tac, FILE* fout){
	if(!tac->op1 || !tac ->op2) return;
		if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION && tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tcmpl	%%eax, %%ebx\n"
				"\tsete %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->res->value);
			}
			else if(tac->op1->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tmovl %%eax, %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl	%%eax, %%edx\n"
				"\tsete %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value,
				tac->res->value);			
			}
			else if (tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tmovl %%eax, %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl %%eax, %%edx\n"
				"\tsete	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,
				tac->res->value);		
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl %%eax, %%edx\n"
				"\tsete	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value, tac->op2->value,
				tac->res->value);
			}
		}
		if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tcmpl $%s, %%eax\n"
				"\tsete	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value,
				tac->res->value);
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl $%s, %%eax\n"
				"\tsete	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value, tac->op2->value,
				tac->res->value);
			}
		}
		if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
			if(tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tcmpl %%eax,$%s \n"
				"\tsete	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,
				tac->res->value);
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl %%eax,$%s\n"
				"\tsete	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value, tac->op1->value,
				tac->res->value);
			}
		}
		if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
			int numero1 = atoi(tac->op1->value);
			int numero2 = atoi(tac->op2->value);
			int res = numero1==numero2;
			fprintf(fout,
			"\tmovl $%d, %s(%%rip)\n",
			res,
			tac->res->value);
		}
		
}
void asmNe(TAC* tac, FILE* fout){
	if(!tac->op1 || !tac ->op2) return;
		if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION && tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tcmpl	%%eax, %%ebx\n"
				"\tsetne %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->res->value);
			}
			else if(tac->op1->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tmovl %%eax, %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl	%%eax, %%edx\n"
				"\tsetne %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value,
				tac->res->value);			
			}
			else if (tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tmovl %%eax, %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl %%eax, %%edx\n"
				"\tsetne	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,
				tac->res->value);		
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl %%eax, %%edx\n"
				"\tsetne	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value, tac->op2->value,
				tac->res->value);
			}
		}
		if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tcmpl $%s, %%eax\n"
				"\tsetne	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value,
				tac->res->value);
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl $%s, %%eax\n"
				"\tsetne	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value, tac->op2->value,
				tac->res->value);
			}
		}
		if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
			if(tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tcmpl %%eax,$%s \n"
				"\tsetne	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,
				tac->res->value);
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl %%eax,$%s\n"
				"\tsetne	%%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value, tac->op1->value,
				tac->res->value);
			}
		}
		if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
			int numero1 = atoi(tac->op1->value);
			int numero2 = atoi(tac->op2->value);
			int res = numero1!=numero2;
			fprintf(fout,
			"\tmovl $%d, %s(%%rip)\n",
			res,
			tac->res->value);
		}
		
}
void asmAnd(TAC* tac, FILE* fout){
	HASH_NODE *l1, *l2;
	l1 = makeLable();
	l2 = makeLable(); 
	if(!tac->op1 || !tac ->op2) return;
		if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION && tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\ttstl	$0, %%eax\n"
				"\tje .%s\n"
				"\ttstl	$0, %%ebx\n"
				"\tje .%s\n"
				"\tmovl $1, %%eax\n"
				"\tjmp .%s\n"
				".%s:\n"
				"\tmovl $0, %%eax\n"
				".%s:\n"
				"\tmovl %%eax, %s(%%rip)\n",
				l1->value,l1->value,l2->value,l1->value,l2->value,
				tac->res->value);
			}
			else if(tac->op1->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\ttstl	$0, %%eax\n"
				"\tje .%s\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\ttstl	$0, %%eax\n"
				"\tje .%s\n"
				"\tmovl $1, %%eax\n"
				"\tjmp .%s\n"
				".%s:\n"
				"\tmovl $0, %%eax\n"
				".%s:\n"
				"\tmovl %%eax, %s(%%rip)\n",
				l1->value,tac->op2->value,l1->value,l2->value,l1->value,l2->value,
				tac->res->value);			
			}
			else if (tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\tmovl %%eax, %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\ttstl	$0, %%eax\n"
				"\tje .%s\n"
				"\ttstl	$0, %%edx\n"
				"\tje .%s\n"
				"\tmovl $1, %%eax\n"
				"\tjmp .%s\n"
				".%s:\n"
				"\tmovl $0, %%eax\n"
				".%s:\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,l1->value,l1->value,l2->value,l1->value,l2->value,
				tac->res->value);		
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%edx\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\ttstl	$0, %%edx\n"
				"\tje .%s\n"
				"\ttstl	$0, %%eax\n"
				"\tje .%s\n"
				"\tmovl $1, %%eax\n"
				"\tjmp .%s\n"
				".%s:\n"
				"\tmovl $0, %%eax\n"
				".%s:\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value, tac->op2->value,l1->value,l1->value,l2->value,l1->value,l2->value,
				tac->res->value);
			}
		}
		if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION){
				int numero2 = atoi(tac->op2->value);
				if(numero2==0){
				fprintf(fout,
				"\tmovl $0, %s(%%rip)\n",
				tac->res->value);
				}
				else{
				fprintf(fout,
				"\tcmpl $0, %%eax\n"
				"\tsetne %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->res->value);
				}
			}
			else{
				int numero2 = atoi(tac->op2->value);
				if(numero2==0){
				fprintf(fout,
				"\tmovl $0, %s(%%rip)\n",
				tac->res->value);
				}
				else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl $0, %%eax\n"
				"\tsetne %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,
				tac->res->value);
				}
			}
		}
		if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION){
				int numero1 = atoi(tac->op1->value);
				if(numero1==0){
				fprintf(fout,
				"\tmovl $0, %s(%%rip)\n",
				tac->res->value);
				}
				else{
				fprintf(fout,
				"\tcmpl $0, %%eax\n"
				"\tsetne %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->res->value);
				}
			}
			else{
				int numero1 = atoi(tac->op1->value);
				if(numero1==0){
				fprintf(fout,
				"\tmovl $0, %s(%%rip)\n",
				tac->res->value);
				}
				else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl $0, %%eax\n"
				"\tsetne %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value,
				tac->res->value);
				}
			}
		}
		if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
			int numero1 = atoi(tac->op1->value);
			int numero2 = atoi(tac->op2->value);
			int res = numero1&&numero2;
			fprintf(fout,
			"\tmovl $%d, %s(%%rip)\n",
			res,
			tac->res->value);
		}
		
}
void asmOr(TAC* tac, FILE* fout){
	HASH_NODE *l1, *l2, *l3;
	l1 = makeLable();
	l2 = makeLable(); 
	l3 = makeLable(); 
	if(!tac->op1 || !tac ->op2) return;
		if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION && tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\ttstl	$0, %%eax\n"
				"\tjne .%s\n"
				"\ttstl	$0, %%ebx\n"
				"\tje .%s\n"
				".%s:\n"
				"\tmovl $1, %%eax\n"
				"\tjmp .%s\n"
				".%s:\n"
				"\tmovl $0, %%eax\n"
				".%s:\n"
				"\tmovl %%eax, %s(%%rip)\n",
				l1->value,l2->value,l1->value,l3->value,l2->value,l3->value,
				tac->res->value);
			}
			else if(tac->op1->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\ttstl	$0, %%eax\n"
				"\tjne .%s\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\ttstl	$0, %%eax\n"
				"\tje .%s\n"
				".%s:\n"
				"\tmovl $1, %%eax\n"
				"\tjmp .%s\n"
				".%s:\n"
				"\tmovl $0, %%eax\n"
				".%s:\n"
				"\tmovl %%eax, %s(%%rip)\n",
				l1->value,tac->op2->value,l2->value,l1->value,l3->value,l2->value,l3->value,
				tac->res->value);			
			}
			else if (tac->op2->nature == NATURE_FUNCTION){
				fprintf(fout,
				"\ttstl	$0, %%eax\n"
				"\tjne .%s\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\ttstl	$0, %%eax\n"
				"\tje .%s\n"
				".%s:\n"
				"\tmovl $1, %%eax\n"
				"\tjmp .%s\n"
				".%s:\n"
				"\tmovl $0, %%eax\n"
				".%s:\n"
				"\tmovl %%eax, %s(%%rip)\n",
				l1->value,tac->op1->value,l2->value,l1->value,l3->value,l2->value,l3->value,
				tac->res->value);		
			}
			else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\ttstl	$0, %%eax\n"
				"\tjne .%s\n"
				"\tmovl %s(%%rip), %%eax\n"
				"\ttstl	$0, %%eax\n"
				"\tje .%s\n"
				".%s:\n"
				"\tmovl $1, %%eax\n"
				"\tjmp .%s\n"
				".%s:\n"
				"\tmovl $0, %%eax\n"
				".%s:\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,l1->value,tac->op2->value,l2->value,l1->value,l3->value,l2->value,l3->value,
				tac->res->value);	
			}
		}
		if(tac->op1->type == SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION){
				int numero2 = atoi(tac->op2->value);
				if(numero2==1){
				fprintf(fout,
				"\tmovl $1, %s(%%rip)\n",
				tac->res->value);
				}
				else{
				fprintf(fout,
				"\tcmpl $0, %%eax\n"
				"\tsetne %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->res->value);
				}
			}
			else{
				int numero2 = atoi(tac->op2->value);
				if(numero2==1){
				fprintf(fout,
				"\tmovl $1, %s(%%rip)\n",
				tac->res->value);
				}
				else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl $0, %%eax\n"
				"\tsetne %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,
				tac->res->value);
				}
			}
		}
		if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type == SYMBOL_IDENTIFIER){
			if(tac->op1->nature == NATURE_FUNCTION){
				int numero1 = atoi(tac->op1->value);
				if(numero1==1){
				fprintf(fout,
				"\tmovl $1, %s(%%rip)\n",
				tac->res->value);
				}
				else{
				fprintf(fout,
				"\tcmpl $0, %%eax\n"
				"\tsetne %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->res->value);
				}
			}
			else{
				int numero1 = atoi(tac->op1->value);
				if(numero1==1){
				fprintf(fout,
				"\tmovl $1, %s(%%rip)\n",
				tac->res->value);
				}
				else{
				fprintf(fout,
				"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl $0, %%eax\n"
				"\tsetne %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op2->value,
				tac->res->value);
				}
			}
		}
		if(tac->op1->type != SYMBOL_IDENTIFIER && tac->op2->type != SYMBOL_IDENTIFIER){
			int numero1 = atoi(tac->op1->value);
			int numero2 = atoi(tac->op2->value);
			int res = numero1||numero2;
			fprintf(fout,
			"\tmovl $%d, %s(%%rip)\n",
			res,
			tac->res->value);
		}
		
}
void asmNegado(TAC* tac, FILE* fout){

	if(tac->op1->type == SYMBOL_IDENTIFIER){
		if(tac->op1->nature == NATURE_FUNCTION){
			fprintf(fout,"\tcmpl	%%eax, $0\n"
				"\tsete %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->res->value);}
		else{fprintf(fout,"\tmovl %s(%%rip), %%eax\n"
				"\tcmpl	%%eax, $0\n"
				"\tsete %%al\n"
				"\tmovzbl %%al, %%eax\n"
				"\tmovl %%eax, %s(%%rip)\n",
				tac->op1->value,
				tac->res->value);}
	}
	else{
		int numero1 = atoi(tac->op1->value);
		if(numero1==0){
			fprintf(fout,
			"\tmovl $1, %s(%%rip)\n",
			tac->res->value);
		}
		else{
			fprintf(fout,
			"\tmovl $0, %s(%%rip)\n",
			tac->res->value);
		}
	}	
}





