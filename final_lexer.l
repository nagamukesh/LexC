%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
#include "custom_memory.h"  // Include custom memory management

extern void yyerror(const char *);
extern int yylineno;
int curly_count=0;

// Initialize memory pool at the start
void init_lexer_memory() {
    init_memory_pool(64 * 1024 * 1024); // Initialize with 64MB
}

#define TABLE_SIZE 1000

struct ConstantTable{
                char constant_name[100];
                char constant_type[100];
                int exist;
        }CT[TABLE_SIZE];

struct SymbolTable{
                char symbol_name[100];
                char symbol_type[100];
                char array_dimensions[100];
                char class[100];
                char value[100];
                char parameters[100];
                char pdl[100];
                int line_number;
                int exist;
                int nesting_level;
        }ST[TABLE_SIZE];

int search_ConstantTable(char* str) {
for (int i = 0; i < TABLE_SIZE; i++) {
if (CT[i].exist == 1 && strcmp(CT[i].constant_name, str) == 0) {
return 1;
        }
}
return 0;
}

int search_SymbolTable(char* str) {
for (int i = 0; i < TABLE_SIZE; i++) {
if (ST[i].exist == 1 && strcmp(ST[i].symbol_name, str) == 0) {
return 1;
        }
}
return 0;
}

void insert_ConstantTable(char* name, char* type){
         if(search_ConstantTable(name))
                return;

        for (int i = 0; i < TABLE_SIZE; i++) {
                if(CT[i].exist == 0){
                        strcpy(CT[i].constant_name, name);
                        strcpy(CT[i].constant_type, type);
                        CT[i].exist = 1;
                        return;
                }
        }
        printf("Error: Constant table is full.\n");
}

        void insert_SymbolTable(char* name, char* type){
                if(search_SymbolTable(name))
                        return;

                for (int i = 0; i < TABLE_SIZE; i++) {
                        if(ST[i].exist == 0){
                                strcpy(ST[i].symbol_name, name);
                                strcpy(ST[i].symbol_type, type);
                                strcpy(ST[i].array_dimensions, "No dimensions");
                                ST[i].line_number=yylineno;
                                ST[i].nesting_level=curly_count;
                                strcpy(ST[i].pdl, "Not a function");
                                strcpy(ST[i].parameters, "No parameters");
                                ST[i].exist = 1;
                                return;
                        }
                }
                printf("Error: Symbol table is full.\n");
        }

        void insert_SymbolTable_type(char *str1, char *str2)
        {
                for(int i = 0 ; i < TABLE_SIZE ; i++)
                {
                        if(strcmp(ST[i].symbol_name,str1)==0)
                        {
                                strcpy(ST[i].symbol_type,str2);
                        }
                }
    }

        void insert_SymbolTable_class(char *str1, int a){
                for(int i=0;i<TABLE_SIZE;i++){
                        if(strcmp(ST[i].symbol_name,str1)==0)
                        {
                                if(a==0){
                                        strcpy(ST[i].class,"STRUCTURE");
                                }
                                else if(a==1){
                                        strcpy(ST[i].class,"FUNCTION");
                                }
                                else if(a==2){
                                        strcpy(ST[i].class,"VARIABLE");
                                }
                        }
                }
        }

        void insert_SymbolTable_value(char *str1, char *str2)
        {
                for(int i = 0 ; i < TABLE_SIZE ; i++)
                {
                        if(strcmp(ST[i].symbol_name,str1)==0)
                        {
                                strcpy(ST[i].value,str2);
                        }
                }
        }

        void insert_SymbolTable_arraydim(char *str1, char *dim)
        {
                for(int i = 0 ; i < TABLE_SIZE ; i++)
                {
                        if(strcmp(ST[i].symbol_name,str1)==0)
                        {
                                strcpy(ST[i].array_dimensions,dim);
                        }
                }
        }

        void insert_SymbolTable_pdl(char *str1, int pdl)
        {
                for(int i = 0 ; i < TABLE_SIZE ; i++)
                {
                        if(strcmp(ST[i].symbol_name,str1)==0)
                        {
                                if(pdl==0) strcpy(ST[i].pdl, "Defined");
                                else if(pdl==1) strcpy(ST[i].pdl, "Declared");
                        }
                }
        }

        void insert_SymbolTable_funcparam(char *str1, char *param)
        {
                for(int i = 0 ; i < TABLE_SIZE ; i++)
                {
                        if(strcmp(ST[i].symbol_name,str1)==0)
                        {
                                strcpy(ST[i].parameters," ");
                strcat(ST[i].parameters,param);
                        }
                }
        }

        void insert_SymbolTable_line(char *str1, int line)
        {
                for(int i = 0 ; i < TABLE_SIZE ; i++)
                {
                        if(strcmp(ST[i].symbol_name,str1)==0)
                        {
                                ST[i].line_number = line;
                        }
                }
        }

        void printConstantTable(){
                printf("\n┌────────────────────────┬────────────────────────┐\n");
                printf("│ %-20s │ %-20s │\n", "CONSTANT", "TYPE");
                printf("├────────────────────────┼────────────────────────┤\n");
                for(int i = 0; i < TABLE_SIZE; ++i){
                        if(CT[i].exist == 0)
                                continue;
                        printf("│ %-20s │ %-20s │\n", CT[i].constant_name, CT[i].constant_type);
                }
                printf("└────────────────────────┴────────────────────────┘\n");
        }

        void printSymbolTable(){
                printf("\n┌────────────┬──────────┬──────────┬───────────┬──────────┐\n");
                printf("│ %-10s │ %-8s │ %-8s │ %-9s │ %-8s │\n", "SYMBOL", "TYPE", "CLASS", "SCOPE", "LINE");
                printf("├────────────┼──────────┼──────────┼───────────┼──────────┤\n");
                for(int i = 0; i < TABLE_SIZE; ++i){
                        if(ST[i].exist == 0)
                                continue;
                        printf("│ %-10s │ %-8s │ %-8s │ %-9d │ %-8d │\n", 
                               ST[i].symbol_name, 
                               ST[i].symbol_type, 
                               ST[i].class,
                               ST[i].nesting_level,
                               ST[i].line_number);
                }
                printf("└────────────┴──────────┴──────────┴───────────┴──────────┘\n");
        }

        char current_identifier[20];
        char current_type[20];
        char current_value[20];
        char current_function[20];
        char previous_operator[20];
        extern int flag;

