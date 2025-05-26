/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "final_parser.y"

        void yyerror(char* s);
        int yylex();
        #include "stdio.h"
        #include "stdlib.h"
        #include "ctype.h"
        #include "string.h"
        #include "custom_memory.h"  // Include custom memory management
        
        void insert_type();
        void insert_class();
        void insert_value();
        void insert_dimensions();
        void insert_pdl(int pdl);
        void insert_parameters();
        int flag=0;
        int insert_flag = 0;
        int pdl;

        extern char current_identifier[20];
        extern char current_type[20];
        extern char current_value[20];
        extern char current_function[20];
        extern char previous_operator[20];
        extern void init_lexer_memory();

        // Define the node structure first
        struct node { 
                struct node *child1; 
                struct node *child2;
                struct node *child3; 
                struct node *child4; 
                struct node *child5;
                struct node *child6; 
                struct node *child7; 
                char *token; 
        };

        struct node *head;

        struct queueNode {
                struct node *treeNode;
                struct queueNode *next;
        };

        struct queue {
                struct queueNode *front;
                struct queueNode *rear;
        };

        // Function declarations
        struct node* mknode(struct node *child1, struct node *child2, struct node *child3, 
                          struct node *child4, struct node *child5, struct node *child6, 
                          struct node *child7, char *token);
        void levelOrderTraversal(struct node *root);
        int isEmpty(struct queue *q);

        // Implementation of mknode
        struct node* mknode(struct node *child1, struct node *child2, struct node *child3, 
                          struct node *child4, struct node *child5, struct node *child6, 
                          struct node *child7, char *token) {
                struct node *newnode = (struct node *)custom_malloc(sizeof(struct node));
                char *newstr = (char *)custom_malloc(strlen(token) + 1);
                strcpy(newstr, token);
                newnode->token = newstr;
                newnode->child1 = child1;
                newnode->child2 = child2;
                newnode->child3 = child3;
                newnode->child4 = child4;
                newnode->child5 = child5;
                newnode->child6 = child6;
                newnode->child7 = child7;
                return newnode;
        }

        void enqueue(struct queue *q, struct node *treeNode) {
                struct queueNode *newNode = (struct queueNode *)custom_malloc(sizeof(struct queueNode));
                newNode->treeNode = treeNode;
                newNode->next = NULL;
                if (q->rear == NULL) {
                        q->front = q->rear = newNode;
                } else {
                        q->rear->next = newNode;
                        q->rear = newNode;
                }
        }

        struct node *dequeue(struct queue *q) {
                if (q->front == NULL) {
                        return NULL;
                }
                struct queueNode *temp = q->front;
                struct node *treeNode = temp->treeNode;
                q->front = q->front->next;
                if (q->front == NULL) {
                        q->rear = NULL;
                }
                custom_free(temp);
                return treeNode;
        }

        int isEmpty(struct queue *q) {
                return q->front == NULL;
        }

        void cleanup_tree(struct node *root) {
                if (root == NULL) return;
                cleanup_tree(root->child1);
                cleanup_tree(root->child2);
                cleanup_tree(root->child3);
                cleanup_tree(root->child4);
                cleanup_tree(root->child5);
                cleanup_tree(root->child6);
                cleanup_tree(root->child7);
                custom_free(root->token);
                custom_free(root);
        }

        void levelOrderTraversal(struct node *root) {
                if (root == NULL) return;

                struct queue q;
                q.front = q.rear = NULL;

                enqueue(&q, root);
                int level = 0;

                printf("\n");
                while (!isEmpty(&q)) {
                        int levelSize = 0;
                        struct queueNode *current = q.front;
                        while (current != NULL) {
                                levelSize++;
                                current = current->next;
                        }

                        for (int i = 0; i < levelSize; i++) {
                                struct node *currentNode = dequeue(&q);
                                
                                // Print indentation and tree branches
                                for (int j = 0; j < level; j++) {
                                        printf("│   ");
                                }
                                printf("├── %s\n", currentNode->token);

                                // Enqueue child nodes in reverse order to maintain tree structure
                                if (currentNode->child7 != NULL) enqueue(&q, currentNode->child7);
                                if (currentNode->child6 != NULL) enqueue(&q, currentNode->child6);
                                if (currentNode->child5 != NULL) enqueue(&q, currentNode->child5);
                                if (currentNode->child4 != NULL) enqueue(&q, currentNode->child4);
                                if (currentNode->child3 != NULL) enqueue(&q, currentNode->child3);
                                if (currentNode->child2 != NULL) enqueue(&q, currentNode->child2);
                                if (currentNode->child1 != NULL) enqueue(&q, currentNode->child1);
                        }
                        level++;
                }
                printf("\n");
        }

