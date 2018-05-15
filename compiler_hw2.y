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
char mType[8];
int I_data;
float F_data;
char mString[87];

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
%token INCREMENT DECREMENT 
%token Other

/* Token with return, which need to sepcify type */
%token <i_val> I_CONST 
%token <f_val> F_CONST 
%token <string> STRING
%token <string> ID

/* Nonterminal with return, which need to sepcify type */
%type <f_val> stat 
%type <i_val> CALC
%type <i_val> INCDRC

/* Yacc will start at this nonterminal */
%start program

/* left */

%left '+' '-'
%left '*' '/'

/* Grammar section */
%%

program 
	: stat program 
	| 
;

stat
    : declaration { /* puts("0"); */ }
    | compound_stat { /* puts("1"); */ }
    | expression_stat { /* puts("2"); */ }
    | print_func { /* puts("3"); */ }
    | trap { /* puts (" trap from stat " ); */ }
;

compound_stat 
	:
;

print_func 
	: PRINT '(' stat ')' { printf("Print : %d\n", lookup_symbol(mID)->I_data); }
	| PRINTLN '(' I_STORE_ID ')' { printf("Println : %s\n", mID); }
	| PRINT '(' I_STORE_STRING ')' { printf("Print : %s\n", mString); }
	| PRINTLN '(' I_STORE_STRING ')' { printf("Println %s\n", mString); }
;


declaration
    	: VAR I_STORE_ID type '=' CALC { I_data = $5; create_symbol(); }
    	| VAR I_STORE_ID type { create_symbol(); }
;

type
    : INT 	{ strcpy(mType, "int"); }
    | FLOAT 	{ strcpy(mType, "float32"); }
    | VOID 	{ strcpy(mType, "void"); }
;

I_STORE_ID
	: ID { strcpy(mID, $1); } 
;

I_STORE_STRING
	: STRING { strcpy(mString, $1); }
;

expression_stat 
	: IF_ELSE
	| FOR '{' stat '}' 
	| CALC
	| I_STORE_ID '=' CALC
	{
		puts("Assign");
		if(!lookup_symbol(mID)) 
		{
			printf("%s --> Undeclared Variable\n", mID);
		}
		else
		{
			lookup_symbol(mID)->I_data = $3;
		}
	}
	| INCDRC { lookup_symbol(mID) -> I_data = $1; }
;

INCDRC	: INCDRC INCREMENT { $$ = $$ + 1;}
	| INCDRC DECREMENT { $$ = $$ - 1;}
	| I_STORE_ID
	{
		if(!lookup_symbol(mID))
		{
			printf("%s --> Undeclared Variable\n", mID);
		}

		else
		{
			$$ = lookup_symbol(mID)->I_data;
		}
	}
;


CALC 	: CALC '+' CALC { $$ = $1 + $3; puts("Add");}
	| CALC '-' CALC { $$ = $1 - $3; puts("Sub");}
	| CALC '*' CALC { $$ = $1 * $3; puts("Mul");}
	| CALC '/' CALC { $$ = $1 / $3; puts("Div");}
	| '(' CALC ')'	{ $$ = $2; }
	| I_STORE_ID
	{ 
		if(!lookup_symbol(mID))
		{ 
			printf("%s -->  Undeclared Varaible\n", mID); $$ = 1; 
		}
		else
		{
			$$ = lookup_symbol(mID)->I_data;
		}
	}
	| constant { $$ = I_data; }
;

IF_ELSE : IF '{' expression_stat '}'
	| IF '{' expression_stat '}' ELSE '{' expression_stat '}'
;


constant
    	: I_CONST { I_data = $1; }
   	| F_CONST { F_data = $1; }
;

trap 	: NEWLINE { /* puts("NEWLINE"); */ }
	| Other { /* puts("Other"); */ }
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
		
                fprintf(stdout, "%s\t%s\t%d\n", temp->mID, temp->mType, temp->I_data);
		temp = temp -> next;
        }
	
}
