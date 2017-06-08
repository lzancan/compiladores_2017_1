#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"

void setNature_dataType(int nature, HASH_NODE * hashNode, ASTREE* astreeNode){
	if(hashNode->nature != 0 || hashNode->dataType != 0){
		fprintf(stderr,"Erro semantico, [%s] já declarada\n",hashNode->value);
		exit(4); // TODO verificar onde deve dar o exit(4)...
	if(hashNode->nature != 0){
		switch(hashNode->nature){
			case NATURE_ESCALAR: fprintf(stderr,"Variavel [%s] já declarada na linha %d\n",hashNode->value, getLineNumber()); 							break;
			case NATURE_FUNCTION: fprintf(stderr,"Funcao [%s] já declarada na linha %d\n",hashNode->value, getLineNumber()); 							break;
			case NATURE_VECTOR: fprintf(stderr,"Vetor [%s] já declarada na linha %d\n",hashNode->value, getLineNumber()); 
						break;
			default: break;
		}
		exit(4); // TODO verificar onde deve dar o exit(4)...	
	}
	hashNode->nature = nature;
	switch (astreeNode->type){
		case ASTREE_BYTE_TYPE: {hashNode->dataType = DATATYPE_BYTE;
                                astreeNode->valueType = VALUETYPE_INTEGER;} break;
		case ASTREE_SHORT_TYPE: {hashNode->dataType = DATATYPE_SHORT;
                                astreeNode->valueType = VALUETYPE_INTEGER;} break;
		case ASTREE_LONG_TYPE: {hashNode->dataType = DATATYPE_LONG;
                                astreeNode->valueType = VALUETYPE_INTEGER;} break;
		case ASTREE_FLOAT_TYPE: {hashNode->dataType = DATATYPE_FLOAT;
                                astreeNode->valueType = VALUETYPE_REAL;} break;
		case ASTREE_DOUBLE_TYPE: {hashNode->dataType = DATATYPE_DOUBLE;
                                astreeNode->valueType = VALUETYPE_REAL;} break;
		default: break;
	}
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
			exit(4); // TODO verificar onde deve dar o exit(4)...	
		}
	}

	if(astreeNode->son[0] && astreeNode->son[1]){
		numberArguments--;
		if(astreeNode->son[0]->valueType== astreeNode->son[1]->valueType){
			//fprintf(stderr,"valueType %d son[0] igual son [1] na linha %d\n",astreeNode->son[0]->valueType,getLineNumber());
		} else{
			fprintf(stderr,"Filhos com valueTypes diferentes [%d] e [%d] na linha %d\n",astreeNode->son[0]->valueType,astreeNode->son[1]->valueType,getLineNumber());
			exit(4); // TODO verificar onde deve dar o exit(4)...	
		}
	}
	testVectorInit(astreeNode->son[0],numberArguments);
	testVectorInit(astreeNode->son[1],numberArguments);

}

