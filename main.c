#include <stdio.h>
#include "tokens.h"
#include "hash.h"

extern lineNumber;
extern FILE *yyin;

int main(int argc, char **argv){

	if(argc < 2){ 
		exit(0);
	}

	if(!openFile(argv[1])){
		exit(1);
	}

	// inicializa
	initMe();

	while (yyin != EOF){
		yylex();
	}

	closeFile();

	printf ("numero de linhas: %d\n",lineNumber);

	exit(0);
}
