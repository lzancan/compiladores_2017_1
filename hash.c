#include "hash.h"

// imprime um token
void printToken(int token){
	switch(token){
		// PALAVRAS RESERVADAS
		case KW_BYTE: fprintf(stderr,"BYTE"); break;
		case KW_SHORT: fprintf(stderr,"SHORT"); break;
		case KW_LONG: fprintf(stderr,"LONG"); break;
		case KW_FLOAT: fprintf(stderr,"FLOAT"); break;
		case KW_DOUBLE: fprintf(stderr,"DOUBLE"); break;
		case KW_WHEN: fprintf(stderr,"WHEN"); break;
		case KW_THEN: fprintf(stderr,"THEN"); break;
		case KW_ELSE: fprintf(stderr,"ELSE"); break;
		case KW_WHILE: fprintf(stderr,"WHILE"); break;
		case KW_FOR: fprintf(stderr,"FOR"); break;
		case KW_READ: fprintf(stderr,"READ"); break;
		case KW_RETURN: fprintf(stderr,"RETURN"); break;
		case KW_PRINT: fprintf(stderr,"PRINT"); break;
		// operadores duplos
		case OPERATOR_LE: fprintf(stderr,"OPERATOR_LE"); break;
		case OPERATOR_GE: fprintf(stderr,"OPERATOR_GE"); break;
		case OPERATOR_EQ: fprintf(stderr,"OPERATOR_EQ"); break;
		case OPERATOR_NE: fprintf(stderr,"OPERATOR_NE"); break;
		case OPERATOR_AND: fprintf(stderr,"OPERATOR_AND"); break;
		case OPERATOR_OR: fprintf(stderr,"OPERATOR_OR"); break;
		// identificador
		case TK_IDENTIFIER: fprintf(stderr,"TK_IDENTIFIER"); break;
		// literais
		case LIT_INTEGER: fprintf(stderr,"LIT_INTEGER"); break;
		case LIT_REAL: fprintf(stderr,"LIT_REAL"); break;
		case LIT_CHAR: fprintf(stderr,"LIT_CHAR"); break;
		case LIT_STRING: fprintf(stderr,"LIT_STRING"); break;
		// erro
		case TOKEN_ERROR: fprintf(stderr,"TOKEN_ERROR"); break;

		default:					fprintf(stderr,"default");		break;
	}
}

// inicializa a hash, fazendo os nodos serem null
void initHash()
{
	int i=0;
	
	for(i=0 ; i < HASH_SIZE ; i++)
		hashTable[i] = NULL;
}

// imprime um nodo da hash
void printNode(hashNode * node){
	if(node){
		fprintf(stderr,"Type: ");
		printToken(node->type);
		fprintf(stderr,", Value: %s\n",node->value);
	}	
}

// imprime a hash toda
void printHash(){
	int i=0;

	hashNode * node = NULL;

	fprintf(stderr,"Hash printing:\nInicio de impressao");
	for(i=0 ; i < HASH_SIZE ; i++){
		for(node = hashTable[i] ; node ; node = node->next){
			printNode(node);
		}
	}
	fprintf(stderr,"Termino de impressao\n");	
}




// procura por um nodo na hash, retorna null se não encontrou
hashNode *getNode(char *value){

	int i=0;
	hashNode * node = NULL;
	
	for(i=0 ; i < HASH_SIZE ; i++){
		for(node = hashTable[i] ; node ; node = node->next){
			if(strcmp(node->value,value) == 0){
				return node;
			}
		}
	}
	return NULL;
}

// gera o endereço hash baseado no nome (char *value)
int hashAddress(char *value){
	int add =1;
	int i=0;
	
	for(i=0; i<strlen(value); ++i){
		add = ((add * value[i]) % HASH_SIZE ) +1;
	}
	return add-1;
}

/* adiciona um caractere terminador no final de uma string */
char * addTerminator(char* value){
	int i = 0;
	char* value2 = NULL;
	value2 = (char*)calloc(strlen(value),sizeof(char));
	for(i=0 ; i<strlen(value); i++)
		value2[i] = value[i];
	value2[strlen(value)]='\0';

	return value2;

}

// insere nodo na hash
hashNode * insertHash(char * value, int type){

	int newAddress = 0;
	int j=0;
	hashNode * newNode = calloc(1,sizeof(hashNode));
	hashNode * returnValue = NULL;
	hashNode * existingNode = NULL;
	
	newAddress = hashAddress(value);

	switch(type){

		case TK_IDENTIFIER:
			newNode->value = addTerminator(value);
			break;

		case LIT_INTEGER:
			newNode->value = addTerminator(value);
			break;
		case LIT_REAL:
			newNode->value = addTerminator(value);
			break;
		case LIT_CHAR:
			newNode->value = (char*)calloc(2,sizeof(char));
			newNode->value[0] = value[1];
			newNode->value[1] = '\0';
			break;
		case LIT_STRING:
			newNode->value = (char*)calloc(strlen(value)-1,sizeof(char));
			for(j=1 ; j < strlen(value)-1 ; j++)
				newNode->value[j-1]=value[j];
			newNode->value[strlen(value)-2]='\0';
			break;
		default: 
			newNode->value = addTerminator(value);  
			break;
	}
	
	/* teste para ver se não está na hash */
	existingNode = getNode(newNode->value);
	
	if(!existingNode)
	{
		/* atribuição do novo nodo */
		newNode->type = type;
		newNode->next = hashTable[newAddress];

		hashTable[newAddress] = newNode;
		returnValue = newNode;
	}
	else
	{
		/* retorna o nodo já existente */
		returnValue = existingNode;
	}
	if(!returnValue)
	{
		fprintf(stderr,"CUIDADO : insert da Hash retornando valor NULL\n");
	}
	
	return returnValue;
	
}
