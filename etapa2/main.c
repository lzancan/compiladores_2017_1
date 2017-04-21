#include <stdio.h>
#include <stdlib.h>

extern char* yytext;
extern FILE *yyin;
void initMe(void);
int isRunning(void);
void printHash(void);

int yyparse(void);

int getLineNumber(void);

void printToken(int token);

int main(int argc, char **argv){

	int token;
	// exit (0) = ok; exit(1) = erro abrir ; exit(2) erro arquivo n existe; exit(3) = erro de sintaxe

	if(argc < 2){ 
		exit(0);
		printf("chame como \"./etapa2 input.txt\"\n");
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


	yyparse();

	printf ("numero de linhas: %d\n",getLineNumber()-1);

	printHash();

	fclose(yyin);

	exit(0);
}
