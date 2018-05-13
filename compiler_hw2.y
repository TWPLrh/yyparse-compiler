/*	Definition section */

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern int yylineno;
extern int yylex();

int Index = 0; 
char mID[20];
char mType[8];
int I_data;
float F_data;

/* Symbol table function - you can add new function if need. */
int lookup_symbol();
void create_symbol();
void insert_symbol();
void dump_symbol();
void yyerror(char const *s) { fprintf(stderr, "%s\n", s); }

typedef struct symbol_table
{
	int Index;
	char mID[20];
	char mType[8];
	int I_data;
	float F_data;
	struct symbol_table *next;

}symbol_table;

symbol_table *Table, *Head;

%}

/* Using union to define nonterminal and token type */
%union {
    int i_val;
    double f_val;
    char* string;
}

/* OTHERS PLEASE RETURN *YYTEXT */

/* Token without return NEED RETURN ! BUT NO TYPE*/
%token PRINT PRINTLN 
%token IF ELSE FOR
%token VAR NEWLINE
%token INT FLOAT VOID

/* Token with return, which need to sepcify type */
%token <i_val> I_CONST 
%token <f_val> F_CONST 
%token <string> STRING
%token <string> ID


/* Nonterminal with return, which need to sepcify type */
%type <f_val> stat 


/* Yacc will start at this nonterminal */
%start program

/* Grammar section */
%%

program 
    : stat program 
    | 
;

stat
    : declaration
    | compound_stat
    | expression_stat
    | print_func
;

compound_stat :
;

print_func 
	: PRINT '(' I_RETURN_ID ')' NEWLINE { printf("%s\n", mID); }
	| PRINTLN '(' I_RETURN_ID ')' NEWLINE { printf("%s\n\n", mID); }
;


declaration
    : VAR I_RETURN_ID type '=' initializer NEWLINE { create_symbol(); }
    | VAR I_RETURN_ID type NEWLINE { create_symbol(); }
;

type
    : INT 	{ strcpy(mType, "int"); }
    | FLOAT 	{ strcpy(mType, "float32"); }
    | VOID 	{ strcpy(mType, "void"); }
;

I_RETURN_ID
	: ID { strcpy(mID, $1); }
;

initializer  
	: ID
	| constant 
;

expression_stat 
	: IF_ELSE
	| FOR '{' expression_stat '}' 
	| CALC
	| 
;

CALC 	: CALC '+' Term 
	| CALC '-' Term
	| CALC '*' Term
	| CALC '/' Term
;

Term	: initializer
;

IF_ELSE : IF '{' expression_stat '}'
	| IF '{' expression_stat '}' ELSE '{' expression_stat '}'
;


constant
    : I_CONST { I_data = $1; }
    | F_CONST { F_data = $1; }
;

%%

/* C code section */
int main(int argc, char** argv)
{
    yylineno = 0;

    yyparse();

    return 0;
}

void create_symbol() 
{	
	if ( !Table )
	{
		fprintf(stdout, "Create symbol table\n");
		Table = malloc(sizeof(Table));
		Head = Table;
	}

	insert_symbol();
}

void insert_symbol() 
{
	// set every variable
	Index ++;
	Table -> Index = Index;

	strcpy(Table -> mID, mID);
	strcpy(Table -> mType, mType);

	switch(mType[0])
	{
	case 'v' : break;
	case 'f' : Table -> F_data = F_data; break;
	case 'i' : Table -> I_data = I_data; break;
	default : puts("Non-type"); break;
	}

	printf("Insert symbol: %s\n", Table -> mID);

	Table -> next = malloc(sizeof(symbol_table));

	// Table point to next;
	Table = Table -> next;
}

int lookup_symbol()
{

}

void dump_symbol()
{

}
