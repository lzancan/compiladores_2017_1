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
void printVarGlobal(TAC* tac, FILE* fout);
void asmGt(TAC* tac, FILE* fout);
void asmLt(TAC* tac, FILE* fout);
void asmLe(TAC* tac, FILE* fout);
void asmGe(TAC* tac, FILE* fout);
void asmEq(TAC* tac, FILE* fout);
void asmNe(TAC* tac, FILE* fout);
void asmAnd(TAC* tac, FILE* fout);
void asmOr(TAC* tac, FILE* fout);
void parametrosFunc(TAC* tac,FILE* fout);