#line 231 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 459 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_IF = 4,                         /* IF  */
  YYSYMBOL_INT = 5,                        /* INT  */
  YYSYMBOL_CHAR = 6,                       /* CHAR  */
  YYSYMBOL_FLOAT = 7,                      /* FLOAT  */
  YYSYMBOL_DOUBLE = 8,                     /* DOUBLE  */
  YYSYMBOL_LONG = 9,                       /* LONG  */
  YYSYMBOL_SHORT = 10,                     /* SHORT  */
  YYSYMBOL_SIGNED = 11,                    /* SIGNED  */
  YYSYMBOL_UNSIGNED = 12,                  /* UNSIGNED  */
  YYSYMBOL_STRUCT = 13,                    /* STRUCT  */
  YYSYMBOL_RETURN = 14,                    /* RETURN  */
  YYSYMBOL_MAIN = 15,                      /* MAIN  */
  YYSYMBOL_VOID = 16,                      /* VOID  */
  YYSYMBOL_WHILE = 17,                     /* WHILE  */
  YYSYMBOL_FOR = 18,                       /* FOR  */
  YYSYMBOL_DO = 19,                        /* DO  */
  YYSYMBOL_BREAK = 20,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 21,                  /* CONTINUE  */
  YYSYMBOL_GOTO = 22,                      /* GOTO  */
  YYSYMBOL_ENDIF = 23,                     /* ENDIF  */
  YYSYMBOL_SWITCH = 24,                    /* SWITCH  */
  YYSYMBOL_CASE = 25,                      /* CASE  */
  YYSYMBOL_DEFAULT = 26,                   /* DEFAULT  */
  YYSYMBOL_AUTO = 27,                      /* AUTO  */
  YYSYMBOL_CONST = 28,                     /* CONST  */
  YYSYMBOL_BOOL = 29,                      /* BOOL  */
  YYSYMBOL_STATIC = 30,                    /* STATIC  */
  YYSYMBOL_TYPEDEF = 31,                   /* TYPEDEF  */
  YYSYMBOL_UNION = 32,                     /* UNION  */
  YYSYMBOL_VOLATILE = 33,                  /* VOLATILE  */
  YYSYMBOL_OPEN_CURLY = 34,                /* OPEN_CURLY  */
  YYSYMBOL_CLOSE_CURLY = 35,               /* CLOSE_CURLY  */
  YYSYMBOL_SEMI_COLON = 36,                /* SEMI_COLON  */
  YYSYMBOL_COMMA = 37,                     /* COMMA  */
  YYSYMBOL_COLON = 38,                     /* COLON  */
  YYSYMBOL_EQUALS = 39,                    /* EQUALS  */
  YYSYMBOL_OPEN_BRACE = 40,                /* OPEN_BRACE  */
  YYSYMBOL_CLOSE_BRACE = 41,               /* CLOSE_BRACE  */
  YYSYMBOL_OPEN_SQR = 42,                  /* OPEN_SQR  */
  YYSYMBOL_CLOSE_SQR = 43,                 /* CLOSE_SQR  */
  YYSYMBOL_DOT = 44,                       /* DOT  */
  YYSYMBOL_AND = 45,                       /* AND  */
  YYSYMBOL_NOT = 46,                       /* NOT  */
  YYSYMBOL_TILD = 47,                      /* TILD  */
  YYSYMBOL_HYPHEN = 48,                    /* HYPHEN  */
  YYSYMBOL_PLUS = 49,                      /* PLUS  */
  YYSYMBOL_MULTIPLY = 50,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 51,                    /* DIVIDE  */
  YYSYMBOL_PERCENT = 52,                   /* PERCENT  */
  YYSYMBOL_POWER = 53,                     /* POWER  */
  YYSYMBOL_OR = 54,                        /* OR  */
  YYSYMBOL_QUESTION = 55,                  /* QUESTION  */
  YYSYMBOL_integer_constant = 56,          /* integer_constant  */
  YYSYMBOL_string_constant = 57,           /* string_constant  */
  YYSYMBOL_float_constant = 58,            /* float_constant  */
  YYSYMBOL_character_constant = 59,        /* character_constant  */
  YYSYMBOL_RIGHT_ASSIGN = 60,              /* RIGHT_ASSIGN  */
  YYSYMBOL_LEFT_ASSIGN = 61,               /* LEFT_ASSIGN  */
  YYSYMBOL_AND_ASSIGN = 62,                /* AND_ASSIGN  */
  YYSYMBOL_XOR_ASSIGN = 63,                /* XOR_ASSIGN  */
  YYSYMBOL_OR_ASSIGN = 64,                 /* OR_ASSIGN  */
  YYSYMBOL_RIGHT_OP = 65,                  /* RIGHT_OP  */
  YYSYMBOL_LEFT_OP = 66,                   /* LEFT_OP  */
  YYSYMBOL_PTR_OP = 67,                    /* PTR_OP  */
  YYSYMBOL_ELSE = 68,                      /* ELSE  */
  YYSYMBOL_MOD_EQUAL = 69,                 /* MOD_EQUAL  */
  YYSYMBOL_MUL_EQUAL = 70,                 /* MUL_EQUAL  */
  YYSYMBOL_DIV_EQUAL = 71,                 /* DIV_EQUAL  */
  YYSYMBOL_ADD_EQUAL = 72,                 /* ADD_EQUAL  */
  YYSYMBOL_SUB_EQUAL = 73,                 /* SUB_EQUAL  */
  YYSYMBOL_OR_OP = 74,                     /* OR_OP  */
  YYSYMBOL_AND_OP = 75,                    /* AND_OP  */
  YYSYMBOL_EQUAL = 76,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 77,                 /* NOT_EQUAL  */
  YYSYMBOL_LESSER_EQUAL = 78,              /* LESSER_EQUAL  */
  YYSYMBOL_LESSER = 79,                    /* LESSER  */
  YYSYMBOL_GREATER_EQUAL = 80,             /* GREATER_EQUAL  */
  YYSYMBOL_GREATER = 81,                   /* GREATER  */
  YYSYMBOL_SIZEOF = 82,                    /* SIZEOF  */
  YYSYMBOL_INCREMENT = 83,                 /* INCREMENT  */
  YYSYMBOL_DECREMENT = 84,                 /* DECREMENT  */
  YYSYMBOL_YYACCEPT = 85,                  /* $accept  */
  YYSYMBOL_state = 86,                     /* state  */
  YYSYMBOL_declarations = 87,              /* declarations  */
  YYSYMBOL_declaration = 88,               /* declaration  */
  YYSYMBOL_structure_dec = 89,             /* structure_dec  */
  YYSYMBOL_90_1 = 90,                      /* $@1  */
  YYSYMBOL_structure_content = 91,         /* structure_content  */
  YYSYMBOL_variable_dec = 92,              /* variable_dec  */
  YYSYMBOL_structure_initialize = 93,      /* structure_initialize  */
  YYSYMBOL_variables = 94,                 /* variables  */
  YYSYMBOL_multiple_variables = 95,        /* multiple_variables  */
  YYSYMBOL_identifier_name = 96,           /* identifier_name  */
  YYSYMBOL_97_2 = 97,                      /* $@2  */
  YYSYMBOL_extended_identifier = 98,       /* extended_identifier  */
  YYSYMBOL_99_3 = 99,                      /* $@3  */
  YYSYMBOL_array_identifier = 100,         /* array_identifier  */
  YYSYMBOL_array_dims = 101,               /* array_dims  */
  YYSYMBOL_102_4 = 102,                    /* $@4  */
  YYSYMBOL_initilization = 103,            /* initilization  */
  YYSYMBOL_string_initilization = 104,     /* string_initilization  */
  YYSYMBOL_105_5 = 105,                    /* $@5  */
  YYSYMBOL_106_6 = 106,                    /* $@6  */
  YYSYMBOL_array_initialization = 107,     /* array_initialization  */
  YYSYMBOL_108_7 = 108,                    /* $@7  */
  YYSYMBOL_array_values = 109,             /* array_values  */
  YYSYMBOL_multiple_array_values = 110,    /* multiple_array_values  */
  YYSYMBOL_datatype = 111,                 /* datatype  */
  YYSYMBOL_unsigned_grammar = 112,         /* unsigned_grammar  */
  YYSYMBOL_signed_grammar = 113,           /* signed_grammar  */
  YYSYMBOL_long_grammar = 114,             /* long_grammar  */
  YYSYMBOL_function_dec = 115,             /* function_dec  */
  YYSYMBOL_function_name = 116,            /* function_name  */
  YYSYMBOL_117_8 = 117,                    /* $@8  */
  YYSYMBOL_function_data = 118,            /* function_data  */
  YYSYMBOL_119_9 = 119,                    /* $@9  */
  YYSYMBOL_120_10 = 120,                   /* $@10  */
  YYSYMBOL_parameters = 121,               /* parameters  */
  YYSYMBOL_all_parameter_identifiers = 122, /* all_parameter_identifiers  */
  YYSYMBOL_multiple_parameters = 123,      /* multiple_parameters  */
  YYSYMBOL_parameter_identifier = 124,     /* parameter_identifier  */
  YYSYMBOL_125_11 = 125,                   /* $@11  */
  YYSYMBOL_extended_parameter = 126,       /* extended_parameter  */
  YYSYMBOL_statement = 127,                /* statement  */
  YYSYMBOL_multiple_statement = 128,       /* multiple_statement  */
  YYSYMBOL_statments = 129,                /* statments  */
  YYSYMBOL_expression_statment = 130,      /* expression_statment  */
  YYSYMBOL_conditional_statements = 131,   /* conditional_statements  */
  YYSYMBOL_extended_conditional_statements = 132, /* extended_conditional_statements  */
  YYSYMBOL_switch_statement = 133,         /* switch_statement  */
  YYSYMBOL_extended_switch_statement = 134, /* extended_switch_statement  */
  YYSYMBOL_iterative_statements = 135,     /* iterative_statements  */
  YYSYMBOL_for_initialization = 136,       /* for_initialization  */
  YYSYMBOL_return_statement = 137,         /* return_statement  */
  YYSYMBOL_return_suffix = 138,            /* return_suffix  */
  YYSYMBOL_break_statement = 139,          /* break_statement  */
  YYSYMBOL_expression = 140,               /* expression  */
  YYSYMBOL_expressions = 141,              /* expressions  */
  YYSYMBOL_142_12 = 142,                   /* $@12  */
  YYSYMBOL_143_13 = 143,                   /* $@13  */
  YYSYMBOL_144_14 = 144,                   /* $@14  */
  YYSYMBOL_145_15 = 145,                   /* $@15  */
  YYSYMBOL_146_16 = 146,                   /* $@16  */
  YYSYMBOL_147_17 = 147,                   /* $@17  */
  YYSYMBOL_simple_expression = 148,        /* simple_expression  */
  YYSYMBOL_simple_expression_breakup = 149, /* simple_expression_breakup  */
  YYSYMBOL_and_expression = 150,           /* and_expression  */
  YYSYMBOL_and_expression_breakup = 151,   /* and_expression_breakup  */
  YYSYMBOL_unary_relation_expression = 152, /* unary_relation_expression  */
  YYSYMBOL_regular_expression = 153,       /* regular_expression  */
  YYSYMBOL_regular_expression_breakup = 154, /* regular_expression_breakup  */
  YYSYMBOL_relational_operators = 155,     /* relational_operators  */
  YYSYMBOL_156_18 = 156,                   /* $@18  */
  YYSYMBOL_157_19 = 157,                   /* $@19  */
  YYSYMBOL_158_20 = 158,                   /* $@20  */
  YYSYMBOL_159_21 = 159,                   /* $@21  */
  YYSYMBOL_160_22 = 160,                   /* $@22  */
  YYSYMBOL_161_23 = 161,                   /* $@23  */
  YYSYMBOL_sum_expression = 162,           /* sum_expression  */
  YYSYMBOL_sum_operators = 163,            /* sum_operators  */
  YYSYMBOL_term = 164,                     /* term  */
  YYSYMBOL_multiply_operators = 165,       /* multiply_operators  */
  YYSYMBOL_factor = 166,                   /* factor  */
  YYSYMBOL_iden = 167,                     /* iden  */
  YYSYMBOL_extended_iden = 168,            /* extended_iden  */
  YYSYMBOL_func = 169,                     /* func  */
  YYSYMBOL_170_24 = 170,                   /* $@24  */
  YYSYMBOL_func_call = 171,                /* func_call  */
  YYSYMBOL_172_25 = 172,                   /* $@25  */
  YYSYMBOL_arguments = 173,                /* arguments  */
  YYSYMBOL_arguments_list = 174,           /* arguments_list  */
  YYSYMBOL_extended_arguments = 175,       /* extended_arguments  */
  YYSYMBOL_constant = 176,                 /* constant  */
  YYSYMBOL_177_26 = 177,                   /* $@26  */
  YYSYMBOL_178_27 = 178,                   /* $@27  */
  YYSYMBOL_179_28 = 179,                   /* $@28  */
  YYSYMBOL_180_29 = 180                    /* $@29  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  32
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   305

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  96
/* YYNRULES -- Number of rules.  */
#define YYNRULES  177
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  278

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   339


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   209,   209,   217,   222,   228,   232,   236,   243,   243,
     254,   259,   265,   270,   276,   283,   292,   299,   305,   311,
     311,   318,   322,   322,   330,   336,   342,   342,   347,   355,
     359,   364,   370,   370,   370,   378,   378,   388,   395,   401,
     408,   412,   416,   420,   424,   429,   434,   439,   444,   451,
     455,   460,   466,   472,   476,   481,   487,   493,   498,   505,
     513,   513,   520,   520,   526,   526,   534,   539,   546,   553,
     559,   565,   565,   573,   580,   586,   590,   594,   598,   602,
     606,   610,   614,   621,   630,   635,   641,   646,   654,   664,
     670,   675,   688,   695,   699,   708,   715,   723,   735,   739,
     744,   752,   760,   765,   773,   782,   786,   793,   793,   798,
     798,   803,   803,   808,   808,   813,   813,   818,   818,   823,
     828,   836,   843,   849,   855,   862,   868,   874,   879,   886,
     893,   898,   904,   904,   909,   909,   914,   914,   919,   919,
     924,   924,   929,   929,   937,   941,   948,   953,   961,   965,
     972,   977,   982,   990,   994,  1001,  1006,  1013,  1019,  1028,
    1028,  1034,  1038,  1045,  1045,  1055,  1060,  1066,  1073,  1079,
    1085,  1085,  1089,  1089,  1093,  1093,  1097,  1097
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER", "IF",
  "INT", "CHAR", "FLOAT", "DOUBLE", "LONG", "SHORT", "SIGNED", "UNSIGNED",
  "STRUCT", "RETURN", "MAIN", "VOID", "WHILE", "FOR", "DO", "BREAK",
  "CONTINUE", "GOTO", "ENDIF", "SWITCH", "CASE", "DEFAULT", "AUTO",
  "CONST", "BOOL", "STATIC", "TYPEDEF", "UNION", "VOLATILE", "OPEN_CURLY",
  "CLOSE_CURLY", "SEMI_COLON", "COMMA", "COLON", "EQUALS", "OPEN_BRACE",
  "CLOSE_BRACE", "OPEN_SQR", "CLOSE_SQR", "DOT", "AND", "NOT", "TILD",
  "HYPHEN", "PLUS", "MULTIPLY", "DIVIDE", "PERCENT", "POWER", "OR",
  "QUESTION", "integer_constant", "string_constant", "float_constant",
  "character_constant", "RIGHT_ASSIGN", "LEFT_ASSIGN", "AND_ASSIGN",
  "XOR_ASSIGN", "OR_ASSIGN", "RIGHT_OP", "LEFT_OP", "PTR_OP", "ELSE",
  "MOD_EQUAL", "MUL_EQUAL", "DIV_EQUAL", "ADD_EQUAL", "SUB_EQUAL", "OR_OP",
  "AND_OP", "EQUAL", "NOT_EQUAL", "LESSER_EQUAL", "LESSER",
  "GREATER_EQUAL", "GREATER", "SIZEOF", "INCREMENT", "DECREMENT",
  "$accept", "state", "declarations", "declaration", "structure_dec",
  "$@1", "structure_content", "variable_dec", "structure_initialize",
  "variables", "multiple_variables", "identifier_name", "$@2",
  "extended_identifier", "$@3", "array_identifier", "array_dims", "$@4",
  "initilization", "string_initilization", "$@5", "$@6",
  "array_initialization", "$@7", "array_values", "multiple_array_values",
  "datatype", "unsigned_grammar", "signed_grammar", "long_grammar",
  "function_dec", "function_name", "$@8", "function_data", "$@9", "$@10",
  "parameters", "all_parameter_identifiers", "multiple_parameters",
  "parameter_identifier", "$@11", "extended_parameter", "statement",
  "multiple_statement", "statments", "expression_statment",
  "conditional_statements", "extended_conditional_statements",
  "switch_statement", "extended_switch_statement", "iterative_statements",
  "for_initialization", "return_statement", "return_suffix",
  "break_statement", "expression", "expressions", "$@12", "$@13", "$@14",
  "$@15", "$@16", "$@17", "simple_expression", "simple_expression_breakup",
  "and_expression", "and_expression_breakup", "unary_relation_expression",
  "regular_expression", "regular_expression_breakup",
  "relational_operators", "$@18", "$@19", "$@20", "$@21", "$@22", "$@23",
  "sum_expression", "sum_operators", "term", "multiply_operators",
  "factor", "iden", "extended_iden", "func", "$@24", "func_call", "$@25",
  "arguments", "arguments_list", "extended_arguments", "constant", "$@26",
  "$@27", "$@28", "$@29", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-240)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-61)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     158,  -240,  -240,  -240,  -240,    12,    12,    13,    19,    22,
    -240,    34,  -240,   158,  -240,  -240,  -240,     4,  -240,    11,
    -240,  -240,  -240,  -240,    12,    12,  -240,  -240,    12,    12,
    -240,    50,  -240,  -240,    38,    50,    23,    37,   289,  -240,
    -240,  -240,  -240,  -240,    45,  -240,    -7,  -240,    44,  -240,
      50,  -240,    79,    48,   246,  -240,   -30,  -240,  -240,  -240,
    -240,  -240,  -240,    56,     9,    91,    60,   246,    16,    27,
      62,  -240,  -240,    61,   289,  -240,   177,  -240,  -240,    50,
      66,  -240,    64,  -240,    27,  -240,  -240,  -240,  -240,  -240,
    -240,    40,    49,  -240,    42,    -3,  -240,    69,  -240,  -240,
    -240,  -240,  -240,    73,    74,  -240,  -240,    72,     6,    85,
      86,   177,   101,    87,   177,  -240,  -240,   177,  -240,   108,
    -240,  -240,  -240,  -240,  -240,  -240,   109,  -240,  -240,  -240,
      27,  -240,    -4,  -240,  -240,  -240,  -240,    27,  -240,    27,
    -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,
      41,    41,  -240,  -240,  -240,    41,  -240,    27,   141,  -240,
    -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,    89,   110,
    -240,    27,  -240,  -240,   112,    27,   234,   133,  -240,   148,
     119,  -240,  -240,  -240,    27,   114,    40,    49,  -240,  -240,
    -240,  -240,  -240,  -240,    21,    -3,  -240,    27,   113,  -240,
      27,    27,    27,    27,    27,  -240,   123,  -240,  -240,  -240,
     117,  -240,   118,  -240,  -240,    27,   124,   122,   131,  -240,
    -240,   138,   135,  -240,  -240,  -240,  -240,  -240,  -240,  -240,
    -240,  -240,  -240,  -240,  -240,   144,   177,   177,   156,  -240,
      27,   164,    27,  -240,  -240,   143,   132,  -240,    27,   161,
      -5,   138,   166,   170,   177,  -240,   165,   171,   152,   172,
     174,  -240,  -240,   143,  -240,  -240,  -240,  -240,  -240,   176,
     192,  -240,  -240,    27,  -240,   179,    -5,  -240
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    40,    41,    42,    43,    58,    58,    56,    52,     0,
      48,     0,     2,     4,     7,     5,    14,     0,     6,     0,
      57,    44,    45,    53,    58,    58,    47,    49,    58,    58,
      46,     8,     1,     3,    19,     0,     0,    18,    67,    54,
      55,    50,    51,    19,     0,    15,    25,    61,     0,    12,
       0,    16,     0,     0,    11,    22,     0,    20,    21,    13,
      17,    71,    66,    70,     0,     0,     0,    11,     0,     0,
       0,    26,    24,    74,    67,    68,    85,    64,    59,     0,
       0,    10,   155,   159,     0,   170,   172,   174,   176,    23,
     106,   123,   126,   128,   131,   145,   149,   154,   153,   161,
     162,    32,    28,     0,     0,    72,    69,     0,     0,     0,
       0,     0,     0,     0,    85,    87,    82,    85,    76,     0,
      75,    77,    79,    78,    80,    81,     0,    65,     9,   163,
       0,   127,   154,   171,   173,   175,   177,     0,   121,     0,
     124,   147,   146,   140,   142,   134,   138,   132,   136,   129,
       0,     0,   150,   151,   152,     0,   107,     0,     0,   117,
     113,   115,   109,   111,   119,   120,   105,   156,     0,    31,
      73,     0,   102,   101,     0,     0,     0,     0,   104,     0,
       0,    84,    62,    86,   166,     0,   123,   126,   141,   143,
     135,   139,   133,   137,   130,   144,   148,     0,     0,   158,
       0,     0,     0,     0,     0,    33,    32,    27,    29,    30,
       0,   103,     0,   100,    98,     0,     0,     0,     0,    83,
      63,   169,     0,   165,   160,   122,   125,   108,   157,   118,
     114,   116,   110,   112,    34,     0,     0,     0,     0,    99,
       0,     0,     0,   167,   164,     0,    90,    95,     0,     0,
       0,   169,    39,     0,     0,    88,     0,     0,     0,     0,
       0,    93,   168,     0,    37,    36,    89,    96,    97,     0,
       0,    91,    38,     0,    94,     0,     0,    92
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -240,  -240,   203,  -240,  -240,  -240,   151,     1,  -240,   -23,
    -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,    51,
    -240,  -240,  -240,  -240,   -44,  -240,     3,  -240,  -240,    81,
    -240,  -240,  -240,  -240,  -240,  -240,   147,  -240,  -240,  -240,
    -240,  -240,  -107,  -240,   -81,  -240,  -240,  -240,  -240,   -54,
    -240,  -240,  -240,  -240,  -239,   -69,  -240,  -240,  -240,  -240,
    -240,  -240,  -240,  -165,    39,    90,    43,   -82,  -240,  -240,
    -240,  -240,  -240,  -240,  -240,  -240,  -240,    76,  -240,    77,
    -240,    83,   -79,  -240,  -240,  -240,  -240,  -240,  -240,  -240,
     -27,  -240,  -240,  -240,  -240,  -240
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    11,    12,    13,    14,    44,    66,   116,    16,    36,
      51,    37,    46,    57,    69,    58,    72,   103,   207,   102,
     168,   234,   209,   235,   253,   264,    68,    30,    26,    21,
      18,    19,    47,    78,   220,   127,    53,    62,    75,    63,
      73,   105,   117,   118,   119,   120,   121,   255,   122,   260,
     123,   215,   124,   173,   125,   126,   166,   197,   203,   204,
     201,   202,   200,    90,   138,    91,   140,    92,    93,   149,
     150,   192,   190,   193,   191,   188,   189,    94,   151,    95,
     155,    96,    97,   167,    98,   130,    99,   184,   222,   223,
     243,   100,   133,   134,   135,   136
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      89,    15,   131,    17,   177,   132,   210,    34,    45,    82,
     212,   261,    48,    70,    15,   112,    17,    20,    23,    43,
     258,   259,    24,    25,    27,    31,    71,    60,    28,    29,
      82,   274,    55,   180,    32,    56,   181,   261,   157,   174,
     158,    52,   172,    76,    82,    77,    83,   152,   153,   154,
     238,    38,    84,    43,    35,    67,    45,   187,   132,    49,
     132,   185,    85,    86,    87,    88,    35,    83,    67,   141,
     142,   132,   132,    84,    50,   249,   132,    52,   -60,    54,
      59,    83,    61,    85,    86,    87,    88,    22,   198,    64,
     141,   142,   132,    74,    79,    80,   132,    85,    86,    87,
      88,   101,   128,   104,   129,    39,    40,   216,   156,    41,
      42,   157,   171,   158,   137,   221,   169,   170,   143,   144,
     145,   146,   147,   148,   139,   175,   176,   179,   227,   246,
     247,   229,   230,   231,   232,   233,   132,   178,   159,   160,
     161,   162,   163,   182,   199,   183,   205,   266,   211,   206,
     217,   218,   164,   165,   219,   224,   228,   -35,   236,   237,
     239,   132,   240,     1,     2,     3,     4,     5,     6,     7,
       8,     9,   241,   251,    10,   242,   244,   214,   245,   256,
      82,   107,     1,     2,     3,     4,     5,     6,     7,     8,
      65,   108,   248,    10,   109,   110,   111,   112,   250,   252,
     254,   113,   257,   263,   275,   265,   267,   268,   269,   271,
     270,   114,   112,   115,   273,   276,    33,    83,    81,   272,
     208,   106,   277,    84,   262,   225,   194,   186,   195,     0,
     226,     0,     0,    85,    86,    87,    88,    82,   196,     1,
       2,     3,     4,     5,     6,     7,     8,    65,     0,     0,
      10,     1,     2,     3,     4,     5,     6,     7,     8,    65,
       0,     0,    10,     0,     0,     0,     0,     0,     0,     0,
     213,     0,     0,     0,    83,     0,     0,     0,     0,     0,
      84,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      85,    86,    87,    88,     1,     2,     3,     4,     5,     6,
       7,     8,     0,     0,     0,    10
};

