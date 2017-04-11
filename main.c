#include <stdio.h>
#include "tokens.h"
#include "hash.h"

extern lineNumber;
extern FILE *yyin;
extern running;

int main(int argc, char **argv){

	int token;

	if(argc < 2){ 
		exit(0);
	}

	FILE* file = fopen(argv[1],"r");

	if(!file){
		printf ("erro ao abrir o arquivo %s\n",argv[1]);
	}
	else{
		yyin = file;
	}

	// inicializa
	initMe();

	while (running){
		token = yylex();
		
		if(!running)
			break;
		
		printf("token: %d (line %d)\n", token, getLineNumber());
	}


	printf ("numero de linhas: %d\n",lineNumber-1);

	printHash();

	fclose(yyin);

	exit(0);
}
