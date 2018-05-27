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

char mID[20];
char lockedID[20];
char mType[8];
int I_data;
float F_data;
char mStr[87];
int printErrflag = 0;
int initflag = 0;
int isflt = 0;
int declaredtwice = 0;

int ScopeDepth = 0;
int MaxScopeDepth = 0;

int l = 0;
int r = 0;

typedef struct symbol_table
{
	int ScopeDepth;
	int scopeindex;

	char mID[20];
	char mType[8];
	int I_data;
	float F_data;
	struct symbol_table *next;

}symbol_table;

typedef struct scope	// include symbol_table
{
	struct scope *child;
	struct scope *mother;

	symbol_table *inScope_head;
	symbol_table *inScope_list;

	int scopeindex;
}scope;

int scopeindex = 0;		// 每個scope有自己的標籤
scope *scopelist[256];	// 在 dump 時使用, print所有的variable

/* Symbol table function - you can add new function if need. */
symbol_table *lookup_symbol(char const *); // 搜尋 symbol_table, return NULL 或一個 symbol_table
void create_symbol();			// 初始化 - print "Create symbol table", 之後都交給 insert_symbol
void insert_symbol();			// 對每個Scope的symbol_table做賦值
void dump_symbol();				// 印出所有的變數資訊
void IAlwaysInit();				// 避免 Core dump 在 main() 直接做初始化
void scopefunc(char);			// 處理 '{' 和 '}'
float Func_Assign(char, float);	// 處理 Assign Op
float IncDecFunc(char);			// 處理 ++ 和 --

// 必要的函式 
void yyerror(char const *s) { fprintf(stderr, "Error : %s\n", s); }

symbol_table *gbTmp;	// 用於 symboltable 的暫存
scope *Scope, *MasterScope; //Scope 會一直變, MasterScope 作為所有 Scope 的祖先

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
%type <f_val> STORE_INT
%type <f_val> STORE_FLT

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
	| ForStmt
	| IfStmt
	| trap
;

ForStmt : FOR '(' expr ')' stmt { printf("For Stmt"); }
;

IfStmt 
	: IF expr stmt{ printf("If Stmt\n"); }
	| IF '(' expr ')' stmt{ printf("If Stmt\n"); }
	| ELSE IF { puts("Else If Stmt"); }
	| ELSE	{ puts("Else Stmt"); }
;

dcl	: VAR lockedID type '=' CALC	{ create_symbol(); }
	| VAR lockedID type		{ create_symbol(); }
;

comp	
	: '{'	{ scopefunc('{'); }
	| '}'	{ scopefunc('}'); }
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
	: PRINT '(' expr ')' 	{ if(printErrflag == 1) {  printErrflag = 0; } else printf("Print : %g\n", $3); }
	| PRINTLN '(' expr ')' 	{ if(printErrflag == 1) {  printErrflag = 0; } else printf("Println : %g\n", $3); }
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
	|	STORE_ID  { $$ = $1; }
;

