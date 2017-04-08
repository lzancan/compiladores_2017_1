%{

	#include "tokens.h"
	#include "hash.h"

	// esboço das funções
	int getLineNumber(void);
	void initMe(void);
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
					{/* palavras reservadas */}
byte					{return KW_BYTE;}
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
					{/* codigo ascii */}
[,;:()\[\]\{}+\-*/<>=!&$#]		{return yytext[0];}
					{/* operadores compostos */}
"<=" 					{return OPERATOR_LE;}
">=" 					{return OPERATOR_GE;}
"==" 					{return OPERATOR_EQ;}
"!=" 					{return OPERATOR_NE;}
"&&" 					{return OPERATOR_AND;}
"||" 					{return OPERATOR_OR;}
					{/* identificador, insere na hash e retorna o token */}
{ALPHAUNDER}{ALPHANUMUNDER}*		{insertHash(yytext); return TK_IDENTIFIER;}
					{/* literais, insere na hash e retorna o token */}
{NUM}+ 					{insertHash(yytext);return LIT_INTEGER;}
{NUM}+.{NUM}+		 		{insertHash(yytext);return LIT_REAL;}
\'.\'					{insertHash(yytext);return LIT_CHAR;}
\"([^\\\"]|\\.)*\"			{insertHash(yytext);return LIT_STRING;}
					{/* comentario simples, com "\n" */}
"//".*"\n" 				{addLineNumber();}
					{/* término de comentario de multiplas linhas */}
"/*" 					BEGIN(MULTI_LINE_COMMENT);
					{/* encontrou "\n", soma 1 ao numberLines */}
"\n"					{addLineNumber();}
					{/* coletor de lixo */}
. 					{return TOKEN_ERROR;}	
					{/* término de comentario de multiplas linhas */}
<MULTI_LINE_COMMENT>"*/" 		BEGIN(INITIAL);
<MULTI_LINE_COMMENT>.
<MULTI_LINE_COMMENT>"\n" 		{addLineNumber();}

%%


int getLineNumber(void)
{
	return numberLines;
}

void addLineNumber(void)
{
	numberLines++;
}

int isRunning(void){
	return running;
}

void initMe(void){
	startHash();
}

int yywrap()
{
	running = 0;
	return 1;
}