static const yytype_int16 yycheck[] =
{
      69,     0,    84,     0,   111,    84,   171,     3,    31,     3,
     175,   250,    35,    43,    13,    20,    13,     5,     5,     3,
      25,    26,     9,    10,     5,     3,    56,    50,     9,    10,
       3,   270,    39,   114,     0,    42,   117,   276,    42,   108,
      44,    38,    36,    34,     3,    36,    40,    50,    51,    52,
     215,    40,    46,     3,    50,    54,    79,   139,   137,    36,
     139,   130,    56,    57,    58,    59,    50,    40,    67,    48,
      49,   150,   151,    46,    37,   240,   155,    74,    40,    34,
      36,    40,     3,    56,    57,    58,    59,     6,   157,    41,
      48,    49,   171,    37,     3,    35,   175,    56,    57,    58,
      59,    39,    36,    42,    40,    24,    25,   176,    39,    28,
      29,    42,    40,    44,    74,   184,    43,    43,    76,    77,
      78,    79,    80,    81,    75,    40,    40,    40,   197,   236,
     237,   200,   201,   202,   203,   204,   215,    36,    69,    70,
      71,    72,    73,    35,     3,    36,    57,   254,    36,    39,
      17,     3,    83,    84,    35,    41,    43,    34,    41,    41,
      36,   240,    40,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    41,   242,    16,    37,    41,   176,    34,   248,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    36,    16,    17,    18,    19,    20,    34,    56,
      68,    24,    41,    37,   273,    35,    41,    36,    56,    35,
      38,    34,    20,    36,    38,    36,    13,    40,    67,   263,
     169,    74,   276,    46,   251,   186,   150,   137,   151,    -1,
     187,    -1,    -1,    56,    57,    58,    59,     3,   155,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      16,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,     5,     6,     7,     8,     9,    10,
      11,    12,    -1,    -1,    -1,    16
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      16,    86,    87,    88,    89,    92,    93,   111,   115,   116,
       5,   114,   114,     5,     9,    10,   113,     5,     9,    10,
     112,     3,     0,    87,     3,    50,    94,    96,    40,   114,
     114,   114,   114,     3,    90,    94,    97,   117,    94,    36,
      37,    95,   111,   121,    34,    39,    42,    98,   100,    36,
      94,     3,   122,   124,    41,    13,    91,    92,   111,    99,
      43,    56,   101,   125,    37,   123,    34,    36,   118,     3,
      35,    91,     3,    40,    46,    56,    57,    58,    59,   140,
     148,   150,   152,   153,   162,   164,   166,   167,   169,   171,
     176,    39,   104,   102,    42,   126,   121,     4,    14,    17,
      18,    19,    20,    24,    34,    36,    92,   127,   128,   129,
     130,   131,   133,   135,   137,   139,   140,   120,    36,    40,
     170,   152,   167,   177,   178,   179,   180,    74,   149,    75,
     151,    48,    49,    76,    77,    78,    79,    80,    81,   154,
     155,   163,    50,    51,    52,   165,    39,    42,    44,    69,
      70,    71,    72,    73,    83,    84,   141,   168,   105,    43,
      43,    40,    36,   138,   140,    40,    40,   127,    36,    40,
     129,   129,    35,    36,   172,   140,   150,   152,   160,   161,
     157,   159,   156,   158,   162,   164,   166,   142,   140,     3,
     147,   145,   146,   143,   144,    57,    39,   103,   104,   107,
     148,    36,   148,    36,    92,   136,   140,    17,     3,    35,
     119,   140,   173,   174,    41,   149,   151,   140,    43,   140,
     140,   140,   140,   140,   106,   108,    41,    41,   148,    36,
      40,    41,    37,   175,    41,    34,   127,   127,    36,   148,
      34,   140,    56,   109,    68,   132,   140,    41,    25,    26,
     134,   139,   175,    37,   110,    35,   127,    41,    36,    56,
      38,    35,   109,    38,   139,   140,    36,   134
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    87,    87,    88,    88,    88,    90,    89,
      91,    91,    92,    92,    92,    93,    94,    95,    95,    97,
      96,    98,    99,    98,   100,   100,   102,   101,   101,   103,
     103,   103,   105,   106,   104,   108,   107,   109,   110,   110,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   112,
     112,   112,   112,   113,   113,   113,   113,   114,   114,   115,
     117,   116,   119,   118,   120,   118,   121,   121,   122,   123,
     123,   125,   124,   126,   126,   127,   127,   127,   127,   127,
     127,   127,   127,   128,   129,   129,   130,   130,   131,   132,
     132,   133,   134,   134,   134,   135,   135,   135,   136,   136,
     136,   137,   138,   138,   139,   140,   140,   142,   141,   143,
     141,   144,   141,   145,   141,   146,   141,   147,   141,   141,
     141,   148,   149,   149,   150,   151,   151,   152,   152,   153,
     154,   154,   156,   155,   157,   155,   158,   155,   159,   155,
     160,   155,   161,   155,   162,   162,   163,   163,   164,   164,
     165,   165,   165,   166,   166,   167,   167,   168,   168,   170,
     169,   169,   169,   172,   171,   173,   173,   174,   175,   175,
     177,   176,   178,   176,   179,   176,   180,   176
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     1,     0,     7,
       2,     0,     3,     4,     1,     3,     2,     2,     0,     0,
       3,     1,     0,     3,     2,     0,     0,     4,     2,     1,
       1,     0,     0,     0,     4,     0,     5,     2,     2,     0,
       1,     1,     1,     1,     2,     2,     2,     2,     1,     1,
       2,     2,     0,     1,     2,     2,     0,     1,     0,     5,
       0,     3,     0,     4,     0,     2,     2,     0,     2,     2,
       0,     0,     3,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     0,     2,     1,     6,     2,
       0,     7,     6,     1,     3,     5,     7,     7,     1,     2,
       1,     2,     1,     2,     2,     2,     1,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     3,     0,     3,     1,
       1,     2,     3,     0,     2,     3,     0,     2,     1,     2,
       2,     0,     0,     2,     0,     2,     0,     2,     0,     2,
       0,     2,     0,     2,     3,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     2,     0,
       4,     1,     1,     0,     5,     1,     0,     2,     3,     0,
       0,     2,     0,     2,     0,     2,     0,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* state: declarations  */
#line 210 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "state");
                        	head=(yyval.nd_obj).nd;
                        }