CALC	
	: CALC '+' CALC	{ puts("Add");  $$ = $1 + $3;}
	| CALC '-' CALC	{ puts("Sub");  $$ = $1 - $3;}
	| CALC '*' CALC	{ puts("Mul");  $$ = $1 * $3;}
	| CALC '/' CALC	{ if($3 == 0) { printErrflag = 1; printf(ANSI_COLOR_RED   "<ERROR> The divisor can’t be 0 (line %d)\n"    ANSI_COLOR_RESET, yylineno);} else { puts("Div"); $$ = $1 / $3;} }
	| CALC '%' CALC { $$ = (int)$1 % (int)$3;}
	| CALC CALC { printf(ANSI_COLOR_RED   "<ERROR> Syntax Error (line %d)\n"    ANSI_COLOR_RESET, yylineno); return 0; }

	| STORE_ID '%' CALC 
	{ 
		if ( isflt == 1 )
		{
			isflt = 0;
			printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); 
			$$ = 0;
		}

		else
		{
			puts("Mod");
			$$ = (int)$1 % (int)$3;
		}
	}
	| CALC '%' STORE_ID 
	{ 
        if ( isflt == 1 ) 
        {   
            isflt = 0;
            printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); 
            $$ = 0;
        }   

        else
        {   
			puts("Mod");
            $$ = (int)$1 % (int)$3; 
        }	
	}
	| STORE_ID '%' STORE_INT 
	{
        if ( isflt == 1 ) 
        {   
            isflt = 0;
            printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); 
            $$ = 0;
        }   

        else
        {   
			puts("Mod");
            $$ = (int)$1 % I_data;
        }
	}
	| STORE_INT '%' STORE_ID 
	{
        if ( isflt == 1 ) 
        {   
            isflt = 0;
            printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno+1); 
            $$ = 0;
        }   

        else
        {   
			puts("Mod");
            $$ = I_data % (int)$3; 
        }
	}
	| STORE_INT '%' STORE_INT { puts("Mod"); $$ = (int)$1 % (int)$3; }
	| STORE_ID '%' STORE_FLT { printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); $$ = 0; }
	| STORE_FLT '%' STORE_ID { printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); $$ = 0; }
	| STORE_INT '%' STORE_FLT { printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno+1); $$ = 0;}
	| STORE_FLT '%' STORE_INT { printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); $$ = 0;}
	| STORE_FLT '%' CALC { printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); $$ = 0;}
	| CALC '%' STORE_FLT { printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); $$ = 0;}
	| STORE_FLT '%' STORE_FLT { printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); $$ = 0;}
	| '(' CALC ')'	{ $$ = $2; }
	| STORE_ID  { $$ = $1; }
	| STORE_INT { $$ = $1;}
	| STORE_FLT { $$ = $1;}
	| CALC '>' CALC { $$ = $1 > $3; if($$ == 1) puts("True"); else puts("False");}
	| CALC '<' CALC	{ $$ = $1 < $3; if($$ == 1) puts("True"); else puts("False");}
	| CALC EQU CALC	{ $$ = $1 == $3; if($$ == 1) puts("True"); else puts("False");}
	| CALC GRE CALC	{ $$ = $1 >= $3; if($$ == 1) puts("True"); else puts("False");}
	| CALC LSE CALC	{ $$ = $1 <= $3; if($$ == 1) puts("True"); else puts("False");}
	| CALC NEQ CALC	{ $$ = $1 != $3; if($$ == 1) puts("True"); else puts("False");}
;

lockedID 
	: ID		
	{ 
		char *p = strtok($1, "+-*/()=%><$!@#^& \t"); 
		strcpy(lockedID, p);
	}
;

STORE_ID
	: ID		
	{
		char *p = strtok($1, "+-*/()=%><$!@#^& \t");
		strcpy(mID, p); 

		gbTmp = lookup_symbol(mID);
		
		if(!gbTmp)
		{
			printf(ANSI_COLOR_RED   "<ERROR> can't find variable %s (line %d)\n"    ANSI_COLOR_RESET, mID, yylineno);
		}
		else
		{
			printf("variable %s is depth %d\n", mID, gbTmp->ScopeDepth);
			if(gbTmp->mType[0] == 'i')
			{
				$$ = (float)gbTmp->I_data;
			}
			else if(gbTmp->mType[0] == 'f')
			{
				isflt = 1;
				$$ = gbTmp->F_data;
			}
		}
	}
;

STORE_STR
	: STRING	{ strcpy(mStr, $1); };

STORE_INT
	: I_CONST	{ $$ = (float)$1; I_data = $1;};

STORE_FLT
	: F_CONST	{ $$ = $1; F_data = $1;};

trap 	
	: NEWLINE 	{ /* puts("NEWLINE"); */}
	| Other 	{  /*puts("Other");*/  } 
	| trap trap
;

%%

/* C code section */
int main(int argc, char** argv)
{
	yyin = fopen(argv[1], "r");

	yylineno = 0;
	IAlwaysInit();	

	yyparse();
	
	printf("\nTotal line : %d\n", yylineno);

	printf("\nThe symbol table:\n");
	dump_symbol();
	
	return 0;
}

void IAlwaysInit()
{
	Scope = malloc(sizeof(scope));
	Scope -> inScope_list = malloc(sizeof(symbol_table));
	Scope -> inScope_list -> scopeindex = scopeindex;
	Scope -> inScope_head = Scope->inScope_list;
	Scope -> scopeindex = scopeindex;
	MasterScope = Scope;
	MasterScope->mother = malloc(sizeof(scope));

	scopelist[0] = Scope;
}