int setValueType(ASTREE* node){
	switch (node->type){
		case ASTREE_ADD: {
		    if(node->son[0]->valueType == 0)
                ajustLitValue(node->son[0]);
            if(node->son[1]->valueType == 0)
                ajustLitValue(node->son[1]);
            if(node->son[0]->valueType == VALUETYPE_STRING || node->son[0]->valueType == VALUETYPE_BOOLEAN || node->son[1]->valueType == VALUETYPE_STRING || node->son[1]->valueType == VALUETYPE_BOOLEAN)
                exit(4);
            else if(node->son[0]->valueType == VALUETYPE_REAL || node->son[1]->valueType == VALUETYPE_REAL){
                node->valueType = VALUETYPE_REAL;
            }
            else if(node->son[0]->valueType == VALUETYPE_INTEGER && node->son[1]->valueType == VALUETYPE_INTEGER){
                node->valueType = VALUETYPE_INTEGER;
			}} break;
		case ASTREE_SUB: {
		    if(node->son[0]->valueType == 0)
                ajustLitValue(node->son[0]);
            if(node->son[1]->valueType == 0)
                ajustLitValue(node->son[1]);
            if(node->son[0]->valueType == VALUETYPE_STRING || node->son[0]->valueType == VALUETYPE_BOOLEAN || node->son[1]->valueType == VALUETYPE_STRING || node->son[1]->valueType == VALUETYPE_BOOLEAN)
                exit(4);
            else if(node->son[0]->valueType == VALUETYPE_REAL || node->son[1]->valueType == VALUETYPE_REAL){
                node->valueType = VALUETYPE_REAL;
            }
            else if(node->son[0]->valueType == VALUETYPE_INTEGER && node->son[1]->valueType == VALUETYPE_INTEGER){
                node->valueType = VALUETYPE_INTEGER;
            }
			} break;
		case ASTREE_MUL:  {
		    if(node->son[0]->valueType == 0)
                ajustLitValue(node->son[0]);
            if(node->son[1]->valueType == 0)
                ajustLitValue(node->son[1]);
            if(node->son[0]->valueType == VALUETYPE_STRING || node->son[0]->valueType == VALUETYPE_BOOLEAN || node->son[1]->valueType == VALUETYPE_STRING || node->son[1]->valueType == VALUETYPE_BOOLEAN)
		        exit(4);
            else if(node->son[0]->valueType == VALUETYPE_REAL || node->son[1]->valueType == VALUETYPE_REAL){
                node->valueType = VALUETYPE_REAL;
            }
            else if(node->son[0]->valueType == VALUETYPE_INTEGER && node->son[1]->valueType == VALUETYPE_INTEGER){
                node->valueType = VALUETYPE_INTEGER;
            }
			} break;
		case ASTREE_DIV:  {
		    if(node->son[0]->valueType == 0)
                ajustLitValue(node->son[0]);
            if(node->son[1]->valueType == 0)
                ajustLitValue(node->son[1]);
		    if(node->son[0]->valueType == VALUETYPE_STRING || node->son[0]->valueType == VALUETYPE_BOOLEAN || node->son[1]->valueType == VALUETYPE_STRING || node->son[1]->valueType == VALUETYPE_BOOLEAN)
		        exit(4);
            else
                node->valueType = VALUETYPE_REAL;
			} break;
		case ASTREE_LESS_THAN:    {
		    if(node->son[0]->valueType == 0)
                ajustLitValue(node->son[0]);
            if(node->son[1]->valueType == 0)
                ajustLitValue(node->son[1]);
		    if(node->son[0]->valueType == VALUETYPE_STRING || node->son[0]->valueType == VALUETYPE_BOOLEAN || node->son[1]->valueType == VALUETYPE_STRING || node->son[1]->valueType == VALUETYPE_BOOLEAN)
		        exit(4);
            else
                node->valueType = VALUETYPE_BOOLEAN;
			} break;
		case ASTREE_GREATER_THAN:      {
		    if(node->son[0]->valueType == 0)
                ajustLitValue(node->son[0]);
            if(node->son[1]->valueType == 0)
                ajustLitValue(node->son[1]);
		    if(node->son[0]->valueType == VALUETYPE_STRING || node->son[0]->valueType == VALUETYPE_BOOLEAN || node->son[1]->valueType == VALUETYPE_STRING || node->son[1]->valueType == VALUETYPE_BOOLEAN)
		        exit(4);
            else
                node->valueType = VALUETYPE_BOOLEAN;
			} break;
		case ASTREE_LE:      {
		    if(node->son[0]->valueType == 0)
                ajustLitValue(node->son[0]);
            if(node->son[1]->valueType == 0)
                ajustLitValue(node->son[1]);
		    if(node->son[0]->valueType == VALUETYPE_STRING || node->son[0]->valueType == VALUETYPE_BOOLEAN || node->son[1]->valueType == VALUETYPE_STRING || node->son[1]->valueType == VALUETYPE_BOOLEAN)
		        exit(4);
            else
                node->valueType = VALUETYPE_BOOLEAN;
			} break;
		case ASTREE_GE:      {
		    if(node->son[0]->valueType == 0)
                ajustLitValue(node->son[0]);
            if(node->son[1]->valueType == 0)
                ajustLitValue(node->son[1]);
		    if(node->son[0]->valueType == VALUETYPE_STRING || node->son[0]->valueType == VALUETYPE_BOOLEAN || node->son[1]->valueType == VALUETYPE_STRING || node->son[1]->valueType == VALUETYPE_BOOLEAN)
		        exit(4);
            else
                node->valueType = VALUETYPE_BOOLEAN;
			} break;
		case ASTREE_EQ:      {
		    if(node->son[0]->valueType == 0)
                ajustLitValue(node->son[0]);
            if(node->son[1]->valueType == 0)
                ajustLitValue(node->son[1]);
		    if(node->son[0]->valueType == VALUETYPE_STRING || node->son[0]->valueType == VALUETYPE_BOOLEAN || node->son[1]->valueType == VALUETYPE_STRING || node->son[1]->valueType == VALUETYPE_BOOLEAN)
		        exit(4);
            else
                node->valueType = VALUETYPE_BOOLEAN;
			} break;
		case ASTREE_NE:      {
		    if(node->son[0]->valueType == 0)
                ajustLitValue(node->son[0]);
            if(node->son[1]->valueType == 0)
                ajustLitValue(node->son[1]);
		    if(node->son[0]->valueType == VALUETYPE_STRING || node->son[0]->valueType == VALUETYPE_BOOLEAN || node->son[1]->valueType == VALUETYPE_STRING || node->son[1]->valueType == VALUETYPE_BOOLEAN)
		        exit(4);
            else
                node->valueType = VALUETYPE_BOOLEAN;
			} break;
		case ASTREE_AND:      {
		    if(node->son[0]->valueType == VALUETYPE_BOOLEAN && node->son[1]->valueType == VALUETYPE_BOOLEAN)
                node->valueType = VALUETYPE_BOOLEAN;
            else
                exit(4);
			} break;
		case ASTREE_OR:  {
		    if(node->son[0]->valueType == VALUETYPE_BOOLEAN && node->son[1]->valueType == VALUETYPE_BOOLEAN)
                node->valueType = VALUETYPE_BOOLEAN;
            else
                exit(4);
			} break;
        case ASTREE_PARENTESES:{
            if(node->son[0]->valueType == 0)
                ajustLitValue(node->son[0]);
		    if(node->son[0]->valueType == VALUETYPE_STRING)
		        exit(4);
            else
                node->valueType = node->son[0]->valueType;
			} break;
		case ASTREE_NEGATIVO: {
		    if(node->son[0]->valueType == 0)
                ajustLitValue(node->son[0]);
			if(node->son[0]->valueType == VALUETYPE_STRING || node->son[0]->valueType == VALUETYPE_BOOLEAN)
		        exit(4);
            else
                node->valueType = node->son[0]->valueType;
			} break;
		case ASTREE_NEGADO: {
		    if(node->son[0]->valueType == VALUETYPE_BOOLEAN)
                node->valueType = VALUETYPE_BOOLEAN;
            else
                exit(4);
			} break;
        case ASTREE_COLCHETES: {
            if(node->son[0]->valueType == 0)
                ajustLitValue(node->son[0]);
		    if(node->son[0]->valueType == VALUETYPE_INTEGER)
                node->valueType = VALUETYPE_INTEGER;
            else
                exit(4);
			} break;
		default: break;
	}

	fprintf(stderr, "Type %d valueType %d linha %d\n", node->type, node->valueType, getLineNumber());
	return 0;
}
int ajustLitValue(ASTREE* node){
    switch (node->symbol->dataType){
		case DATATYPE_BYTE: {node->valueType = VALUETYPE_INTEGER;} break;
		case DATATYPE_SHORT: {node->valueType = VALUETYPE_INTEGER;} break;
		case DATATYPE_LONG: {node->valueType = VALUETYPE_INTEGER;} break;
		case DATATYPE_FLOAT: {node->valueType = VALUETYPE_REAL;} break;
		case DATATYPE_DOUBLE: {node->valueType = VALUETYPE_REAL;} break;
		default: break;
	}
}

