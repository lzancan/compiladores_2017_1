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
	
	PROGRAMA: DECLARACAO PROGRAMA | /*vazio*/
	;
	DECLARACAO: FUNCOES | VARIAVEL_GLOBAL ';'
	;
	VARIAVEL_GLOBAL: TK_IDENTIFIER ':' TIPO VAR_GLOBAL_INIT_VEC
	;
	VAR_GLOBAL_INIT_VEC: VALOR_INICIALIZACAO | '[' LIT_INTEGER ']' VALOR_INICIALIZACAO_VETOR
	;
	VALOR_INICIALIZACAO: LIT_INTEGER  |
			     LIT_REAL |
			     LIT_CHAR 
	;
	VALOR_INICIALIZACAO_VETOR: VALOR_INICIALIZACAO VALOR_INICIALIZACAO_VETOR | /*vazio*/
	;
	TIPO: KW_BYTE  | 
	      KW_SHORT |    
	      KW_LONG  |  
 	      KW_FLOAT |   
	      KW_DOUBLE
	; 
	FUNCOES: CABECALHO CORPO
	;
	CABECALHO: TIPO TK_IDENTIFIER '(' LISTA ')'
	;
	LISTA:
	;
	CORPO:
	;
	
%%



int yyerror(char *value){
  fprintf(stderr, "Erro: %s ,na linha: %d\n",value,getLineNumber());
  exit(3);
}