void scopefunc(char m)
{
	/*
		每個Scope有自己的Symbol Table
		應該要直接使用scope裡面的inScope_table, inScope_head 才對.
		如果在自己的Symbol Table找不到變數 -> 則尋找Mother.
	*/
	scope *mother;

	if(m == '{') // 如果遇到左括號
	{
		Scope -> child = malloc(sizeof(scope)); // 分配空間

		mother = Scope; 					// 設給 mother 當前的 Scope

		Scope = Scope -> child; 			// 當前 Scope 設為 child
		Scope -> mother = mother; 			// child 的 mother 等於前面設定好的 mother

		ScopeDepth ++; 						// 深度 + 1

		Scope -> inScope_list = malloc(sizeof(symbol_table));
		Scope -> inScope_head = Scope -> inScope_list;

		scopeindex ++; // 每個scope都有自己的 index
		scopelist[scopeindex] = Scope; 
		Scope -> scopeindex = scopeindex;

		l = 1;
	}

	else if(m == '}') // 如果遇到右括號
	{
		Scope = Scope -> mother; // Scope 設為 mother
		ScopeDepth --; // 深度 - 1
		
		if( l == 1 && r == 0 )
		{
			Scope -> child -> child = malloc(sizeof(scope));
			r = 1;
		}
	}

	if (ScopeDepth == 0)
	{
		r = 0;
	}

	if (MaxScopeDepth < ScopeDepth)
	{
		MaxScopeDepth = ScopeDepth; // 紀錄最大深度
	}
}

void create_symbol() 
{	
	if(initflag == 0){
		puts("Create symbol table");
		initflag = 1;
	}
	insert_symbol();
}

void insert_symbol() 
{
	declaredtwice = 0;

	if(lookup_symbol(lockedID) && declaredtwice == 0)
	{
		printf(ANSI_COLOR_RED   "<ERROR> re-declaration for variable %s (line %d)\n"    ANSI_COLOR_RESET, lockedID, yylineno);
		return;
	}

	printf("Insert a symbol: %s\n", lockedID);

	Scope -> inScope_list -> ScopeDepth = ScopeDepth;
	Scope -> inScope_list -> scopeindex = scopeindex;
	strcpy(Scope -> inScope_list -> mID, lockedID);
	strcpy(Scope -> inScope_list -> mType, mType);

	if(mType[0] == 'i')
	{
		Scope -> inScope_list ->I_data = I_data;
	}
	else if(mType[0] == 'f')
	{
		Scope -> inScope_list ->F_data = F_data;
	}

	printf("declare %s in block of depth %d\n", lockedID, Scope-> inScope_list -> ScopeDepth);

	Scope -> inScope_list -> next = malloc(sizeof(symbol_table));
	Scope -> inScope_list = Scope-> inScope_list -> next;
}

symbol_table *lookup_symbol(char const *Look_ID) // 只搜尋自己的Scope 找不到再找 mother
{
	scope *tmp = Scope;

	while(tmp -> mother != NULL)
	{
		symbol_table *ttmp  = tmp -> inScope_head;
		
		while(ttmp -> next != NULL)
		{
			if(strcmp(ttmp->mID, Look_ID) == 0)
			{
				return ttmp;
			}
			ttmp = ttmp -> next;
		}

		declaredtwice++;
		tmp = tmp -> mother;
	}

	return NULL;
}

void dump_symbol()
{
	puts("ID\tType\tData\tDepth");

	scope *tmp = MasterScope;

	int i = 0;

	for ( i = 0; i <= scopeindex; i++)
	{
		symbol_table *ttmp = scopelist[i] -> inScope_head;

		while(ttmp -> next != NULL)
		{
             if(ttmp -> mType[0] == 'i')
             {
                 printf("%s\t%s\t%d\t%d\n", ttmp -> mID, ttmp -> mType, ttmp->I_data, ttmp->ScopeDepth); 
             }
             else if(ttmp -> mType[0] == 'f')
             {
                 printf("%s\t%s\t%g\t%d\n", ttmp -> mID, ttmp -> mType, ttmp->F_data, ttmp->ScopeDepth);
             }
             ttmp = ttmp -> next;
		}
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
				case '%' : printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); break;
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