#line 1860 "y.tab.c"
    break;

  case 3: /* declarations: declaration declarations  */
#line 218 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "declarations");
                        }
#line 1868 "y.tab.c"
    break;

  case 4: /* declarations: %empty  */
#line 222 "final_parser.y"
                        {
	     			(yyval.nd_obj).nd = NULL; 
	     		}
#line 1876 "y.tab.c"
    break;

  case 5: /* declaration: variable_dec  */
#line 229 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "declaration");
                        }
#line 1884 "y.tab.c"
    break;

  case 6: /* declaration: function_dec  */
#line 233 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "declaration");
                        }
#line 1892 "y.tab.c"
    break;

  case 7: /* declaration: structure_dec  */
#line 237 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "declaration");
                        }
#line 1900 "y.tab.c"
    break;

  case 8: /* $@1: %empty  */
#line 243 "final_parser.y"
                                            {insert_type(); insert_class(0);}
#line 1906 "y.tab.c"
    break;

  case 9: /* structure_dec: STRUCT IDENTIFIER $@1 OPEN_CURLY structure_content CLOSE_CURLY SEMI_COLON  */
#line 244 "final_parser.y"
                        {
                        	(yyvsp[-6].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "STRUCT");
                        	(yyvsp[-5].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IDENTIFIER");
                        	(yyvsp[-3].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_CURLY");
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_CURLY");
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-6].nd_obj).nd, (yyvsp[-5].nd_obj).nd, (yyvsp[-3].nd_obj).nd, (yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, "structure_dec");
                        }
