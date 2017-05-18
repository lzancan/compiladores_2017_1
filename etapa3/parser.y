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

%type <astree> P
%type <astree> DECLARACOES
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
	
	P: PROGRAMA{	 astreePrint(0, $1);
			 uncompile($1); 
	}
	;
	PROGRAMA: DECLARACOES { $$ = astreeCreate(ASTREE_PROGRAMA, NULL, $1, 0, 0, 0);}
	;
	DECLARACOES: DECLARACAO DECLARACOES {$$ = astreeCreate(ASTREE_DECLARACAO, NULL, $1, $2, 0, 0);}
		   | /*vazio*/ { $$ = 0; }
	;
	DECLARACAO: FUNCOES 
		    | VARIAVEL_GLOBAL ';' 
	;
	VARIAVEL_GLOBAL: TK_IDENTIFIER ':' TIPO VAR_GLOBAL_INIT_VEC { $$ = astreeCreate(ASTREE_VAR_GLOBAL, $1, $3, $4, 0, 0);}
	;
	VAR_GLOBAL_INIT_VEC: VALOR 
			     | '[' LIT_INTEGER ']' VALOR_INICIALIZACAO_VETOR { $$ = astreeCreate(ASTREE_VAR_GLOBAL_INIT_VEC, $2, $4, 0, 0, 0);}
	;
	VALOR: 	LIT_INTEGER { $$ = astreeCreate(ASTREE_LITERAL, $1, 0, 0, 0, 0);} |
		LIT_REAL { $$ = astreeCreate(ASTREE_LITERAL, $1, 0, 0, 0, 0);} |
		LIT_CHAR { $$ = astreeCreate(ASTREE_LITERAL, $1, 0, 0, 0, 0);}
	;
	VALOR_INICIALIZACAO_VETOR: VALOR VALOR_INICIALIZACAO_VETOR 
				   | /*vazio*/ { $$ = 0; }
	;
	TIPO: KW_BYTE  { $$ = astreeCreate(ASTREE_BYTE_TYPE, 0, 0, 0, 0, 0);}| 
	      KW_SHORT { $$ = astreeCreate(ASTREE_SHORT_TYPE, 0, 0, 0, 0, 0); }|    
	      KW_LONG  { $$ = astreeCreate(ASTREE_LONG_TYPE, 0, 0, 0, 0, 0);}|  
 	      KW_FLOAT { $$ = astreeCreate(ASTREE_FLOAT_TYPE, 0, 0, 0, 0, 0); }|   
	      KW_DOUBLE{ $$ = astreeCreate(ASTREE_DOUBLE_TYPE, 0, 0, 0, 0, 0); }
	; 
	FUNCOES: CABECALHO CORPO {$$ = astreeCreate(ASTREE_FUNCAO, NULL, $1, $2, 0, 0);}
	;
	CABECALHO: TIPO TK_IDENTIFIER '(' LISTA_PARAMETROS ')' {$$ = astreeCreate(ASTREE_FUNC_CABECALHO, $2, $1, $4, 0, 0);}
	;
	LISTA_PARAMETROS: TIPO TK_IDENTIFIER MAIS_PARAMETROS {$$ = astreeCreate(ASTREE_LISTA_PARAMETROS, $2, $1, $3, 0, 0);}
			| /*vazio*/ {$$ = 0;}
	;
	MAIS_PARAMETROS: ',' TIPO TK_IDENTIFIER MAIS_PARAMETROS  {$$ = astreeCreate(ASTREE_MAIS_PARAMETROS, $3, $2, $4, 0, 0);}
			| /*vazio*/ {$$ = 0;}
	;
	CORPO: COMANDO ';'
	;
	BLOCO_COMANDOS: '{'LISTA_COMANDOS'}' {$$ = astreeCreate(ASTREE_BLOCO_COMANDOS, NULL, $2, 0, 0, 0);}
	;
	LISTA_COMANDOS: COMANDO';' LISTA_COMANDOS {$$ = astreeCreate(ASTREE_LISTA_COMANDOS, NULL, $1, $3, 0, 0);}
			| /*vazio*/ {$$ = 0;}
	;
	COMANDO: ATRIBUICAO|
		 CONTROLE_FLUXO|
		 READ|
		 PRINT|
		 RETURN|
		 BLOCO_COMANDOS|
		 /*vazio*/ {$$ = 0;}
	;
	ATRIBUICAO: TK_IDENTIFIER '='EXPRESSAO {$$ = astreeCreate(ASTREE_ATRIBUICAO, $1, $3, 0, 0, 0);}
		  | TK_IDENTIFIER '#'EXPRESSAO'='EXPRESSAO {$$ = astreeCreate(ASTREE_ATRIBUICAO_VETOR, $1, $3, $5, 0, 0);}
	;
	READ: KW_READ TK_IDENTIFIER {$$ = astreeCreate(ASTREE_READ, $2, 0, 0, 0, 0);}
	;
	PRINT: KW_PRINT LISTA_ELEMENTOS_PRINT {$$ = astreeCreate(ASTREE_PRINT, NULL, $2, 0, 0, 0);}
	;
	LISTA_ELEMENTOS_PRINT: ELEMENTO_PRINT LISTA_ELEMENTOS_PRINT 
				| ELEMENTO_PRINT 
	;
	ELEMENTO_PRINT: LIT_STRING { $$ = astreeCreate(ASTREE_LITERAL, $1, 0, 0, 0, 0);}
			| EXPRESSAO
	;
	RETURN: KW_RETURN EXPRESSAO { $$ = astreeCreate(ASTREE_RETURN, NULL, $2, 0, 0, 0);}
	;
	EXPRESSAO: TK_IDENTIFIER { $$ = astreeCreate(ASTREE_IDENTIFIER, $1, 0, 0, 0, 0);} |
		   TK_IDENTIFIER EXPRESSAO { $$ = astreeCreate(ASTREE_EXPRESSAO_VETOR, $1, $2, 0, 0, 0);} | 
		   TK_IDENTIFIER '(' LISTA_FUNCAO_PARAMETROS ')' { $$ = astreeCreate(ASTREE_EXPRESSAO_FUNCAO, $1, $3, 0, 0, 0);}  |
		   '-' EXPRESSAO { $$ = astreeCreate(ASTREE_NEGATIVO, NULL, $2, 0, 0, 0);} |
		   LIT_INTEGER { $$ = astreeCreate(ASTREE_LITERAL, $1, 0, 0, 0, 0);} |
		   LIT_REAL { $$ = astreeCreate(ASTREE_LITERAL, $1, 0, 0, 0, 0);} |
		   LIT_CHAR { $$ = astreeCreate(ASTREE_LITERAL, $1, 0, 0, 0, 0);}|
		   '('EXPRESSAO')' { $$ = astreeCreate(ASTREE_PARENTESES, NULL, $2, 0, 0, 0);} |
		   '[' EXPRESSAO ']'  { $$ = astreeCreate(ASTREE_COLCHETES, NULL, $2, 0, 0, 0);} |
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
		   '!'EXPRESSAO { $$ = astreeCreate(ASTREE_NEGADO, NULL, $2, 0, 0, 0);} 
	;		  

	LISTA_FUNCAO_PARAMETROS: EXPRESSAO ',' LISTA_FUNCAO_PARAMETROS { $$ = astreeCreate(ASTREE_LISTA_FUNC_PARAMETROS, NULL, $1, $3, 0, 0);}
			        | EXPRESSAO 
				|/*VAZIO*/ {$$ = 0;}
	;
	CONTROLE_FLUXO: WHEN_THEN 
			| WHEN_THEN_ELSE 
			| FOR 
			| WHILE
	;
	WHEN_THEN: KW_WHEN '('EXPRESSAO')' KW_THEN COMANDO  { $$ = astreeCreate(ASTREE_WHEN_THEN, NULL, $3, $6, 0, 0);}
	;
	WHEN_THEN_ELSE: KW_WHEN '(' EXPRESSAO ')' KW_THEN COMANDO KW_ELSE COMANDO { $$ = astreeCreate(ASTREE_WHEN_THEN_ELSE, NULL, $3, $6, $8, 0);}
	;
	WHILE: KW_WHILE '(' EXPRESSAO ')' COMANDO { $$ = astreeCreate(ASTREE_WHILE, NULL, $3, $5, 0, 0);}
	;
	FOR: KW_FOR '(' TK_IDENTIFIER '=' EXPRESSAO KW_TO EXPRESSAO ')' COMANDO { $$ = astreeCreate(ASTREE_FOR, $3, $5, $7, $9, 0);}
	;
	

%%

int yyerror(char *value){
  fprintf(stderr, "Erro: %s ,na linha: %d\n",value,getLineNumber());
  exit(3);
}