int mustBeBoolType(ASTREE* astreeNode){
	if(astreeNode->valueType != VALUETYPE_BOOLEAN){
		fprintf(stderr,"Expressao nao e booleana em %d\n",getLineNumber());
		exit(4);	
		return -1;
	}
	return 0;
}

int getFunctCallAstreeNode(HASH_NODE* hashNode, ASTREE* astreeNode){
	if(hashNode->dataType == 0){
			fprintf(stderr,"Funcao [%s] nao declarada na linha %d\n",hashNode->value, getLineNumber());			
			exit(4);
			return -1;
	}
	ASTREE* node = hashNode->astreeNode;
	return (testFunctionParams(node, astreeNode));
}

int testFunctionParams(ASTREE* astreeNode1, ASTREE* astreeNode2){
	if(!astreeNode1){ // se astreeNode nao existe na hash
		if(!astreeNode2){ // se o astreeNode passado existe
			return 0;
		}
		else{
			if(astreeNode2->son[0] || astreeNode2->son[1]){
				fprintf(stderr,"Muitos parametros passados na funcao da linha %d\n",getLineNumber());				
				exit(4);
				return -1;
			}
			return -1;
		}
		
	}
	if(!astreeNode2){ // se astreeNode passado nao existe
		if(astreeNode1){ // mas astreenode da hash existe		
			fprintf(stderr,"Faltam parametros na funcao da linha %d\n",getLineNumber());			
			exit(4);
			return -1;	
		}
	}
	if(astreeNode1->valueType != astreeNode2->valueType){ //TODO intercambiar entre int e real...
			if(astreeNode1->valueType == VALUETYPE_INTEGER){
				if(astreeNode2->valueType != VALUETYPE_REAL){
					fprintf(stderr,"Parametros incompativeis na funcao da linha %d\n",getLineNumber());			
					exit(4);
					return -1;
				}
			}
			if(astreeNode1->valueType == VALUETYPE_REAL){
				if(astreeNode2->valueType != VALUETYPE_INTEGER){
					fprintf(stderr,"Parametros incompativeis na funcao da linha %d\n",getLineNumber());			
					exit(4);
					return -1;
				}	
			}	
	}

	testFunctionParams(astreeNode1->son[0], astreeNode2->son[0]);
	testFunctionParams(astreeNode1->son[1], astreeNode2->son[1]);
	
	
}