#line 1919 "y.tab.c"
    break;

  case 10: /* structure_content: variable_dec structure_content  */
#line 255 "final_parser.y"
                  {
		  	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd,(yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "structure_content");
		  }
#line 1927 "y.tab.c"
    break;

  case 11: /* structure_content: %empty  */
#line 259 "final_parser.y"
                  {
	     		(yyval.nd_obj).nd = NULL; 
	     	  }
#line 1935 "y.tab.c"
    break;

  case 12: /* variable_dec: datatype variables SEMI_COLON  */
#line 266 "final_parser.y"
                        {
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd,(yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, "variable_dec");
                        }
#line 1944 "y.tab.c"
    break;

  case 13: /* variable_dec: datatype MULTIPLY variables SEMI_COLON  */
#line 271 "final_parser.y"
                        {
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "MULTIPLY");
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-3].nd_obj).nd,(yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, "variable_dec");
                        }
#line 1954 "y.tab.c"
    break;

  case 14: /* variable_dec: structure_initialize  */
#line 277 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "variable_dec");
                        }
#line 1962 "y.tab.c"
    break;

  case 15: /* structure_initialize: STRUCT IDENTIFIER variables  */
#line 284 "final_parser.y"
                        {
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "STRUCT");
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IDENTIFIER");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, "structure_dec");
                        }
#line 1972 "y.tab.c"
    break;

  case 16: /* variables: identifier_name multiple_variables  */
#line 293 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "variable_dec");
                        }
#line 1980 "y.tab.c"
    break;

  case 17: /* multiple_variables: COMMA variables  */
#line 300 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "COMMA");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "multiple_variables");
                        }
#line 1989 "y.tab.c"
    break;

  case 18: /* multiple_variables: %empty  */
#line 305 "final_parser.y"
                        {
	     			(yyval.nd_obj).nd = NULL; 
	     	  	}
#line 1997 "y.tab.c"
    break;

  case 19: /* $@2: %empty  */
#line 311 "final_parser.y"
                                     {insert_type(); insert_class(2);}
#line 2003 "y.tab.c"
    break;

  case 20: /* identifier_name: IDENTIFIER $@2 extended_identifier  */
#line 312 "final_parser.y"
                        {
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IDENTIFIER");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "identifier_name");
                        }
#line 2012 "y.tab.c"
    break;

  case 21: /* extended_identifier: array_identifier  */
#line 319 "final_parser.y"
                    {
		    	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "extended_identifier");
		    }
#line 2020 "y.tab.c"
    break;

  case 22: /* $@3: %empty  */
#line 322 "final_parser.y"
                             {strcpy(previous_operator,"=");}
#line 2026 "y.tab.c"
    break;

  case 23: /* extended_identifier: EQUALS $@3 expression  */
#line 323 "final_parser.y"
                    {
	            	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "EQUALS");
	            	(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "extended_identifier");
	            }
#line 2035 "y.tab.c"
    break;

  case 24: /* array_identifier: OPEN_SQR array_dims  */
#line 331 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_SQR");
	            		(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "array_identifier");
                        }
#line 2044 "y.tab.c"
    break;

  case 25: /* array_identifier: %empty  */
#line 336 "final_parser.y"
                        {
	     			(yyval.nd_obj).nd = NULL; 
	     	  	}
#line 2052 "y.tab.c"
    break;

  case 26: /* $@4: %empty  */
#line 342 "final_parser.y"
                                           {insert_dimensions();}
#line 2058 "y.tab.c"
    break;

  case 27: /* array_dims: integer_constant $@4 CLOSE_SQR initilization  */
#line 343 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_SQR");
	            		(yyval.nd_obj).nd=mknode((yyvsp[-3].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, "array_dims");
                        }
#line 2067 "y.tab.c"
    break;

  case 28: /* array_dims: CLOSE_SQR string_initilization  */
#line 348 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_SQR");
	            		(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "array_dims");
                        }
#line 2076 "y.tab.c"
    break;

  case 29: /* initilization: string_initilization  */
#line 356 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "initialization");
                        }
#line 2084 "y.tab.c"
    break;

  case 30: /* initilization: array_initialization  */
#line 360 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "initialization");
                        }
#line 2092 "y.tab.c"
    break;

  case 31: /* initilization: %empty  */
#line 364 "final_parser.y"
                        {
	     			(yyval.nd_obj).nd = NULL; 
	     	  	}
#line 2100 "y.tab.c"
    break;

  case 32: /* $@5: %empty  */
#line 370 "final_parser.y"
                                 {strcpy(previous_operator,"=");}
#line 2106 "y.tab.c"
    break;

  case 33: /* $@6: %empty  */
#line 370 "final_parser.y"
                                                                                  {insert_value();}
#line 2112 "y.tab.c"
    break;

  case 34: /* string_initilization: EQUALS $@5 string_constant $@6  */
#line 371 "final_parser.y"
                        {
                        	(yyvsp[-3].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "EQUALS");
	            		(yyval.nd_obj).nd=mknode((yyvsp[-3].nd_obj).nd, (yyvsp[-1].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "string_initialization");
                        }
#line 2121 "y.tab.c"
    break;

  case 35: /* $@7: %empty  */
#line 378 "final_parser.y"
                                 {strcpy(previous_operator,"=");}
#line 2127 "y.tab.c"
    break;

  case 36: /* array_initialization: EQUALS $@7 OPEN_CURLY array_values CLOSE_CURLY  */
#line 379 "final_parser.y"
                        {
                        	(yyvsp[-4].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "EQUALS");
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_CURLY");
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_CURLY");
	            		(yyval.nd_obj).nd=mknode((yyvsp[-4].nd_obj).nd, (yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, "array_initialization");
                        }
#line 2138 "y.tab.c"
    break;

  case 37: /* array_values: integer_constant multiple_array_values  */
#line 389 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "array_values");
                        }
#line 2146 "y.tab.c"
    break;

  case 38: /* multiple_array_values: COMMA array_values  */
#line 396 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "COMMA");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "multiple_array_values");
                        }
#line 2155 "y.tab.c"
    break;

  case 39: /* multiple_array_values: %empty  */
#line 401 "final_parser.y"
                        {
	     			(yyval.nd_obj).nd = NULL; 
	     	  	}
#line 2163 "y.tab.c"
    break;

  case 40: /* datatype: INT  */
#line 409 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "INT");
                        }
#line 2171 "y.tab.c"
    break;

  case 41: /* datatype: CHAR  */
#line 413 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CHAR");
                        }
#line 2179 "y.tab.c"
    break;

  case 42: /* datatype: FLOAT  */
#line 417 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "FLOAT");
                        }
#line 2187 "y.tab.c"
    break;

  case 43: /* datatype: DOUBLE  */
#line 421 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "DOUBLE");
                        }
#line 2195 "y.tab.c"
    break;

  case 44: /* datatype: LONG long_grammar  */
#line 425 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "LONG");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "datatype");
                        }
#line 2204 "y.tab.c"
    break;

  case 45: /* datatype: SHORT long_grammar  */
#line 430 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SHORT");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "datatype");
                        }
#line 2213 "y.tab.c"
    break;

  case 46: /* datatype: UNSIGNED unsigned_grammar  */
#line 435 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "UNSIGNED");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "datatype");
                        }
#line 2222 "y.tab.c"
    break;

  case 47: /* datatype: SIGNED signed_grammar  */
#line 440 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SIGNED");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "datatype");
                        }
#line 2231 "y.tab.c"
    break;

  case 48: /* datatype: VOID  */
#line 445 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "VOID");
                        }
#line 2239 "y.tab.c"
    break;

  case 49: /* unsigned_grammar: INT  */
#line 452 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "INT");
                        }
#line 2247 "y.tab.c"
    break;

  case 50: /* unsigned_grammar: LONG long_grammar  */
#line 456 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "LONG");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "unsigned_grammar");
                        }
#line 2256 "y.tab.c"
    break;

  case 51: /* unsigned_grammar: SHORT long_grammar  */
#line 461 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SHORT");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "unsigned_grammar");
                        }
#line 2265 "y.tab.c"
    break;

  case 52: /* unsigned_grammar: %empty  */
#line 466 "final_parser.y"
                        {
	     			(yyval.nd_obj).nd = NULL; 
	     	  	}
#line 2273 "y.tab.c"
    break;

  case 53: /* signed_grammar: INT  */
#line 473 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "INT");
                        }
#line 2281 "y.tab.c"
    break;

  case 54: /* signed_grammar: LONG long_grammar  */
#line 477 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "LONG");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "signed_grammar");	
                        }
#line 2290 "y.tab.c"
    break;

  case 55: /* signed_grammar: SHORT long_grammar  */
#line 482 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SHORT");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "signed_grammar");
                        }
#line 2299 "y.tab.c"
    break;

  case 56: /* signed_grammar: %empty  */
#line 487 "final_parser.y"
                        {
	     			(yyval.nd_obj).nd = NULL; 
	     	  	}
#line 2307 "y.tab.c"
    break;

  case 57: /* long_grammar: INT  */
