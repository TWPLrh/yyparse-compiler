/*	Definition section */

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern int yylineno;
extern int yylex();
extern FILE *yyin;

int Index = 0; 
char mID[20];
char lockedID[20];
char mType[8];
int I_data;
float F_data;
char mStr[87];
int isthisaID = 0;

typedef struct symbol_table
{
        int Index;
        char mID[20];
        char mType[8];
        int I_data;
        float F_data;
        struct symbol_table *next;

}symbol_table;

/* Symbol table function - you can add new function if need. */
symbol_table *lookup_symbol(char const *);
void create_symbol();
void insert_symbol();
void dump_symbol();
void yyerror(char const *s) { fprintf(stderr, "Error : %s\n", s); }

symbol_table *Table, *Head, *gbTmp;

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
%token INCREMENT DECREMENT 
%token GRE LSE EQU NEQ;
%token Other

/* Token with return, which need to sepcify type */
%token <i_val> I_CONST 
%token <f_val> F_CONST 
%token <string> STRING
%token <string> ID

/* Nonterminal with return, which need to sepcify type */
%type <f_val> CALC
%type <f_val> expr

/* Yacc will start at this nonterminal */
%start program

/* left */

%left '+' '-'
%left '*' '/'

/* Grammar section */
%%

program 
	: stmt program 
	| 
;

stmt
	: dcl 		
	| comp 		
	| expr
	| print_func
	| trap 		
;

dcl	: VAR STORE_ID type '=' CALC	{ create_symbol(); }
	| VAR STORE_ID type		{ create_symbol(); }
;

comp	:
;

expr	
	:	CALC
	|	lockedID '=' CALC 
	{
		puts("ASSIGN");

		gbTmp = lookup_symbol(lockedID);
		if(!gbTmp)
			printf("Undeclared Variable --> %s\n", lockedID);
		else
			if(gbTmp->mType[0] == 'i')
				gbTmp->I_data = (int)$3;
			else if(gbTmp->mType[0] == 'f')
				gbTmp->F_data = $3;
		$$ = $3;
	}
;

print_func 
	: PRINT '(' expr ')' 	{ printf("Print : %g\n", $3); }
	| PRINTLN '(' expr ')' 	{ printf("Println : %g\n", $3); }
	| PRINT '(' STORE_STR ')' 	{ printf("Print : %s\n", mStr); }
	| PRINTLN '(' STORE_STR ')'	{ printf("Println %s\n", mStr); }
;

type
	: INT 		{ strcpy(mType, "int"); }
	| FLOAT 	{ strcpy(mType, "float32"); }
	| VOID 		{ strcpy(mType, "void"); }
;

CALC	
	: CALC '+' CALC	{ $$ = $1 + $3; puts("Add");}
	| CALC '-' CALC	{ $$ = $1 - $3; puts("Sub");}
	| CALC '*' CALC	{ $$ = $1 * $3; puts("Mul");}
	| CALC '/' CALC	{ $$ = $1 / $3; puts("Div");}
	| '(' CALC ')'	{ $$ = $2; }
	| CALC INCREMENT { lookup_symbol(mID)->I_data++; $$ = $1 + 1; puts("Incr");}
	| CALC DECREMENT { lookup_symbol(mID)->I_data--; $$ = $1 - 1; puts("Decr");}
	| STORE_ID  
	{
		gbTmp = lookup_symbol(mID);
		
		if(!gbTmp) 
		{
			printf("Undeclared Variable --> %s\n", mID);
		}
		else
		{
			if(gbTmp->mType[0] == 'i')
			{
				$$ = (float)gbTmp->I_data;
			}
			else if(gbTmp->mType[0] == 'f')
			{
				$$ = gbTmp->F_data;
			}
		}
	}
	| STORE_INT { $$ = (float)I_data; }
	| STORE_FLT { $$ = F_data; }
;

lockedID 
	: ID		{ char *p = strtok($1, "+-*/()= \t"); strcpy(lockedID, p);};

STORE_ID
	: ID		{ char *p = strtok($1, "+-*/()= \t"); strcpy(mID, p);/*strcpy(mID, $1);*/};

STORE_STR
	: STRING	{ strcpy(mStr, $1); };

STORE_INT
	: I_CONST	{ I_data = $1; };

STORE_FLT
	: F_CONST	{ F_data = $1; };

trap 	: NEWLINE 	{ /* puts("NEWLINE"); */ }
	| Other 	{ /* puts("Other"); */ }
;

%%

/* C code section */
int main(int argc, char** argv)
{
	yyin = fopen(argv[1], "r");	

	yylineno = 0;
	
	yyparse();
	
	printf("\nTotal line : %d\n", yylineno);

	printf("\nThe symbol table:\n");
	dump_symbol();
	
	return 0;
}

void create_symbol() 
{	
	if ( !Table )
	{
		fprintf(stdout, "Create symbol table\n");
		Table = malloc(sizeof(symbol_table));
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

symbol_table *lookup_symbol(char const *Look_ID)
{
	if (!Head) return NULL;

	symbol_table *temp = Head;

	while(temp -> next != NULL)
	{
		if(strcmp(Look_ID, temp->mID) == 0)
		{
			return temp;
		}
		temp = temp -> next;
	}

	return NULL;
}

void dump_symbol()
{
	if ( !Head ) return;

        symbol_table *temp = Head;

	puts("\nID\tType\tData");

        while(temp -> next != NULL)
        {
			if(temp->mType[0] == 'i')
			{
                fprintf(stdout, "%s\t%s\t%d\n", temp->mID, temp->mType, temp->I_data);
				fflush(stdout);
			}
			else if(temp -> mType[0] == 'f')
			{
				fprintf(stdout, "%s\t%s\t%g\n", temp->mID, temp->mType, temp->F_data);
				fflush(stdout);
			}
			temp = temp -> next;
        }	
}
