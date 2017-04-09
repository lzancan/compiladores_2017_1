%{

	#include "tokens.h"
	#include "hash.h"

	// esboço das funções
	int getLineNumber(void);
	void initMe(void);
	int isRunning(void);
	int openFile(char* filePath);
	int closeFile();
	// variáveis
	int lineNumber = 1; // inicia com 1, pois só incrementa ao achar o \n (que vai para a próxima já)
	int running = 1; // indica running da análise
%}

NUM [0-9]
ALPHANUM [0-9a-fA-F]
ALPHAUNDER [a-zA-Z_]
ALPHANUMUNDER [a-zA-Z0-9_]

%x MULTI_LINE_COMMENT

%%
					
byte					{return KW_BYTE; printf ("byte\n"); /* palavras reservadas */}
short 					{return KW_SHORT;}
long 					{return KW_LONG;}
float 					{return KW_FLOAT;}
double 					{return KW_DOUBLE;}
when 					{return KW_WHEN;}
then 					{return KW_THEN;}
else 					{return KW_ELSE;}
while 					{return KW_WHILE;}
for 					{return KW_FOR;}
read 					{return KW_READ;}
print 					{return KW_PRINT;}
return 					{return KW_RETURN;}

[,;:()\[\]\{}+\-*/<>=!&$#]		{return yytext[0];/* codigo ascii */}
					
"<=" 					{return OPERATOR_LE;/* operadores compostos */}
">=" 					{return OPERATOR_GE;}
"==" 					{return OPERATOR_EQ;}
"!=" 					{return OPERATOR_NE;}
"&&" 					{return OPERATOR_AND;}
"||" 					{return OPERATOR_OR;}
					
{ALPHAUNDER}{ALPHANUMUNDER}*		{insertHash(yytext,TK_IDENTIFIER); return TK_IDENTIFIER;/* identificador, insere na hash e retorna o token */}
					
{NUM}+ 					{insertHash(yytext,LIT_INTEGER);return LIT_INTEGER;/* literais, insere na hash e retorna o token */}
{NUM}+.{NUM}+		 		{insertHash(yytext,LIT_REAL);return LIT_REAL;}
\'.\'					{insertHash(yytext,LIT_CHAR);return LIT_CHAR;}
\"([^\\\"]|\\.)*\"			{insertHash(yytext,LIT_STRING);return LIT_STRING;}
					
"//".*"\n" 				{lineNumber++;/* comentario simples, com "\n" */}
					
"/*" 					BEGIN(MULTI_LINE_COMMENT);
					
"\n"					{lineNumber++;/* encontrou "\n", soma 1 ao numberLines */}
					
. 					{return TOKEN_ERROR;/* coletor de lixo */}	
			
<MULTI_LINE_COMMENT>"*/" 		BEGIN(INITIAL);
<MULTI_LINE_COMMENT>.
<MULTI_LINE_COMMENT>"\n" 		{lineNumber++;}

%%


int getLineNumber(void)
{
	return lineNumber;
}

int isRunning(void){
	return running;
}

void initMe(void){
	startHash();
}

int openFile(char* filePath){
	FILE* file = fopen(filePath,"r");

	if(!file){
		return 0;
	}
	else{
		yyin = file;
		return 1;
	}
}

int closeFile(){
	fclose(yyin);
	return 1;
}

int yywrap()
{
	running = 0;
	return 1;
}