#line 494 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "INT");
                        }
#line 2315 "y.tab.c"
    break;

  case 58: /* long_grammar: %empty  */
#line 498 "final_parser.y"
                        {
	     			(yyval.nd_obj).nd = NULL; 
	     	  	}
#line 2323 "y.tab.c"
    break;

  case 59: /* function_dec: function_name OPEN_BRACE parameters CLOSE_BRACE function_data  */
#line 506 "final_parser.y"
            {
            	(yyvsp[-3].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_BRACE");
            	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_BRACE");
            	(yyval.nd_obj).nd=mknode((yyvsp[-4].nd_obj).nd, (yyvsp[-3].nd_obj).nd, (yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, "function_dec");
            }
#line 2333 "y.tab.c"
    break;

  case 60: /* $@8: %empty  */
#line 513 "final_parser.y"
                                    {strcpy(current_function,current_identifier);insert_class(1);}
#line 2339 "y.tab.c"
    break;

  case 61: /* function_name: datatype IDENTIFIER $@8  */
#line 514 "final_parser.y"
              {
	      		(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IDENTIFIER");
	      		(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "function_name");
	      }
#line 2348 "y.tab.c"
    break;

  case 62: /* $@9: %empty  */
#line 520 "final_parser.y"
                                                  {insert_pdl(0);}
#line 2354 "y.tab.c"
    break;

  case 63: /* function_data: OPEN_CURLY statments CLOSE_CURLY $@9  */
#line 521 "final_parser.y"
             {	
	     	(yyvsp[-3].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_CURLY");
            	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_CURLY");
            	(yyval.nd_obj).nd=mknode((yyvsp[-3].nd_obj).nd, (yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, NULL, NULL, NULL, NULL, "function_data");
	     }
#line 2364 "y.tab.c"
    break;

  case 64: /* $@10: %empty  */
#line 526 "final_parser.y"
                          {insert_pdl(1);}
#line 2370 "y.tab.c"
    break;

  case 65: /* function_data: SEMI_COLON $@10  */
#line 527 "final_parser.y"
             {
             	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
             	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "function_data");
             }
#line 2379 "y.tab.c"
    break;

  case 66: /* parameters: datatype all_parameter_identifiers  */
#line 535 "final_parser.y"
            {
            	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "parameters");
            }
#line 2387 "y.tab.c"
    break;

  case 67: /* parameters: %empty  */
#line 539 "final_parser.y"
            {
	     	(yyval.nd_obj).nd = NULL; 
	    }
#line 2395 "y.tab.c"
    break;

  case 68: /* all_parameter_identifiers: parameter_identifier multiple_parameters  */
#line 547 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "all_parameter_identifiers");
                        }
#line 2403 "y.tab.c"
    break;

  case 69: /* multiple_parameters: COMMA parameters  */
#line 554 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "COMMA");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "multiple_parameters");
                        }
#line 2412 "y.tab.c"
    break;

  case 70: /* multiple_parameters: %empty  */
#line 559 "final_parser.y"
                        {
	     			(yyval.nd_obj).nd = NULL; 
	     	  	}
#line 2420 "y.tab.c"
    break;

  case 71: /* $@11: %empty  */
#line 565 "final_parser.y"
                                     {insert_parameters(); insert_type();}
#line 2426 "y.tab.c"
    break;

  case 72: /* parameter_identifier: IDENTIFIER $@11 extended_parameter  */
#line 566 "final_parser.y"
                        {
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IDENTIFIER");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "parameter_identifier");
                        }
#line 2435 "y.tab.c"
    break;

  case 73: /* extended_parameter: OPEN_SQR CLOSE_SQR  */
#line 574 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_SQR");
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_SQR");
	            		(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "extended_parameter");
                        }
#line 2445 "y.tab.c"
    break;

  case 74: /* extended_parameter: %empty  */
#line 580 "final_parser.y"
                        {
	     			(yyval.nd_obj).nd = NULL; 
	     	  	}
#line 2453 "y.tab.c"
    break;

  case 75: /* statement: expression_statment  */
#line 587 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "statment");
                        }
#line 2461 "y.tab.c"
    break;

  case 76: /* statement: multiple_statement  */
#line 591 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "statment");
                        }
#line 2469 "y.tab.c"
    break;

  case 77: /* statement: conditional_statements  */
#line 595 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "statment");
                        }
#line 2477 "y.tab.c"
    break;

  case 78: /* statement: iterative_statements  */
#line 599 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "statment");
                        }
#line 2485 "y.tab.c"
    break;

  case 79: /* statement: switch_statement  */
#line 603 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "statment");
                        }
#line 2493 "y.tab.c"
    break;

  case 80: /* statement: return_statement  */
#line 607 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "statment");
                        }
#line 2501 "y.tab.c"
    break;

  case 81: /* statement: break_statement  */
#line 611 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "statment");
                        }
#line 2509 "y.tab.c"
    break;

  case 82: /* statement: variable_dec  */
#line 615 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "statment");
                        }
#line 2517 "y.tab.c"
    break;

  case 83: /* multiple_statement: OPEN_CURLY statments CLOSE_CURLY  */
#line 622 "final_parser.y"
                        {
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_CURLY");
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_CURLY");
	            		(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, "multiple_statement");
                        }
#line 2527 "y.tab.c"
    break;

  case 84: /* statments: statement statments  */
#line 631 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "statments");
                        }
#line 2535 "y.tab.c"
    break;

  case 85: /* statments: %empty  */
#line 635 "final_parser.y"
                        {
	     			(yyval.nd_obj).nd = NULL; 
	     	  	}
#line 2543 "y.tab.c"
    break;

  case 86: /* expression_statment: expression SEMI_COLON  */
#line 642 "final_parser.y"
                        {
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "expression_statment");
                        }
#line 2552 "y.tab.c"
    break;

  case 87: /* expression_statment: SEMI_COLON  */
#line 647 "final_parser.y"
                        {
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "expression_statment");
                        }
#line 2561 "y.tab.c"
    break;

  case 88: /* conditional_statements: IF OPEN_BRACE simple_expression CLOSE_BRACE statement extended_conditional_statements  */
#line 655 "final_parser.y"
                        {
                        	(yyvsp[-5].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IF");
                        	(yyvsp[-4].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_BRACE");
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_BRACE");
	            		(yyval.nd_obj).nd=mknode((yyvsp[-5].nd_obj).nd, (yyvsp[-4].nd_obj).nd, (yyvsp[-3].nd_obj).nd, (yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, "conditional_statements");
                        }
#line 2572 "y.tab.c"
    break;

  case 89: /* extended_conditional_statements: ELSE statement  */
#line 665 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "ELSE");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "extended_conditional_statements");
                        }
#line 2581 "y.tab.c"
    break;

  case 90: /* extended_conditional_statements: %empty  */
#line 670 "final_parser.y"
                        {
	     			(yyval.nd_obj).nd = NULL; 
	     	  	}
#line 2589 "y.tab.c"
    break;

  case 91: /* switch_statement: SWITCH OPEN_BRACE IDENTIFIER CLOSE_BRACE OPEN_CURLY extended_switch_statement CLOSE_CURLY  */
#line 676 "final_parser.y"
                        {
				(yyvsp[-6].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SWITCH");
                        	(yyvsp[-5].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_BRACE");
                        	(yyvsp[-4].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IDENTIFIER");
                        	(yyvsp[-3].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_BRACE");
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_CURLY");
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_CURLY");
	            		(yyval.nd_obj).nd=mknode((yyvsp[-6].nd_obj).nd, (yyvsp[-5].nd_obj).nd, (yyvsp[-4].nd_obj).nd, (yyvsp[-3].nd_obj).nd, (yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, "switch_statement");
			}
#line 2603 "y.tab.c"
    break;

  case 92: /* extended_switch_statement: CASE integer_constant COLON expression SEMI_COLON extended_switch_statement  */
#line 689 "final_parser.y"
                        {
                        	(yyvsp[-5].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CASE");
                        	(yyvsp[-3].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "COLON");
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
	            		(yyval.nd_obj).nd=mknode((yyvsp[-5].nd_obj).nd, (yyvsp[-4].nd_obj).nd, (yyvsp[-3].nd_obj).nd, (yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, "extended_switch_statement");
                        }
#line 2614 "y.tab.c"
    break;

  case 93: /* extended_switch_statement: break_statement  */
#line 696 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "extended_switch_statement");
                        }
#line 2622 "y.tab.c"
    break;

  case 94: /* extended_switch_statement: DEFAULT COLON break_statement  */
#line 700 "final_parser.y"
                        {
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "DEFAULT");
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "COLON");
	            		(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, "extended_switch_statement");
                        }
#line 2632 "y.tab.c"
    break;

  case 95: /* iterative_statements: WHILE OPEN_BRACE simple_expression CLOSE_BRACE statement  */
#line 709 "final_parser.y"
                        {
                        	(yyvsp[-4].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "WHILE");
                        	(yyvsp[-3].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_BRACE");
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_BRACE");
	            		(yyval.nd_obj).nd=mknode((yyvsp[-4].nd_obj).nd, (yyvsp[-3].nd_obj).nd, (yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, "iterative_statements");	
                        }
#line 2643 "y.tab.c"
    break;

  case 96: /* iterative_statements: FOR OPEN_BRACE for_initialization simple_expression SEMI_COLON expression CLOSE_BRACE  */
#line 716 "final_parser.y"
                        {
                        	(yyvsp[-6].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "FOR");
                        	(yyvsp[-5].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_BRACE");
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_BRACE");
	            		(yyval.nd_obj).nd=mknode((yyvsp[-6].nd_obj).nd, (yyvsp[-5].nd_obj).nd, (yyvsp[-4].nd_obj).nd, (yyvsp[-3].nd_obj).nd, (yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, "iterative_statements");	
                        }
#line 2655 "y.tab.c"
    break;

  case 97: /* iterative_statements: DO statement WHILE OPEN_BRACE simple_expression CLOSE_BRACE SEMI_COLON  */
#line 724 "final_parser.y"
                        {
                        	(yyvsp[-6].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "DO");
                        	(yyvsp[-4].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "WHILE");
                        	(yyvsp[-3].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_BRACE");
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_BRACE");
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
	            		(yyval.nd_obj).nd=mknode((yyvsp[-6].nd_obj).nd, (yyvsp[-5].nd_obj).nd, (yyvsp[-4].nd_obj).nd, (yyvsp[-3].nd_obj).nd, (yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, "iterative_statements");
                        }
#line 2668 "y.tab.c"
    break;

  case 98: /* for_initialization: variable_dec  */
#line 736 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "for_initialization");
                        }
#line 2676 "y.tab.c"
    break;

  case 99: /* for_initialization: expression SEMI_COLON  */
#line 740 "final_parser.y"
                        {
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "for_initialization");
                        }
#line 2685 "y.tab.c"
    break;

  case 100: /* for_initialization: SEMI_COLON  */
#line 745 "final_parser.y"
                        {
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "for_initialization");
                        }
#line 2694 "y.tab.c"
    break;

  case 101: /* return_statement: RETURN return_suffix  */
#line 753 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "RETURN");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "return statement");
                        }
#line 2703 "y.tab.c"
    break;

  case 102: /* return_suffix: SEMI_COLON  */
#line 761 "final_parser.y"
                        {
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "return_suffix");
                        }
#line 2712 "y.tab.c"
    break;

  case 103: /* return_suffix: expression SEMI_COLON  */
#line 766 "final_parser.y"
                        {
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "return_suffix");
                        }
#line 2721 "y.tab.c"
    break;

  case 104: /* break_statement: BREAK SEMI_COLON  */
#line 774 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "BREAK");
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "break_statement");
                        }
#line 2731 "y.tab.c"
    break;

  case 105: /* expression: iden expressions  */
#line 783 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "expression");
                        }
#line 2739 "y.tab.c"
    break;

  case 106: /* expression: simple_expression  */
#line 787 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "expression");
                        }
#line 2747 "y.tab.c"
    break;

  case 107: /* $@12: %empty  */
#line 793 "final_parser.y"
                                 {strcpy(previous_operator,"=");}
#line 2753 "y.tab.c"
    break;

  case 108: /* expressions: EQUALS $@12 expression  */
#line 794 "final_parser.y"
                        {
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "EQUALS");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "expressions");
                        }
