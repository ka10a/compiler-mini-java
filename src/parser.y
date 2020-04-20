%require "3.5"

%{
#include <string>
#include <iostream>
#include "parser.hpp"

extern yy::parser::symbol_type yylex();

%}

%language "c++"
%define api.value.type variant
%define api.token.constructor

%token NOT
%token AND
%token LESS
%token PLUS
%token MINUS
%token MUL

%token OCURLY
%token CCURLY
%token OSQUARE
%token CSQUARE
%token OPAREN
%token CPAREN
%token ASSIGN
%token COMMA
%token DOT
%token SCOLON

%token STRING
%token INT
%token BOOL

%token TRUE
%token FALSE

%token CLASS
%token PUBLIC
%token STATIC
%token VOID
%token MAIN
%token EXTENDS
%token RETURN
%token THIS
%token NEW

%token IF
%token ELSE
%token WHILE

%token PRINT
%token LENGTH

%token <std::string> IDENTIFIER
%token <int> INTEGER_LITERAL


// %start goal

%%
program:
    %empty
    | program NOT       { std::cout << "NOT "; }
    | program AND     { std::cout << "AND "; }
    | program LESS    { std::cout << "LESS "; }
    | program PLUS    { std::cout << "PLUS "; }
    | program MINUS   { std::cout << "MINUS "; }
    | program MUL     { std::cout << "MUL "; }
    | program OCURLY  { std::cout << "OCURLY "; }
    | program CCURLY  { std::cout << "CCURLY "; }
    | program OSQUARE { std::cout << "OSQUARE "; }
    | program CSQUARE { std::cout << "CSQUARE "; }
    | program OPAREN  { std::cout << "OPAREN "; }
    | program CPAREN  { std::cout << "CPAREN "; }
    | program ASSIGN  { std::cout << "ASSIGN "; }
    | program COMMA   { std::cout << "COMMA "; }
    | program DOT     { std::cout << "DOT "; }
    | program SCOLON  { std::cout << "SCOLON "; }
    | program STRING  { std::cout << "STRING "; }
    | program INT     { std::cout << "INT "; }
    | program BOOL    { std::cout << "BOOL "; }
    | program TRUE    { std::cout << "TRUE "; }
    | program FALSE   { std::cout << "FALSE "; }
    | program CLASS   { std::cout << "CLASS "; }
    | program PUBLIC  { std::cout << "PUBLIC "; }
    | program STATIC  { std::cout << "STATIC "; }
    | program VOID    { std::cout << "VOID "; }
    | program MAIN    { std::cout << "MAIN "; }
    | program EXTENDS { std::cout << "EXTENDS "; }
    | program RETURN  { std::cout << "RETURN "; }
    | program THIS    { std::cout << "THIS "; }
    | program NEW     { std::cout << "NEW "; }
    | program IF      { std::cout << "IF "; }
    | program ELSE    { std::cout << "ELSE "; }
    | program WHILE   { std::cout << "WHILE "; }
    | program PRINT   { std::cout << "PRINT "; }
    | program LENGTH  { std::cout << "LENGTH "; }
    | program IDENTIFIER { std::cout << "IDENTIFIER(" << $2 << ") "; }
    | program INTEGER_LITERAL { std::cout << "INTEGER_LITERAL(" << $2 << ") "; }
;
%%

