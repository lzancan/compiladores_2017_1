#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "semantic.h"

#define TAC_SYMBOL 1
#define TAC_ADD 2
#define TAC_SUB 3
#define TAC_IFZ 4
#define TAC_LABLE 5

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

