/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PRINT = 258,
    PRINTLN = 259,
    IF = 260,
    ELSE = 261,
    FOR = 262,
    ELIF = 263,
    VAR = 264,
    NEWLINE = 265,
    INT = 266,
    FLOAT = 267,
    VOID = 268,
    INCREMENT = 269,
    DECREMENT = 270,
    Add_Assign = 271,
    Sub_Assign = 272,
    Mul_Assign = 273,
    Div_Assign = 274,
    Mod_Assign = 275,
    GRE = 276,
    LSE = 277,
    EQU = 278,
    NEQ = 279,
    AND = 280,
    OR = 281,
    Other = 282,
    I_CONST = 283,
    F_CONST = 284,
    STRING = 285,
    ID = 286
  };
#endif
/* Tokens.  */
#define PRINT 258
#define PRINTLN 259
#define IF 260
#define ELSE 261
#define FOR 262
#define ELIF 263
#define VAR 264
#define NEWLINE 265
#define INT 266
#define FLOAT 267
#define VOID 268
#define INCREMENT 269
#define DECREMENT 270
#define Add_Assign 271
#define Sub_Assign 272
#define Mul_Assign 273
#define Div_Assign 274
#define Mod_Assign 275
#define GRE 276
#define LSE 277
#define EQU 278
#define NEQ 279
#define AND 280
#define OR 281
#define Other 282
#define I_CONST 283
#define F_CONST 284
#define STRING 285
#define ID 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 75 "compiler_hw2.y" /* yacc.c:1909  */

	int i_val;
	double f_val;
	char* string;

#line 122 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