int testIndiceVetor(ASTREE* astreeNode){
	if(astreeNode->valueType != VALUETYPE_INTEGER && astreeNode->valueType != VALUETYPE_CHAR){
		fprintf(stderr,"Atribuicao de vetor com numero nao inteiro, nem char na linha %d\n",getLineNumber());	
		exit(4); //TODO verificar...		
		return -1;
	}
}


int testAtribuicao(HASH_NODE * hashNode, ASTREE* astreeNode){
	switch(hashNode->dataType){
		case DATATYPE_BYTE: 	if(astreeNode->valueType != VALUETYPE_INTEGER){
						fprintf (stderr,"Expressao incompativel com o tipo na linha %d\n",getLineNumber());		
						exit(4);
					}
					break;
		case DATATYPE_SHORT:	if(astreeNode->valueType != VALUETYPE_INTEGER){
						fprintf (stderr,"Expressao incompativel com o tipo na linha %d\n",getLineNumber());		
						exit(4);
					}
					break;
		case DATATYPE_LONG:	if(astreeNode->valueType != VALUETYPE_INTEGER){
						fprintf (stderr,"Expressao incompativel com o tipo na linha %d\n",getLineNumber());		
						exit(4);
					}
					break;
		case DATATYPE_FLOAT:	if(astreeNode->valueType != VALUETYPE_REAL){
						fprintf (stderr,"Expressao incompativel com o tipo na linha %d\n",getLineNumber());		
						exit(4);
					}
					break;
		case DATATYPE_DOUBLE:	if(astreeNode->valueType != VALUETYPE_REAL){
						fprintf (stderr,"Expressao incompativel com o tipo na linha %d\n",getLineNumber());		
						exit(4);
					}
					break;
		default: break;
	}

}



