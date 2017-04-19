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
		int i;
		switch(type){
			case TK_IDENTIFIER:
				newNode->value = addStringTerminator(value);
				break;

			case LIT_INTEGER:
				newNode->value = addStringTerminator(value);
				break;
			case LIT_REAL:
				newNode->value = addStringTerminator(value);
				break;
			case LIT_CHAR:
				newNode->value = (char*)calloc(2,sizeof(char));
				newNode->value[0] = value[1];
				newNode->value[1] = '\0';
				break;
			case LIT_STRING:
				newNode->value = (char*)calloc(strlen(value)-1,sizeof(char));
				for(i=1 ; i < strlen(value)-1 ; i++)
				newNode->value[i-1]=value[i];
				newNode->value[strlen(value)-2]='\0';
				break;
			default: 
				newNode->value = addStringTerminator(value);  
				break;
		}
		// senão está na hash, insere
		newNode->type = type;
		newNode->next = hashTable[newAddress];
		hashTable[newAddress] = newNode;

		if(!newNode){
			fprintf (stderr,"newNode return NULL in insertHash\n");		
		}
		return newNode;
	}
}


// imprime um token
void printToken(int token){
	switch(token){
		// PALAVRAS RESERVADAS
		case KW_BYTE: fprintf(stderr,"BYTE"); 
			break;
		case KW_SHORT: fprintf(stderr,"SHORT"); 
			break;
		case KW_LONG: fprintf(stderr,"LONG"); 
			break;
		case KW_FLOAT: fprintf(stderr,"FLOAT"); 
			break;
		case KW_DOUBLE: fprintf(stderr,"DOUBLE"); 
			break;
		case KW_WHEN: fprintf(stderr,"WHEN"); 
			break;
		case KW_THEN: fprintf(stderr,"THEN"); 
			break;
		case KW_ELSE: fprintf(stderr,"ELSE"); 
			break;
		case KW_WHILE: fprintf(stderr,"WHILE"); 
			break;
		case KW_FOR: fprintf(stderr,"FOR"); 
			break;
		case KW_READ: fprintf(stderr,"READ"); 
			break;
		case KW_RETURN: fprintf(stderr,"RETURN"); 
			break;
		case KW_PRINT: fprintf(stderr,"PRINT"); 
			break;
		// operadores duplos
		case OPERATOR_LE: fprintf(stderr,"OPERATOR_LE"); 
			break;
		case OPERATOR_GE: fprintf(stderr,"OPERATOR_GE"); 
			break;
		case OPERATOR_EQ: fprintf(stderr,"OPERATOR_EQ"); 
			break;
		case OPERATOR_NE: fprintf(stderr,"OPERATOR_NE"); 	
			break;
		case OPERATOR_AND: fprintf(stderr,"OPERATOR_AND"); 
			break;
		case OPERATOR_OR: fprintf(stderr,"OPERATOR_OR"); 
			break;
		// identificador
		case TK_IDENTIFIER: fprintf(stderr,"TK_IDENTIFIER"); 
			break;
		// literais
		case LIT_INTEGER: fprintf(stderr,"LIT_INTEGER"); 
			break;
		case LIT_REAL: fprintf(stderr,"LIT_REAL"); 
			break;
		case LIT_CHAR: fprintf(stderr,"LIT_CHAR"); 
			break;
		case LIT_STRING: fprintf(stderr,"LIT_STRING"); 
			break;
		// erro
		case TOKEN_ERROR: fprintf(stderr,"TOKEN_ERROR"); 
			break;
		default: fprintf(stderr,"default");
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




