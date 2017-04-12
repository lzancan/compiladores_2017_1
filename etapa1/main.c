#include <stdio.h>
#include <stdlib.h>

int yylex(void);
extern char* yytext;
extern FILE *yyin;
void initMe(void);
int isRunning(void);
void printHash(void);


int getLineNumber(void);

void printToken(int token);

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

	while (isRunning()){
		token = yylex();
		
		if(!isRunning())
			break;
		printToken(token);
		printf(",%s,linha: %d\n",yytext,getLineNumber());
	}


	printf ("numero de linhas: %d\n",getLineNumber()-1);

	printHash();

	fclose(yyin);

	exit(0);
}
