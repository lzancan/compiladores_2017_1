include "tokens.h"
int lineNumber = 0;

%%
byte					return KW_BYTE;
short 					return KW_SHORT;
long 					return KW_LONG;
float 					return KW_FLOAT;
double 					return KW_DOUBLE;
when 					return KW_WHEN;
then 					return KW_THEN;
else 					return KW_ELSE;
while 					return KW_WHILE;
for 					return KW_FOR;
read 					return KW_READ;
return 					return KW_RETURN;
print 					return KW_PRINT;
"<=" 					return OPERATOR_LE;
">=" 					return OPERATOR_GE;
"==" 					return OPERATOR_EQ;
"!=" 					return OPERATOR_NE;
"&&" 					return OPERATOR_AND;
"||" 					return OPERATOR_OR;
[a-zA-Z_][a-zA-Z0-9_]* 			return TK_IDENTIFIER;
[0-9]+ 					return LIT_INTEGER;
([0-9]+"."[0-9]+)		 	return LIT_REAL;
"'"."'" 				return LIT_CHAR;
"'".*"'" 				return LIT_STRING;
"\n"					addLineNumber();
[,;:()"[""]"{}+-*"/"<>=!&$#]		yytext[0]
//					//ignora até o \n
/*					//ignora até achar o */
. 					return TOKEN_ERROR;
%%
int getLineNumber(void)
{
	return numberLines;
}
void addLineNumber(void)
{
	numberLines++;
}



