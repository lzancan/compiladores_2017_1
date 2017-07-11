#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#include "tacs.h"


void asmGen(TAC* first);
void asmAdd(TAC* tac, FILE* fout);
void asmSub(TAC* tac, FILE* fout);
void asmMul(TAC* tac, FILE* fout);
void asmDiv(TAC* tac, FILE* fout);
void funcPush(TAC* tac, FILE* fout);
void funcPop(TAC* tac, FILE* fout);
void asmPrint(TAC* tac,FILE* fout);
void printHashAsm(FILE* fout);
