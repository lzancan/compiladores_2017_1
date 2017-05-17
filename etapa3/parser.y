%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "hash.h"
	#include "astree.h"
	
	

%}

%union{ 
	HASH_NODE* symbol; 
	ASTREE* astree; 
      }

%token KW_TO
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

%token <symbol> TK_IDENTIFIER 
%token <symbol> LIT_INTEGER   
%token <symbol> LIT_REAL      
%token <symbol> LIT_CHAR      
%token <symbol> LIT_STRING    

%token TOKEN_ERROR   

%type <astree> PROGRAMA
%type <astree> DECLARACAO
%type <astree> VARIAVEL_GLOBAL
%type <astree> VAR_GLOBAL_INIT_VEC
%type <astree> VALOR
%type <astree> VALOR_INICIALIZACAO_VETOR
%type <astree> TIPO
%type <astree> FUNCOES
%type <astree> CABECALHO
%type <astree> LISTA_PARAMETROS
%type <astree> MAIS_PARAMETROS
%type <astree> CORPO
%type <astree> BLOCO_COMANDOS
%type <astree> LISTA_COMANDOS
%type <astree> COMANDO
%type <astree> ATRIBUICAO
%type <astree> READ
%type <astree> PRINT
%type <astree> LISTA_ELEMENTOS_PRINT
%type <astree> ELEMENTO_PRINT
%type <astree> RETURN
%type <astree> EXPRESSAO
%type <astree> LISTA_FUNCAO_PARAMETROS
%type <astree> CONTROLE_FLUXO
%type <astree> WHEN_THEN
%type <astree> WHEN_THEN_ELSE
%type <astree> WHILE
%type <astree> FOR


%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left OPERATOR_AND OPERATOR_OR
%left '+' '-'
%left '*' '/'
%left '='
%left '[' ']'
%left '(' ')'