#line 2762 "y.tab.c"
    break;

  case 109: /* $@13: %empty  */
#line 798 "final_parser.y"
                                   {strcpy(previous_operator,"+=");}
#line 2768 "y.tab.c"
    break;

  case 110: /* expressions: ADD_EQUAL $@13 expression  */
#line 799 "final_parser.y"
                        {
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "ADD_EQUAL");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "expressions");
                        }
#line 2777 "y.tab.c"
    break;

  case 111: /* $@14: %empty  */
#line 803 "final_parser.y"
                                   {strcpy(previous_operator,"-=");}
#line 2783 "y.tab.c"
    break;

  case 112: /* expressions: SUB_EQUAL $@14 expression  */
#line 804 "final_parser.y"
                        {
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SUB_EQUAL");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "expressions");
                        }
#line 2792 "y.tab.c"
    break;

  case 113: /* $@15: %empty  */
#line 808 "final_parser.y"
                                   {strcpy(previous_operator,"*=");}
#line 2798 "y.tab.c"
    break;

  case 114: /* expressions: MUL_EQUAL $@15 expression  */
#line 809 "final_parser.y"
                        {
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "MUL_EQUAL");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "expressions");
                        }
#line 2807 "y.tab.c"
    break;

  case 115: /* $@16: %empty  */
#line 813 "final_parser.y"
                                   {strcpy(previous_operator,"/=");}
#line 2813 "y.tab.c"
    break;

  case 116: /* expressions: DIV_EQUAL $@16 expression  */
#line 814 "final_parser.y"
                        {
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "DIV_EQUAL");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "expressions");
                        }
#line 2822 "y.tab.c"
    break;

  case 117: /* $@17: %empty  */
#line 818 "final_parser.y"
                                   {strcpy(previous_operator,"%=");}
#line 2828 "y.tab.c"
    break;

  case 118: /* expressions: MOD_EQUAL $@17 expression  */
#line 819 "final_parser.y"
                        {
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "MOD_EQUAL");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "expressions");
                        }
#line 2837 "y.tab.c"
    break;

  case 119: /* expressions: INCREMENT  */
#line 824 "final_parser.y"
                        {
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "INCREMENT");
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "expressions");	
                        }
#line 2846 "y.tab.c"
    break;

  case 120: /* expressions: DECREMENT  */
#line 829 "final_parser.y"
                        {
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "DECREMENT");
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "expressions");	
                        }
#line 2855 "y.tab.c"
    break;

  case 121: /* simple_expression: and_expression simple_expression_breakup  */
#line 837 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "simple_expression");
                        }
#line 2863 "y.tab.c"
    break;

  case 122: /* simple_expression_breakup: OR_OP and_expression simple_expression_breakup  */
#line 844 "final_parser.y"
                        {
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OR_OP");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, "simple_expression_breakup");	
                        }
#line 2872 "y.tab.c"
    break;

  case 123: /* simple_expression_breakup: %empty  */
#line 849 "final_parser.y"
                        {
	     			(yyval.nd_obj).nd = NULL; 
	     	  	}
#line 2880 "y.tab.c"
    break;

  case 124: /* and_expression: unary_relation_expression and_expression_breakup  */
#line 856 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "and_expression");
                        }
#line 2888 "y.tab.c"
    break;

  case 125: /* and_expression_breakup: AND_OP unary_relation_expression and_expression_breakup  */
#line 863 "final_parser.y"
                        {
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "AND_OP");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, "and_expression_breakup");	
                        }
#line 2897 "y.tab.c"
    break;

  case 126: /* and_expression_breakup: %empty  */
#line 868 "final_parser.y"
                        {
	     			(yyval.nd_obj).nd = NULL; 
	     	  	}
#line 2905 "y.tab.c"
    break;

  case 127: /* unary_relation_expression: NOT unary_relation_expression  */
#line 875 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "NOT");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "unary_relation_expression");	
                        }
#line 2914 "y.tab.c"
    break;

  case 128: /* unary_relation_expression: regular_expression  */
#line 880 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "unary_relation_expression");
                        }
#line 2922 "y.tab.c"
    break;

  case 129: /* regular_expression: sum_expression regular_expression_breakup  */
#line 887 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "regular_expression");
                        }
#line 2930 "y.tab.c"
    break;

  case 130: /* regular_expression_breakup: relational_operators sum_expression  */
#line 894 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "regular_expression_breakup");
                        }
#line 2938 "y.tab.c"
    break;

  case 131: /* regular_expression_breakup: %empty  */
#line 898 "final_parser.y"
                        {
	     			(yyval.nd_obj).nd = NULL; 
	     	  	}
#line 2946 "y.tab.c"
    break;

  case 132: /* $@18: %empty  */
#line 904 "final_parser.y"
                                       {strcpy(previous_operator,">=");}
#line 2952 "y.tab.c"
    break;

  case 133: /* relational_operators: GREATER_EQUAL $@18  */
#line 905 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "GREATER_EQUAL");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "relational_operators");	
                        }
#line 2961 "y.tab.c"
    break;

  case 134: /* $@19: %empty  */
#line 909 "final_parser.y"
                                      {strcpy(previous_operator,"<=");}
#line 2967 "y.tab.c"
    break;

  case 135: /* relational_operators: LESSER_EQUAL $@19  */
#line 910 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "LESSER_EQUAL");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "relational_operators");	
                        }
#line 2976 "y.tab.c"
    break;

  case 136: /* $@20: %empty  */
#line 914 "final_parser.y"
                                 {strcpy(previous_operator,">");}
#line 2982 "y.tab.c"
    break;

  case 137: /* relational_operators: GREATER $@20  */
#line 915 "final_parser.y"
                        {
				(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "GREATER");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "relational_operators");	
                        }
#line 2991 "y.tab.c"
    break;

  case 138: /* $@21: %empty  */
#line 919 "final_parser.y"
                                {strcpy(previous_operator,"<");}
#line 2997 "y.tab.c"
    break;

  case 139: /* relational_operators: LESSER $@21  */
#line 920 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "LESSER");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "relational_operators");	
                        }
#line 3006 "y.tab.c"
    break;

  case 140: /* $@22: %empty  */
#line 924 "final_parser.y"
                               {strcpy(previous_operator,"==");}
#line 3012 "y.tab.c"
    break;

  case 141: /* relational_operators: EQUAL $@22  */
#line 925 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "EQUAL");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "relational_operators");	
                        }
#line 3021 "y.tab.c"
    break;

  case 142: /* $@23: %empty  */
#line 929 "final_parser.y"
                                   {strcpy(previous_operator,"!=");}
#line 3027 "y.tab.c"
    break;

  case 143: /* relational_operators: NOT_EQUAL $@23  */
#line 930 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "NOT_EQUAL");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "relational_operators");	
                        }
