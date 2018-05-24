/*	Definition section */

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
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
int printErrflag = 0;

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
float Func_Assign(char, float);
float IncDecFunc(char);
void printfunc(float);
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
%token Add_Assign Sub_Assign Mul_Assign Div_Assign Mod_Assign
%token GRE LSE EQU NEQ
%token AND OR
%token Other

/* Token with return, which need to sepcify type */
%token <i_val> I_CONST 
%token <f_val> F_CONST 
%token <string> STRING
%token <string> ID

/* Nonterminal with return, which need to sepcify type */
%type <f_val> CALC
%type <f_val> expr
%type <f_val> IncDecStmt
%type <f_val> STORE_ID

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

dcl	: VAR lockedID type '=' CALC	{ create_symbol(); }
	| VAR lockedID type		{ create_symbol(); }
;

comp	:
;

expr	
	:	CALC						
	|	lockedID '=' CALC 			{puts("ASSIGN"); $$ = Func_Assign('=', $3);}
	|	lockedID Add_Assign CALC	{puts("Add Assign"); $$ = Func_Assign('+', $3);}
	|	lockedID Sub_Assign CALC	{puts("Sub Assign"); $$ = Func_Assign('-', $3);}
	|	lockedID Mul_Assign CALC	{puts("Mul Assign"); $$ = Func_Assign('*', $3);}
	|	lockedID Div_Assign CALC	{puts("Div Assign"); $$ = Func_Assign('/', $3);}
	|	lockedID Mod_Assign CALC	{puts("Mod Assign"); $$ = Func_Assign('%', $3);}
	|	IncDecStmt
;

print_func 
	: PRINT '(' expr ')' 	{ if(printErrflag == 1) {  printErrflag = 0; } else printfunc($3); }
	| PRINTLN '(' expr ')' 	{ if(printErrflag == 1) {  printErrflag = 0; } else printfunc($3); }
	| PRINT '(' STORE_STR ')' 	{ printf("Print : %s\n", mStr); }
	| PRINTLN '(' STORE_STR ')'	{ printf("Println %s\n", mStr); }
;

type
	: INT 		{ strcpy(mType, "int"); }
	| FLOAT 	{ strcpy(mType, "float32"); }
	| VOID 		{ strcpy(mType, "void"); }
;

IncDecStmt
	:	INCREMENT IncDecStmt {puts("preInc"); $$ = IncDecFunc('+');}
	|	DECREMENT IncDecStmt {puts("preDec"); $$ = IncDecFunc('-');}
	|	IncDecStmt INCREMENT {puts("postInc");$$ = IncDecFunc('+') - 1;}
	|	IncDecStmt DECREMENT {puts("postDec");$$ = IncDecFunc('-') + 1;}
	|	STORE_ID  { $$ = $1;}
;

CALC	
	: CALC '+' CALC	{ $$ = $1 + $3; puts("Add");}
	| CALC '-' CALC	{ $$ = $1 - $3; puts("Sub");}
	| CALC '*' CALC	{ $$ = $1 * $3; puts("Mul");}
	| CALC '/' CALC	{ if($3 == 0) { printErrflag = 1; printf(ANSI_COLOR_RED   "<ERROR> The divisor can’t be 0 (line %d)\n"    ANSI_COLOR_RESET, yylineno + 1);} else { puts("Div"); $$ = $$ / $3;}}
	| CALC '%' CALC { $$ = (int)$1 % (int)$3; puts("Mod");}
	| '(' CALC ')'	{ $$ = $2; }
	| STORE_ID  { $$ = $1 ;}
	| STORE_INT { $$ = (float)I_data; }
	| STORE_FLT { $$ = F_data; }
	| CALC '>' CALC { $$ = $1 > $3; puts("Greater");}
	| CALC '<' CALC	{ $$ = $1 < $3; puts("Lesser");}
	| CALC EQU CALC	{ $$ = $1 == $3; puts("Equal");}
	| CALC GRE CALC	{ $$ = $1 >= $3; puts("Greater or Equal");}
	| CALC LSE CALC	{ $$ = $1 <= $3; puts("Lesser or Equal");}
	| CALC NEQ CALC	{ $$ = $1 != $3; puts("Not Equal");}
;

lockedID 
	: ID		{ char *p = strtok($1, "+-*/()=% \t"); strcpy(lockedID, p);};

STORE_ID
	: ID		
	{ 
		char *p = strtok($1, "+-*/()=%>< \t");
		strcpy(mID, p); 

		gbTmp = lookup_symbol(mID);

		if(!gbTmp)
		{
			printf(ANSI_COLOR_RED   "<ERROR> can't find variable %s (line %d)\n"    ANSI_COLOR_RESET, mID, yylineno);
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
;

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
	if(lookup_symbol(lockedID))
	{
		printf(ANSI_COLOR_RED   "<ERROR> re-declaration for variable %s (line %d)\n"    ANSI_COLOR_RESET, mID, yylineno);
		return;
	}

	// set every variable
	Index ++;
	Table -> Index = Index;
	strcpy(Table -> mID, lockedID);
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
	if (!Head) 
	{ 
		return NULL;
	}

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

float Func_Assign(char m, float flt)
{
	gbTmp = lookup_symbol(lockedID);

	if(!gbTmp)
	{   
		printf(ANSI_COLOR_RED   "<ERROR> can't find variable %s (line %d)\n"    ANSI_COLOR_RESET, lockedID, yylineno);
	}

	else
	{
		if(gbTmp->mType[0] == 'i')
		{
			switch(m)
			{
				case '=' : gbTmp->I_data = (int)flt; break;
				case '+' : gbTmp->I_data += (int)flt; break;
				case '-' : gbTmp->I_data -= (int)flt; break;
				case '*' : gbTmp->I_data *= (int)flt; break;
				case '/' : gbTmp->I_data /= (int)flt; break;
				case '%' : gbTmp->I_data %= (int)flt; break;
			}
			return (float)gbTmp->I_data;
		}
		else if(gbTmp->mType[0] == 'f')
		{
			switch(m)
			{
				case '=' : gbTmp->F_data = flt; break;
				case '+' : gbTmp->F_data += flt; break;
				case '-' : gbTmp->F_data -= flt; break;
				case '*' : gbTmp->F_data *= flt; break;
				case '/' : gbTmp->F_data /= flt; break;
				case '%' : printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno+1); break;
			}
			return gbTmp->F_data;
		}
	}
}

float IncDecFunc(char m)
{
	gbTmp = lookup_symbol(mID);
	
	if(gbTmp)
	{   
		if(gbTmp->mType[0] == 'i')
		{
			switch(m)
			{
				case '+': gbTmp -> I_data++; break; 
				case '-': gbTmp -> I_data--; break;
			}
			return (float)gbTmp->I_data;
		}
		else if(gbTmp->mType[0] == 'f')
		{
			switch(m)
			{
				case '+': gbTmp -> F_data++; break;
				case '-': gbTmp -> F_data--; break;
			}
			return gbTmp->F_data;
		}
	}
}

void printfunc(float flt)
{
	printf("%g\n", flt);
}
