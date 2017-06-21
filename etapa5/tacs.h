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
TAC* tacReverse(TAC* tac);
void tacPrintBack(TAC* last);
void tacPrintForward(TAC* first);

#endif 

