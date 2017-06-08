#include "hash.h"
#include "astree.h"


// função que seta o nature e o datatype na tabela hash já na passada da árvore
void setNature_dataType(int nature, HASH_NODE * hashNode, ASTREE* astreeNode);
int testVectorInit(ASTREE* astreeNode,int numberArguments);
<<<<<<< Updated upstream
int setValueType(ASTREE* node);
int ajustLitValue(ASTREE* node);
=======
int mustBeBoolType(ASTREE* astreeNode);
int getFunctCallAstreeNode(HASH_NODE* hashNode, ASTREE* astreeNode);
int testFunctionParams(ASTREE* astreeNode1, ASTREE* astreeNode2);
int testIndiceVetor(ASTREE* astreeNode);
int testAtribuicao(HASH_NODE * hashNode, ASTREE* astreeNode);

>>>>>>> Stashed changes
