#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "semantic.h"

#define TAC_SYMBOL 1
#define TAC_ADD 2
#define TAC_SUB 3
#define TAC_MUL 4
#define TAC_DIV 5
#define TAC_IFZ 6
#define TAC_LABEL 7
#define TAC_LT 8
#define TAC_GT 9
#define TAC_LE 10
#define TAC_GE 11
#define TAC_EQ 12
#define TAC_NE 13
#define TAC_AND 14
#define TAC_OR 15
#define TAC_NEGATIVO 16
#define TAC_NEGADO 17
#define TAC_GOTO 18
#define TAC_RET 19
#define TAC_READ 20
#define TAC_PRINT 21
#define TAC_INC 22
#define TAC_MOVE 23
#define TAC_MOVE_VETOR 24
#define TAC_EXPRESSAO 25
#define TAC_CALLFUNC 26
#define TAC_RETURN 27
#define TAC_BEGINFUNC 28
#define TAC_ENDFUNC 29
#define TAC_FUNCPUSH 30
#define TAC_FUNCPOP 31
#define TAC_EXPRESSAO_VETOR 32
#define TAC_PARAMETRO 33
#define TAC_PARAMETRO_CALL 34
#define TAC_VAR_GLOBAL 35


typedef struct tac_struct
{
	int type;
	HASH_NODE* res;
	HASH_NODE* op1;
	HASH_NODE* op2;
	struct tac_struct* prev;
	struct tac_struct* next;
}TAC;

TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2);
TAC* tacJoin(TAC* l1, TAC* l2);
TAC* tacGenerate(ASTREE* node);
TAC* makeWhenThen(TAC* code0, TAC* code1);
TAC* makeWhenThenElse(TAC* code0, TAC* code1, TAC* code2);
TAC* makeFor(HASH_NODE* nodeSymbol, TAC* code0, TAC* code1, TAC* code2);
TAC* makeWhile(TAC* code0, TAC* code1);

TAC* tacReverse(TAC* tac);
void tacPrintBack(TAC* last);
void tacPrintForward(TAC* first);

#endif 