%%
	
	P: PROGRAMA {astreePrint($1);}
	;
	PROGRAMA: DECLARACAO PROGRAMA 
		   | /*vazio*/ 
	;
	DECLARACAO: FUNCOES {$$ = astreeCreate(ASTREE_FUNCAO, NULL, $1, 0, 0, 0);}
		    | VARIAVEL_GLOBAL ';' {$$ = astreeCreate(ASTREE_VAR_GLOBAL, NULL, $1, 0, 0, 0);}
	;
	VARIAVEL_GLOBAL: TK_IDENTIFIER ':' TIPO VAR_GLOBAL_INIT_VEC {$$ = astreeCreate(ASTREE_LITERAL, $1, 0, 0, 0, 0);}
	;
	VAR_GLOBAL_INIT_VEC: VALOR 
			     | '[' LIT_INTEGER ']' VALOR_INICIALIZACAO_VETOR
	;
	VALOR: 	LIT_INTEGER { $$ = astreeCreate(ASTREE_LITERAL, $1, 0, 0, 0, 0);} |
		LIT_REAL { $$ = astreeCreate(ASTREE_LITERAL, $1, 0, 0, 0, 0);} |
		LIT_CHAR { $$ = astreeCreate(ASTREE_LITERAL, $1, 0, 0, 0, 0);}
	;
	VALOR_INICIALIZACAO_VETOR: VALOR VALOR_INICIALIZACAO_VETOR 
				   | /*vazio*/
	;
	TIPO: KW_BYTE  | 
	      KW_SHORT |    
	      KW_LONG  |  
 	      KW_FLOAT |   
	      KW_DOUBLE
	; 
	FUNCOES: CABECALHO CORPO
	;
	CABECALHO: TIPO TK_IDENTIFIER '(' LISTA_PARAMETROS ')' 
	;
	LISTA_PARAMETROS: TIPO TK_IDENTIFIER MAIS_PARAMETROS 
			| /*vazio*/
	;
	MAIS_PARAMETROS: ',' TIPO TK_IDENTIFIER MAIS_PARAMETROS  
			| /*vazio*/ 
	;
	CORPO: COMANDO ';'
	;
	BLOCO_COMANDOS: '{'LISTA_COMANDOS'}' {$$ = astreeCreate(ASTREE_BLOCO_COMANDOS, NULL, $2, 0, 0, 0);}
	;
	LISTA_COMANDOS: COMANDO';' LISTA_COMANDOS {$$ = astreeCreate(ASTREE_LISTA_COMANDOS, NULL, $1, $3, 0, 0);}
			| /*vazio*/ 
	;
	COMANDO: ATRIBUICAO|
		 CONTROLE_FLUXO|
		 READ|
		 PRINT|
		 RETURN|
		 BLOCO_COMANDOS|
		 /*vazio*/ 
	;
	ATRIBUICAO: TK_IDENTIFIER '='EXPRESSAO {$$ = astreeCreate(ASTREE_ATRIBUICAO, $1, $3, 0, 0, 0);}
		  | TK_IDENTIFIER '#'EXPRESSAO'='EXPRESSAO {$$ = astreeCreate(ASTREE_ATRIBUICAO, $1, $3, $5, 0, 0);}
	;
	READ: KW_READ TK_IDENTIFIER 
	;
	PRINT: KW_PRINT LISTA_ELEMENTOS_PRINT
	;
	LISTA_ELEMENTOS_PRINT: ELEMENTO_PRINT LISTA_ELEMENTOS_PRINT 
				| ELEMENTO_PRINT 
	;
	ELEMENTO_PRINT: LIT_STRING
			| EXPRESSAO
	;
	RETURN: KW_RETURN EXPRESSAO
	;
	EXPRESSAO: TK_IDENTIFIER { $$ = astreeCreate(ASTREE_LITERAL, $1, 0, 0, 0, 0);} |
		   TK_IDENTIFIER '[' EXPRESSAO ']' { $$ = astreeCreate(ASTREE_EXPRESSAO, $1, $3, 0, 0, 0);} |
		   TK_IDENTIFIER '(' LISTA_FUNCAO_PARAMETROS ')' { $$ = astreeCreate(ASTREE_EXPRESSAO, $1, $3, 0, 0, 0);}  |
		   '-' EXPRESSAO { $$ = astreeCreate(ASTREE_EXPRESSAO, NULL, $2, 0, 0, 0);} |
		   LIT_INTEGER { $$ = astreeCreate(ASTREE_LITERAL, $1, 0, 0, 0, 0); fprintf (stderr,"achei um lit");} |
		   LIT_REAL { $$ = astreeCreate(ASTREE_LITERAL, $1, 0, 0, 0, 0);} |
		   LIT_CHAR { $$ = astreeCreate(ASTREE_LITERAL, $1, 0, 0, 0, 0);}|
		   '('EXPRESSAO')' { $$ = astreeCreate(ASTREE_EXPRESSAO, NULL, $2, 0, 0, 0);} |
		   '[' EXPRESSAO ']'  { $$ = astreeCreate(ASTREE_EXPRESSAO, NULL, $2, 0, 0, 0);} |
		   EXPRESSAO '+' EXPRESSAO  { $$ = astreeCreate(ASTREE_ADD, NULL, $1, $3, 0, 0);} | 
		   EXPRESSAO '-' EXPRESSAO  { $$ = astreeCreate(ASTREE_SUB, NULL, $1, $3, 0, 0);} |
		   EXPRESSAO '*' EXPRESSAO  { $$ = astreeCreate(ASTREE_MUL, NULL, $1, $3, 0, 0);} |
		   EXPRESSAO '/' EXPRESSAO  { $$ = astreeCreate(ASTREE_DIV, NULL, $1, $3, 0, 0);} |
	           EXPRESSAO '>' EXPRESSAO  { $$ = astreeCreate(ASTREE_LESS_THAN, NULL, $1, $3, 0, 0);} |
		   EXPRESSAO '<' EXPRESSAO  { $$ = astreeCreate(ASTREE_GREATER_THAN, NULL, $1, $3, 0, 0);} | 
		   EXPRESSAO OPERATOR_LE EXPRESSAO  { $$ = astreeCreate(ASTREE_LE, NULL, $1, $3, 0, 0);} | 
		   EXPRESSAO OPERATOR_GE EXPRESSAO  { $$ = astreeCreate(ASTREE_GE, NULL, $1, $3, 0, 0);} |
		   EXPRESSAO OPERATOR_EQ EXPRESSAO  { $$ = astreeCreate(ASTREE_EQ, NULL, $1, $3, 0, 0);} | 
		   EXPRESSAO OPERATOR_NE EXPRESSAO  { $$ = astreeCreate(ASTREE_NE, NULL, $1, $3, 0, 0);} | 
		   EXPRESSAO OPERATOR_AND EXPRESSAO { $$ = astreeCreate(ASTREE_AND, NULL, $1, $3, 0, 0);} |
		   EXPRESSAO OPERATOR_OR EXPRESSAO  { $$ = astreeCreate(ASTREE_OR, NULL, $1, $3, 0, 0);} | 
		   '!'EXPRESSAO { $$ = astreeCreate(ASTREE_EXPRESSAO, NULL, $2, 0, 0, 0);} 
	;		  

	LISTA_FUNCAO_PARAMETROS: EXPRESSAO ',' LISTA_FUNCAO_PARAMETROS
			        | EXPRESSAO 
				|/*VAZIO*/
	;
	CONTROLE_FLUXO: WHEN_THEN 
			| WHEN_THEN_ELSE 
			| FOR 
			| WHILE
	;
	WHEN_THEN: KW_WHEN '('EXPRESSAO')' KW_THEN COMANDO 
	;
	WHEN_THEN_ELSE: KW_WHEN '(' EXPRESSAO ')' KW_THEN COMANDO KW_ELSE COMANDO 
	;
	WHILE: KW_WHILE '(' EXPRESSAO ')' COMANDO
	;
	FOR: KW_FOR '(' TK_IDENTIFIER '=' EXPRESSAO KW_TO EXPRESSAO ')' COMANDO
	;
	

%%



int yyerror(char *value){
  fprintf(stderr, "Erro: %s ,na linha: %d\n",value,getLineNumber());
  exit(3);
}




