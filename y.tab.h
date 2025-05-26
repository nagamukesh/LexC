/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    IF = 259,                      /* IF  */
    INT = 260,                     /* INT  */
    CHAR = 261,                    /* CHAR  */
    FLOAT = 262,                   /* FLOAT  */
    DOUBLE = 263,                  /* DOUBLE  */
    LONG = 264,                    /* LONG  */
    SHORT = 265,                   /* SHORT  */
    SIGNED = 266,                  /* SIGNED  */
    UNSIGNED = 267,                /* UNSIGNED  */
    STRUCT = 268,                  /* STRUCT  */
    RETURN = 269,                  /* RETURN  */
    MAIN = 270,                    /* MAIN  */
    VOID = 271,                    /* VOID  */
    WHILE = 272,                   /* WHILE  */
    FOR = 273,                     /* FOR  */
    DO = 274,                      /* DO  */
    BREAK = 275,                   /* BREAK  */
    CONTINUE = 276,                /* CONTINUE  */
    GOTO = 277,                    /* GOTO  */
    ENDIF = 278,                   /* ENDIF  */
    SWITCH = 279,                  /* SWITCH  */
    CASE = 280,                    /* CASE  */
    DEFAULT = 281,                 /* DEFAULT  */
    AUTO = 282,                    /* AUTO  */
    CONST = 283,                   /* CONST  */
    BOOL = 284,                    /* BOOL  */
    STATIC = 285,                  /* STATIC  */
    TYPEDEF = 286,                 /* TYPEDEF  */
    UNION = 287,                   /* UNION  */
    VOLATILE = 288,                /* VOLATILE  */
    OPEN_CURLY = 289,              /* OPEN_CURLY  */
    CLOSE_CURLY = 290,             /* CLOSE_CURLY  */
    SEMI_COLON = 291,              /* SEMI_COLON  */
    COMMA = 292,                   /* COMMA  */
    COLON = 293,                   /* COLON  */
    EQUALS = 294,                  /* EQUALS  */
    OPEN_BRACE = 295,              /* OPEN_BRACE  */
    CLOSE_BRACE = 296,             /* CLOSE_BRACE  */
    OPEN_SQR = 297,                /* OPEN_SQR  */
    CLOSE_SQR = 298,               /* CLOSE_SQR  */
    DOT = 299,                     /* DOT  */
    AND = 300,                     /* AND  */
    NOT = 301,                     /* NOT  */
    TILD = 302,                    /* TILD  */
    HYPHEN = 303,                  /* HYPHEN  */
    PLUS = 304,                    /* PLUS  */
    MULTIPLY = 305,                /* MULTIPLY  */
    DIVIDE = 306,                  /* DIVIDE  */
    PERCENT = 307,                 /* PERCENT  */
    POWER = 308,                   /* POWER  */
    OR = 309,                      /* OR  */
    QUESTION = 310,                /* QUESTION  */
    integer_constant = 311,        /* integer_constant  */
    string_constant = 312,         /* string_constant  */
    float_constant = 313,          /* float_constant  */
    character_constant = 314,      /* character_constant  */
    RIGHT_ASSIGN = 315,            /* RIGHT_ASSIGN  */
    LEFT_ASSIGN = 316,             /* LEFT_ASSIGN  */
    AND_ASSIGN = 317,              /* AND_ASSIGN  */
    XOR_ASSIGN = 318,              /* XOR_ASSIGN  */
    OR_ASSIGN = 319,               /* OR_ASSIGN  */
    RIGHT_OP = 320,                /* RIGHT_OP  */
    LEFT_OP = 321,                 /* LEFT_OP  */
    PTR_OP = 322,                  /* PTR_OP  */
    ELSE = 323,                    /* ELSE  */
    MOD_EQUAL = 324,               /* MOD_EQUAL  */
    MUL_EQUAL = 325,               /* MUL_EQUAL  */
    DIV_EQUAL = 326,               /* DIV_EQUAL  */
    ADD_EQUAL = 327,               /* ADD_EQUAL  */
    SUB_EQUAL = 328,               /* SUB_EQUAL  */
    OR_OP = 329,                   /* OR_OP  */
    AND_OP = 330,                  /* AND_OP  */
    EQUAL = 331,                   /* EQUAL  */
    NOT_EQUAL = 332,               /* NOT_EQUAL  */
    LESSER_EQUAL = 333,            /* LESSER_EQUAL  */
    LESSER = 334,                  /* LESSER  */
    GREATER_EQUAL = 335,           /* GREATER_EQUAL  */
    GREATER = 336,                 /* GREATER  */
    SIZEOF = 337,                  /* SIZEOF  */
    INCREMENT = 338,               /* INCREMENT  */
    DECREMENT = 339                /* DECREMENT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IDENTIFIER 258
#define IF 259
#define INT 260
#define CHAR 261
#define FLOAT 262
#define DOUBLE 263
#define LONG 264
#define SHORT 265
#define SIGNED 266
#define UNSIGNED 267
#define STRUCT 268
#define RETURN 269
#define MAIN 270
#define VOID 271
#define WHILE 272
#define FOR 273
#define DO 274
#define BREAK 275
#define CONTINUE 276
#define GOTO 277
#define ENDIF 278
#define SWITCH 279
#define CASE 280
#define DEFAULT 281
#define AUTO 282
#define CONST 283
#define BOOL 284
#define STATIC 285
#define TYPEDEF 286
#define UNION 287
#define VOLATILE 288
#define OPEN_CURLY 289
#define CLOSE_CURLY 290
#define SEMI_COLON 291
#define COMMA 292
#define COLON 293
#define EQUALS 294
#define OPEN_BRACE 295
#define CLOSE_BRACE 296
#define OPEN_SQR 297
#define CLOSE_SQR 298
#define DOT 299
#define AND 300
#define NOT 301
#define TILD 302
#define HYPHEN 303
#define PLUS 304
#define MULTIPLY 305
#define DIVIDE 306
#define PERCENT 307
#define POWER 308
#define OR 309
#define QUESTION 310
#define integer_constant 311
#define string_constant 312
#define float_constant 313
#define character_constant 314
#define RIGHT_ASSIGN 315
#define LEFT_ASSIGN 316
#define AND_ASSIGN 317
#define XOR_ASSIGN 318
#define OR_ASSIGN 319
#define RIGHT_OP 320
#define LEFT_OP 321
#define PTR_OP 322
#define ELSE 323
#define MOD_EQUAL 324
#define MUL_EQUAL 325
#define DIV_EQUAL 326
#define ADD_EQUAL 327
#define SUB_EQUAL 328
#define OR_OP 329
#define AND_OP 330
#define EQUAL 331
#define NOT_EQUAL 332
#define LESSER_EQUAL 333
#define LESSER 334
#define GREATER_EQUAL 335
#define GREATER 336
#define SIZEOF 337
#define INCREMENT 338
#define DECREMENT 339

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 161 "final_parser.y"
 
	struct var_name { 
		char name[100]; 
		struct node* nd;
	} nd_obj; 

#line 242 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
