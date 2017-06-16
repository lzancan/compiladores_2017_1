#include <stdio.h>
#include <stdlib.h>
#include "hash.h"


// inicializa a hash, fazendo os nodos serem null
void initHash(){
	int i;
	for(i=0 ; i < HASH_SIZE ; i++){
		hashTable[i] = NULL;
	}
}

// gera o endereço hash baseado no nome (char *value)
int hashAddress(char *value){
	int i;
	int address = 1;
	for(i=0; i<strlen(value); i++){
		address = ((address * value[i]) % HASH_SIZE) +1;
	}
	return address-1;
}

// procura por um nodo na hash, retorna null se não encontrou
HASH_NODE *hashFind(char *value){
	int i;
	HASH_NODE * node = NULL;
	for(i=0 ; i < HASH_SIZE ; i++){
		for(node = hashTable[i] ; node ; node = node->next){
			if(strcmp(node->value,value) == 0){
				return node;
			}
		}
	}
	return NULL;
}

/// adiciona o '\0' ao final de uma string
char * addStringTerminator(char* value){
	int i;
	char* string = (char*)calloc(strlen(value),sizeof(char));
	for(i=0 ; i<strlen(value) ; i++){
		string[i] = value[i];
	}
	string[strlen(value)]='\0';
	return string;

}

// insere nodo na hash
HASH_NODE * insertHash(int type,char * value){

	HASH_NODE * newNode;

	int newAddress = hashAddress(value);


	// se esta na hash retorna o proprio nodo
	if(newNode = hashFind (value)){
		return newNode;
	}
	else{
		newNode=calloc(1,sizeof(HASH_NODE));
		int i=0;
		switch(type){
			case SYMBOL_IDENTIFIER:
				newNode->value = addStringTerminator(value);
				break;

			case SYMBOL_LIT_INTEGER:
				newNode->value = addStringTerminator(value);
				break;
			case SYMBOL_LIT_REAL:
				newNode->value = addStringTerminator(value);
				break;
			case SYMBOL_LIT_CHAR:
				newNode->value = (char*)calloc(2,sizeof(char));
				newNode->value[0] = value[1];
				newNode->value[1] = '\0';
				break;
			case SYMBOL_LIT_STRING:
				newNode->value = (char*)calloc(strlen(value)-1,sizeof(char));
				for(i=1 ; i < strlen(value)-1 ; i++)
				newNode->value[i-1]=value[i];
				newNode->value[strlen(value)-2]='\0';
				break;
		}
		// senão está na hash, insere
		newNode->type = type;
		newNode->next = hashTable[newAddress];
		hashTable[newAddress] = newNode;

		if(!newNode){
			fprintf (stderr,"newNode return NULL in insertHash\n");
		}
		newNode->nature = 0;
		newNode->dataType = 0;
		return newNode;
	}
}


// imprime um token
void printToken(int token){
	switch(token){
		// identificador
		case SYMBOL_IDENTIFIER: fprintf(stderr,"IDENTIFIER");
			break;
		// literais
		case SYMBOL_LIT_INTEGER: fprintf(stderr,"LIT_INTEGER");
			break;
		case SYMBOL_LIT_REAL: fprintf(stderr,"LIT_REAL");
			break;
		case SYMBOL_LIT_CHAR: fprintf(stderr,"LIT_CHAR");
			break;
		case SYMBOL_LIT_STRING: fprintf(stderr,"LIT_STRING");
			break;
	}
}


// imprime um nodo da hash
void printHashNode(HASH_NODE * node){
	if(node){
		fprintf(stderr,"Type: ");
		printToken(node->type);
		fprintf(stderr,", Value: %s",node->value);
		fprintf(stderr,", HashAddress: %d\n",hashAddress(node->value));
	}
}

// imprime a hash toda
void printHash(){
	int i;
	HASH_NODE * node = NULL;

	fprintf(stderr,"Hash printing:\nInicio de impressao\n");
	for(i=0 ; i < HASH_SIZE ; i++){
		for(node = hashTable[i] ; node ; node = node->next){
			printHashNode(node);
		}
	}
	fprintf(stderr,"Termino de impressao\n");
}




