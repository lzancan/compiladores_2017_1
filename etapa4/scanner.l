%{
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "hash.h"
	#include "astree.h"	
	#include "y.tab.h"

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
ALPHANUM [0-9a-zA-Z]
ALPHAUNDER [a-zA-Z_]
ALPHANUMUNDER [a-zA-Z0-9_]

%x MULTI_LINE_COMMENT

%%
					
"byte"					{return KW_BYTE; /* palavras reservadas */}
"short" 					{return KW_SHORT;}
"long" 					{return KW_LONG;}
"float" 					{return KW_FLOAT;}
"double" 					{return KW_DOUBLE;}
"when" 					{return KW_WHEN;}
"then" 					{return KW_THEN;}
"else" 					{return KW_ELSE;}
"while" 					{return KW_WHILE;}
"for" 					{return KW_FOR;}
"to" 					{return KW_TO;}
"read" 					{return KW_READ;}
"return" 					{return KW_RETURN;}
"print" 					{return KW_PRINT;}

[-,;:()\[\]\{}+\*/<>=!&$#]		{return yytext[0];/* codigo ascii */}
					
"<=" 					{return OPERATOR_LE;/* operadores compostos */}
">=" 					{return OPERATOR_GE;}
"==" 					{return OPERATOR_EQ;}
"!=" 					{return OPERATOR_NE;}
"&&" 					{return OPERATOR_AND;}
"||" 					{return OPERATOR_OR;}
					
{ALPHAUNDER}{ALPHANUMUNDER}*		{ yylval.symbol = insertHash(SYMBOL_IDENTIFIER,yytext); 
					 return TK_IDENTIFIER;/* identificador, insere na hash e retorna o token */}
					
{NUM}+ 					{ yylval.symbol = insertHash(SYMBOL_LIT_INTEGER,yytext);return LIT_INTEGER;/* literais, insere na hash e retorna o token */}
{NUM}+.{NUM}+		 		{yylval.symbol = insertHash(SYMBOL_LIT_REAL,yytext); return LIT_REAL;}
\'.\'					{yylval.symbol = insertHash(SYMBOL_LIT_CHAR,yytext); return LIT_CHAR;}
\"([^\\\"]|\\.)*\"			{yylval.symbol = insertHash(SYMBOL_LIT_STRING,yytext); return LIT_STRING;}
					
"//".*"\n" 				{lineNumber++;/* comentario simples, com "\n" */}
					
"/*" 					BEGIN(MULTI_LINE_COMMENT);
					
"\n"					{lineNumber++;/* encontrou "\n", soma 1 ao numberLines */}

[ \t\r]+                               {/*ignore blankspace*/}
					
. 					{return TOKEN_ERROR;/* coletor de lixo */}	
			
<MULTI_LINE_COMMENT>"*/" 		BEGIN(INITIAL);
<MULTI_LINE_COMMENT>.
<MULTI_LINE_COMMENT>"\n" 		{lineNumber++;}

%%


int getLineNumber(void){
	return lineNumber;
}

int isRunning(void){
	return running;
}

void initMe(void){
	initHash();
}

int yywrap()
{
	running = 0;
	return 1;
}





