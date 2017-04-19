%{
	#include <stdio.h>
	#include <stdlib.h>

	int getLineNumber(void);
	int yyerror(char *value);
	int yylex(void);
%}



%token KW_BYTE   
%token KW_SHORT     
%token KW_LONG     
%token KW_FLOAT     
%token KW_DOUBLE     
%token KW_WHEN       
%token KW_THEN       
%token KW_ELSE       
%token KW_WHILE      
%token KW_FOR        
%token KW_READ       
%token KW_RETURN     
%token KW_PRINT      

%token OPERATOR_LE   
%token OPERATOR_GE   
%token OPERATOR_EQ   
%token OPERATOR_NE   
%token OPERATOR_AND  
%token OPERATOR_OR   

%token TK_IDENTIFIER 
%token LIT_INTEGER   
%token LIT_REAL      
%token LIT_CHAR      
%token LIT_STRING    

%token TOKEN_ERROR   


%%
	
	PROGRAMA: LIT_INTEGER ;
%%



int yyerror(char *value){
  fprintf(stderr, "Erro: %s ,line: %d\n",value,getLineNumber());
  exit(3);
}




