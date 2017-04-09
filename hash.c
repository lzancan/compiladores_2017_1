#include "hash.h"

// impressao dos tokens
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

// inicializa a hash
void startHash()
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

/* printa a hash */
void printHash()
{
	int i=0;
	hashNode * node = NULL;
	
	fprintf(stderr,"Imprimindo a hash...\n");
	
	for(i=0 ; i < HASH_SIZE ; i++)
		for(node = hashTable[i] ; node ; node = node->next)
		{
			printNode(node);
		}
	fprintf(stderr,"Fim da impressao...\n");	
}




/* 	Função para obter um nodo da hash, buscando pelo campo 'value'
	Retorna NULL se não encontrar o valor */
hashNode * getNode(char *text)
{
	int i=0;
	hashNode * node = NULL;
	
	for(i=0 ; i < HASH_SIZE ; i++)
		for(node = hashTable[i] ; node ; node = node->next)
		{
			if(strcmp(node->value,text) == 0)
			{
				return node;
			}
		}
	return NULL;

}

/* gera o valor de endereço da hash baseado na string */
int address(char * text)
{
	int add =1;
	int i=0;
	
	for(i=0; i<strlen(text); ++i)
	{
			add = ((add * text[i]) % HASH_SIZE ) +1;
	}
	return add-1;
}

/* adiciona um caractere terminador no final de uma string */
char * addTerminator(char* text)
{
	
	int j = 0;
	char* value = NULL;
	
	value = (char*)calloc(strlen(text),sizeof(char));
	for(j=0 ; j<strlen(text); j++)
		value[j] = text[j];
	value[strlen(text)]='\0';
	
	return value;

}

// insere nodo na hash
hashNode * insertHash(char * text, int type){


	int newAddress = 0;
	int j=0;
	hashNode * newNode = calloc(1,sizeof(hashNode));
	hashNode * returnValue = NULL;
	hashNode * existingNode = NULL;
	
	newAddress = address(text);
	
	// switch do tipo para decidir como tratar o texto 
	switch(type){

		case TK_IDENTIFIER:
			newNode->value = addTerminator(text);
			break;

		case LIT_INTEGER:
			newNode->value = addTerminator(text);
			break;
		case LIT_REAL:
			newNode->value = addTerminator(text);
			break;
		case LIT_CHAR:
			newNode->value = (char*)calloc(2,sizeof(char));
			newNode->value[0] = text[1];
			newNode->value[1] = '\0';
			break;
		case LIT_STRING:
			newNode->value = (char*)calloc(strlen(text)-1,sizeof(char));
			for(j=1 ; j < strlen(text)-1 ; j++)
				newNode->value[j-1]=text[j];
			newNode->value[strlen(text)-2]='\0';
			break;
		default: 
			newNode->value = addTerminator(text);  
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
