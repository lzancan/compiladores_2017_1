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

	if(!openFile(argv[1])){
		exit(1);
	}

	// inicializa
	initMe();

	while (running){
		token = yylex();
		
		if(!running)
			break;
		
		printf("token: %d (line %d)\n", token, getLineNumber());
	}

	closeFile();

	printf ("numero de linhas: %d\n",lineNumber-1);

	printHash();

	exit(0);
}