%}

%option noyywrap
%option noinput
%option nounput

num                     [0-9]
alpha                   [a-zA-Z]
alphanum            {alpha}|{num}
escape_sequences    0|a|b|f|n|r|t|v|"\\"|"\""|"\'"
%x MLCOMMENT
DE "define"
IN "include"

%%

        int nested_count = 0;
        int check_nested = 0;

"#include"[ ]*"<"{alpha}({alphanum})*".h>"                                      { }
"#define"[ ]+(_|{alpha})({alphanum})*[ ]*(.)+                                   { }
"//".*                                                                                                                                                  { }

"/*"                                                                     { BEGIN MLCOMMENT; }
<MLCOMMENT>"/*"                                                          { ++nested_count;
                                                                                                check_nested = 1;
                                                                                         }      
<MLCOMMENT>"*"+"/"                                               { if (nested_count) --nested_count;
                                                                                           else{ if(check_nested){
                                                                                                                check_nested = 0;
                                                                                                                BEGIN INITIAL;
                                                                                                                }
                                                                                                         else{
                                                                                                                BEGIN INITIAL;
                                                                                                        }
                                                                                            }
                                                                                         }
<MLCOMMENT>"*"+                                                  ;
<MLCOMMENT>[^/*\n]+                                                      ;
<MLCOMMENT>[/]                                                           ;
<MLCOMMENT>\n                                                            ;
<MLCOMMENT><<EOF>>                                                       { printf("Line No. %d ERROR: MULTI LINE COMMENT NOT CLOSED\n", yylineno); return 0;}
"auto"                                  { return AUTO; }
"break"                                 { insert_SymbolTable_line(yytext, yylineno); insert_SymbolTable(yytext, "Keyword");  return BREAK;}
"bool"                                  { return BOOL; }
"case"                                  { insert_SymbolTable(yytext, "Keyword");  return CASE;}
"char"                                  { strcpy(current_type,yytext); insert_SymbolTable(yytext, "Keyword"); return CHAR;}
"const"                                 { return CONST; }
"continue"                              { insert_SymbolTable(yytext, "Keyword");  return CONTINUE;}
"default"                               { insert_SymbolTable(yytext, "Keyword");  return DEFAULT;}
"do"                                    { insert_SymbolTable(yytext, "Keyword"); return DO;}
"double"                                { strcpy(current_type,yytext); insert_SymbolTable(yytext, "Keyword"); return DOUBLE;}
"else"                                  { insert_SymbolTable_line(yytext, yylineno); insert_SymbolTable(yytext, "Keyword"); return ELSE;}
"float"                                 { strcpy(current_type,yytext); insert_SymbolTable(yytext, "Keyword");return FLOAT;}
"for"                                   { insert_SymbolTable(yytext, "Keyword"); return FOR;}
"goto"                                  { insert_SymbolTable(yytext, "Keyword");  return GOTO;}
"if"                                    { insert_SymbolTable(yytext, "Keyword"); return IF;}
"int"                                   { strcpy(current_type,yytext); insert_SymbolTable(yytext, "Keyword");return INT;}
"long"                                  { strcpy(current_type,yytext); insert_SymbolTable(yytext, "Keyword");  return LONG;}
"return"                                { insert_SymbolTable(yytext, "Keyword");  return RETURN;}
"short"                                 { strcpy(current_type,yytext); insert_SymbolTable(yytext, "Keyword");  return SHORT;}
"signed"                                { strcpy(current_type,yytext); insert_SymbolTable(yytext, "Keyword");  return SIGNED;}
"sizeof"                                { insert_SymbolTable(yytext, "Keyword");  return SIZEOF;}
"static"                                { return STATIC; }
"struct"                                { strcpy(current_type,yytext); insert_SymbolTable(yytext, "Keyword");  return STRUCT;}
"switch"                                { insert_SymbolTable(yytext, "Keyword");  return SWITCH;}
"typedef"                               { return TYPEDEF; }
"union"                                 { return UNION; }
"unsigned"                              { insert_SymbolTable(yytext, "Keyword");  return UNSIGNED;}
"void"                                  { strcpy(current_type,yytext); insert_SymbolTable(yytext, "Keyword");  return VOID;}
"volatile"                              { return VOLATILE; }
"while"                                 { insert_SymbolTable(yytext, "Keyword"); return WHILE;}
">>="                                   { return RIGHT_ASSIGN; }
"<<="                                   { return LEFT_ASSIGN; }
"+="                                    { return ADD_EQUAL; }
"-="                                    { return SUB_EQUAL; }
"*="                                    { return MUL_EQUAL; }
"/="                                    { return DIV_EQUAL; }
"%="                                    { return MOD_EQUAL; }
"&="                                    { return AND_ASSIGN; }
"^="                                    { return XOR_ASSIGN; }
"|="                                    { return OR_ASSIGN; }
">>"                                    { return RIGHT_OP; }
"<<"                                    { return LEFT_OP; }
"++"                                    { return INCREMENT; }
"--"                                    { return DECREMENT; }
"->"                                    { return PTR_OP; }
"&&"                                    { return AND_OP; }
"||"                                    { return OR_OP; }
"<="                                    { return LESSER_EQUAL; }
">="                                    { return GREATER_EQUAL; }
"=="                                    { return EQUAL; }
"!="                                    { return NOT_EQUAL; }
";"                                     { return SEMI_COLON; }
("{")                                   { curly_count++; return OPEN_CURLY; }
("<%")                                  { return OPEN_CURLY; }
("}")                                   { curly_count--; return CLOSE_CURLY; }
("%>")                                  { return CLOSE_CURLY; }
","                                     { return COMMA; }
":"                                     { return COLON; }
"="                                     { return EQUALS; }
"("                                     { return OPEN_BRACE; }
")"                                     { return CLOSE_BRACE; }
("["|"<:")                              { return OPEN_SQR; }
("]"|":>")                              { return CLOSE_SQR; }
"."                                     { return DOT; }
"&"                                     { return AND; }
"!"                                     { return NOT; }
"~"                                     { return TILD; }
"-"                                     { return HYPHEN; }
"+"                                     { return PLUS; }
"*"                                     { return MULTIPLY; }
"/"                                     { return DIVIDE; }
"%"                                     { return PERCENT; }
"<"                                     { return LESSER; }
">"                                     { return GREATER; }
"^"                                     { return POWER; }
"|"                                     { return OR; }
"?"                                     { return QUESTION; }
[ \t\v\f]                                           { /*whitespaces*/ }
"\n"                                                    { yylineno++; }
("\"")[^\n\"]*("\"")                            { strcpy(current_value,yytext); insert_ConstantTable(yytext,"String Constant"); return string_constant;}

