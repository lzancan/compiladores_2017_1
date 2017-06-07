#include <stdio.h>
#include <stdlib.h>

#include "semantic.h"

void setNature_dataType(int nature, HASH_NODE * hashNode, ASTREE* astreeNode){
	if(hashNode->nature != 0 || hashNode->dataType != 0){
		fprintf(stderr,"Erro semantico, [%s] já declarada\n",hashNode->value);
		//exit(4); // TODO verificar onde deve dar o exit(4)...	
	}
	hashNode->nature = nature;
	switch (astreeNode->type){
		case ASTREE_BYTE_TYPE: hashNode->dataType = DATATYPE_BYTE; break;
		case ASTREE_SHORT_TYPE: hashNode->dataType = DATATYPE_SHORT; break;
		case ASTREE_LONG_TYPE: hashNode->dataType = DATATYPE_LONG; break;
		case ASTREE_FLOAT_TYPE: hashNode->dataType = DATATYPE_FLOAT; break;
		case ASTREE_DOUBLE_TYPE: hashNode->dataType = DATATYPE_DOUBLE; break;
		default: break;	
	}	
}

int testVectorInit(ASTREE* astreeNode,int numberArguments){
	if(!astreeNode) 
		return 0;
	if(astreeNode->son[0] && !astreeNode->son[1]){
		//fprintf(stderr,"%d\n",numberArguments);
		//fprintf(stderr,"nao tem filho 1\n");	
		numberArguments--;
		if (numberArguments != 0){
			fprintf(stderr,"Numero de argumentos diferentes da declaracao na linha %d\n",getLineNumber());
			//exit(4); // TODO verificar onde deve dar o exit(4)...	
		}
	}
	
	if(astreeNode->son[0] && astreeNode->son[1]){
		//fprintf(stderr,"%d\n",numberArguments);
		numberArguments--;
		if(astreeNode->son[0]->valueType== astreeNode->son[1]->valueType){
			//fprintf(stderr,"valueType %d son[0] igual son [1] na linha %d\n",astreeNode->son[0]->valueType,getLineNumber());
		} else{ 
			fprintf(stderr,"Filhos com valueTypes diferentes [%d] e [%d] na linha %d\n",astreeNode->son[0]->valueType,astreeNode->son[1]->valueType,getLineNumber());
			//exit(4); // TODO verificar onde deve dar o exit(4)...	
		}
	}
	testVectorInit(astreeNode->son[0],numberArguments);
	testVectorInit(astreeNode->son[1],numberArguments);
	
}