#line 3036 "y.tab.c"
    break;

  case 144: /* sum_expression: sum_expression sum_operators term  */
#line 938 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, "sum_expression");
                        }
#line 3044 "y.tab.c"
    break;

  case 145: /* sum_expression: term  */
#line 942 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "sum_expression");
                        }
#line 3052 "y.tab.c"
    break;

  case 146: /* sum_operators: PLUS  */
#line 949 "final_parser.y"
                        {
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "PLUS");
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "sum_operators");	
                        }
#line 3061 "y.tab.c"
    break;

  case 147: /* sum_operators: HYPHEN  */
#line 954 "final_parser.y"
                        {
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "HYPHEN");
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "sum_operators");	
                        }
#line 3070 "y.tab.c"
    break;

  case 148: /* term: term multiply_operators factor  */
#line 962 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, "term");	
                        }
#line 3078 "y.tab.c"
    break;

  case 149: /* term: factor  */
#line 966 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "term");	
                        }
#line 3086 "y.tab.c"
    break;

  case 150: /* multiply_operators: MULTIPLY  */
#line 973 "final_parser.y"
                        {
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "MULTIPLY");
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "multiply_operators");	
                        }
#line 3095 "y.tab.c"
    break;

  case 151: /* multiply_operators: DIVIDE  */
#line 978 "final_parser.y"
                        {
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "DIVIDE");
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "multiply_operators");	
                        }
#line 3104 "y.tab.c"
    break;

  case 152: /* multiply_operators: PERCENT  */
#line 983 "final_parser.y"
                        {
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "PERCENT");
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "multiply_operators");	
                        }
#line 3113 "y.tab.c"
    break;

  case 153: /* factor: func  */
#line 991 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "factor");	
                        }
#line 3121 "y.tab.c"
    break;

  case 154: /* factor: iden  */
#line 995 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "factor");	
                        }
#line 3129 "y.tab.c"
    break;

  case 155: /* iden: IDENTIFIER  */
#line 1002 "final_parser.y"
                        {
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IDENTIFIER");
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "iden");	
                        }
#line 3138 "y.tab.c"
    break;

  case 156: /* iden: iden extended_iden  */
#line 1007 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "iden");
                        }
#line 3146 "y.tab.c"
    break;

  case 157: /* extended_iden: OPEN_SQR expression CLOSE_SQR  */
#line 1014 "final_parser.y"
                        {
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_SQR");
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_SQR");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, "extended_iden");
                        }
#line 3156 "y.tab.c"
    break;

  case 158: /* extended_iden: DOT IDENTIFIER  */
#line 1020 "final_parser.y"
                        {
                        	(yyvsp[-1].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "DOT");
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IDENTIFIER");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "extended_iden");
                        }
#line 3166 "y.tab.c"
    break;

  case 159: /* $@24: %empty  */
#line 1028 "final_parser.y"
                                     {strcpy(previous_operator,"(");}
#line 3172 "y.tab.c"
    break;

  case 160: /* func: OPEN_BRACE $@24 expression CLOSE_BRACE  */
#line 1029 "final_parser.y"
                        {
                        	(yyvsp[-3].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_BRACE");
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_BRACE");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-3].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, "func_call");
                        }
#line 3182 "y.tab.c"
    break;

  case 161: /* func: func_call  */
#line 1035 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "func");	
                        }
#line 3190 "y.tab.c"
    break;

  case 162: /* func: constant  */
#line 1039 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "func");
                        }
#line 3198 "y.tab.c"
    break;

  case 163: /* $@25: %empty  */
#line 1045 "final_parser.y"
                                                {strcpy(previous_operator,"(");insert_class(1);}
#line 3204 "y.tab.c"
    break;

  case 164: /* func_call: IDENTIFIER OPEN_BRACE $@25 arguments CLOSE_BRACE  */
#line 1046 "final_parser.y"
                        {
                        	(yyvsp[-4].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IDENTIFIER");
                        	(yyvsp[-3].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_BRACE");
                        	(yyvsp[0].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_BRACE");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-4].nd_obj).nd, (yyvsp[-3].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, "func_call");
                        }
#line 3215 "y.tab.c"
    break;

  case 165: /* arguments: arguments_list  */
#line 1056 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "arguments");	
                        }
#line 3223 "y.tab.c"
    break;

  case 166: /* arguments: %empty  */
#line 1060 "final_parser.y"
                        {
	     			(yyval.nd_obj).nd = NULL; 
	     	  	}
#line 3231 "y.tab.c"
    break;

  case 167: /* arguments_list: expression extended_arguments  */
#line 1067 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, "arguments_list");	
                        }
#line 3239 "y.tab.c"
    break;

  case 168: /* extended_arguments: COMMA expression extended_arguments  */
#line 1074 "final_parser.y"
                        {
                        	(yyvsp[-2].nd_obj).nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "COMMA");
                        	(yyval.nd_obj).nd=mknode((yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, NULL, NULL, NULL, NULL, "multiply_operators");
                        }
#line 3248 "y.tab.c"
    break;

  case 169: /* extended_arguments: %empty  */
#line 1079 "final_parser.y"
                        {
	     			(yyval.nd_obj).nd = NULL; 
	     	  	}
#line 3256 "y.tab.c"
    break;

  case 170: /* $@26: %empty  */
#line 1085 "final_parser.y"
                                                { insert_value(); }
#line 3262 "y.tab.c"
    break;

  case 171: /* constant: integer_constant $@26  */
#line 1086 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "constant");	
                        }
#line 3270 "y.tab.c"
    break;

  case 172: /* $@27: %empty  */
#line 1089 "final_parser.y"
                                                { insert_value(); }
#line 3276 "y.tab.c"
    break;

  case 173: /* constant: string_constant $@27  */
#line 1090 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "constant");	
                        }
#line 3284 "y.tab.c"
    break;

  case 174: /* $@28: %empty  */
#line 1093 "final_parser.y"
                                                { insert_value(); }
#line 3290 "y.tab.c"
    break;

  case 175: /* constant: float_constant $@28  */
#line 1094 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "constant");	
                        }
#line 3298 "y.tab.c"
    break;

  case 176: /* $@29: %empty  */
#line 1097 "final_parser.y"
                                                { insert_value(); }
#line 3304 "y.tab.c"
    break;

  case 177: /* constant: character_constant $@29  */
#line 1098 "final_parser.y"
                        {
                        	(yyval.nd_obj).nd=mknode((yyvsp[-1].nd_obj).nd, NULL, NULL, NULL, NULL, NULL, NULL, "constant");	
                        }
#line 3312 "y.tab.c"
    break;


#line 3316 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1103 "final_parser.y"


extern FILE *yyin;
extern int yylineno;
extern char *yytext;
void insert_SymbolTable_type(char *,char *);
void insert_SymbolTable_class(char *,int);
void insert_SymbolTable_value(char *, char *);
void insert_ConstantTable(char *, char *);
void insert_SymbolTable_arraydim(char *, char *);
void insert_SymbolTable_pdl(char *, int);
void insert_SymbolTable_funcparam(char *, char *);
void printSymbolTable();
void printConstantTable();
void printSymbolDataLine();

int main() {
        init_lexer_memory();  // Initialize memory pool
        yyin = fopen("test1.c", "r");
        int result = yyparse();
        
        if(flag == 0) {
                printf("\nVALID PARSE\n");
                printf("\n");
                printf("%30s SYMBOL TABLE \n", " ");
                printf("%1s %s\n", " ", "----------------------------------------------------------------------------------------------------------------------------------");
                printSymbolTable();
                printf("%1s %s\n", " ", "---------------------------------------------------------------------------------------------------------------------------------");
                printf("\n\n%20s CONSTANT TABLE \n", " ");
                printf("%1s %s\n", " ", "-------------------------------------------");
                printConstantTable();
                printf("%1s %s\n\n", " ", "-------------------------------------------");

                // Print beautified AST
                printf("\n╔════════════════════════════════════╗");
                printf("\n║      Abstract Syntax Tree          ║");
                printf("\n╚════════════════════════════════════╝\n");
                levelOrderTraversal(head);

                // Print concise memory info
                printf("\n╔════════════════════════════════════╗");
                printf("\n║      Memory Usage Summary          ║");
                printf("\n╠════════════════════════════════════╣");
                printf("\n║ Memory operations completed        ║");
                printf("\n║ All resources properly freed       ║");
                printf("\n╚════════════════════════════════════╝\n");
        } else {
                printf("\n╔════════════════════════════════════╗");
                printf("\n║          Parsing Status            ║");
                printf("\n╠════════════════════════════════════╣");
                printf("\n║ ✗ Failed to parse input file       ║");
                printf("\n╚════════════════════════════════════╝\n");
        }

        cleanup_tree(head);   // Clean up the parse tree
        free_memory_pool();   // Clean up memory pool
        return result;
}

void yyerror(char *s) {
        printf("Line No. : %d %s %s\n",yylineno, s, yytext);
        flag=1;
        printf("INVALID PARSE\n");
}

void insert_type() {
        insert_SymbolTable_type(current_identifier,current_type);
}

void insert_class(int a) {
        insert_SymbolTable_class(current_identifier,a);
}

void insert_value() {       
        if(strcmp(previous_operator, "=") == 0) {
                insert_SymbolTable_value(current_identifier,current_value);
        }
}       

void insert_dimensions() {       
        insert_SymbolTable_arraydim(current_identifier, current_value);
}

void insert_pdl(int pdl) {
        insert_SymbolTable_pdl(current_function, pdl);
}

void insert_parameters() {
        insert_SymbolTable_funcparam(current_function, current_identifier);
}