("\"")[^\n\"]*                                  { printf("Line No. %d ERROR: UNCLOSED STRING - %s\n", yylineno, yytext); return 0;}

("\'")(("\\"({escape_sequences}))|.)("\'")   {strcpy(current_value,yytext); insert_ConstantTable(yytext,"Character Constant"); return character_constant;}

("\'")(((("\\")[^0abfnrtv\\\"\'][^\n\']*))|[^\n\''][^\n\'']+)("\'") {printf("Line No. %d ERROR: NOT A CHARACTER - %s\n", yylineno, yytext); return 0; }

{num}+(\.{num}+)?e{num}+                        {strcpy(current_value,yytext); insert_ConstantTable(yytext, "Floating Constant"); return float_constant;}

{num}+\.{num}+                              {strcpy(current_value,yytext); insert_ConstantTable(yytext, "Floating Constant"); return float_constant;}

{num}+                                          {strcpy(current_value,yytext); insert_ConstantTable(yytext, "Number Constant"); return integer_constant;}

(_|{alpha})({alphanum}|_)*              {strcpy(current_identifier,yytext);insert_SymbolTable(yytext,"Identifier");  return IDENTIFIER;}

(_|{alpha})({alphanum}|_)*/\[   {strcpy(current_identifier,yytext);insert_SymbolTable(yytext,"Array Identifier");  return IDENTIFIER;}


.                                       { flag = 1;
                                          if(yytext[0] == '#')
                                          printf("Line No. %d PREPROCESSOR ERROR - %s\n",yylineno, yytext);
                                          else
                                          printf("Line No. %d ERROR ILLEGAL CHARACTER - %s\n", yylineno, yytext);
                                          return 0;}
%%


