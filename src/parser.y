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

%token NOT "!"
%token AND "&&"
%token LESS "<"
%token PLUS "+"
%token MINUS "-"
%token MUL "*"

%token OCURLY "{"
%token CCURLY "}"
%token OSQUARE "["
%token CSQUARE "]"
%token OPAREN "("
%token CPAREN ")"
%token ASSIGN "="
%token COMMA ","
%token DOT "."
%token SCOLON ";"

%token STRING "String"

%token INT "int"
%token BOOL "boolean"

%token TRUE "true"
%token FALSE "false"

%token CLASS "class"
%token PUBLIC "public"
%token STATIC "static"
%token VOID "void"
%token MAIN "main"
%token EXTENDS "extends"
%token RETURN "return"
%token THIS "this"
%token NEW "new"

%token IF "if"
%token ELSE "else"
%token WHILE "while"

%token PRINT "System.out.println"
%token LENGTH "length"

%token <std::string> IDENTIFIER
%token <int> INTEGER_LITERAL

// %token Goal
// %token MainClass
// %token ClassDeclarations
// %token ClassDeclaration
// %token Extends
// %token VarDeclarations
// %token VarDeclaration
// %token Type
// %token MethodDeclarations
// %token MethodDeclaration
// %token MethodType
// %token MethodParameters
// %token Statements
// %token Statement
// %token Expression
// %token Expressions
// %token Identifier

// %start Goal

%%
Goal:
	MainClass ClassDeclarations
;

MainClass:
    "class" Identifier "{" "public" "static" "void" "main" "(" "String" "[" "]" Identifier ")" "{" Statement "}" "}" {
        std::cout << "MainClass ";
    }
;

ClassDeclarations:
    %empty
    | ClassDeclarations ClassDeclaration
;

ClassDeclaration:
    "class" Identifier Extends "{" VarDeclarations MethodDeclarations "}" {
        std::cout << "ClassDeclaration ";
    }
;

Extends:
    %empty
    | "extends" Identifier {
        std::cout << "Extends ";
    }
;

VarDeclarations:
    %empty
    | VarDeclarations VarDeclaration
;

VarDeclaration:
    Type Identifier ";" {
        std::cout << "VarDeclaration ";
    }
;

Type:
    "int" "[" "]"
    | "int"
    | "boolean"
    | Identifier
;

MethodDeclarations:
    %empty
    | MethodDeclarations MethodDeclaration
;

MethodDeclaration:
    MethodType Type Identifier "(" MethodParameters ")" "{" VarDeclarations Statements "return" Expression ";" "}" {
        std::cout << "MethodDeclaration ";
    }
;


MethodType:
    "public" {
        std::cout << "Public ";
    }
;

MethodParameters:
    %empty
    | Type Identifier {
        std::cout << "MethodParameter ";
    }
    | MethodParameters "," Type Identifier {
        std::cout << "MethodParameter ";
    }
;

Statements:
    %empty
    | Statement Statements
;

Statement:
    "{" Statements "}"
    | "if" "(" Expression ")" Statement "else" Statement {
        std::cout << "If ";
    }
    | "while" "(" Expression ")" Statement {
        std::cout << "While ";
    }
    | "System.out.println" "(" Expression ")" ";" {
        std::cout << "Print ";
    }
    | Identifier "=" Expression ";" {
        std::cout << "Assignment ";
    }
    | Identifier "[" Expression "]" "=" Expression ";" {
        std::cout << "ArrayAssignment ";
    }
;

Expression:
    Expression "&&" Expression {
        std::cout << "And ";
    }
    | Expression "<" Expression {
        std::cout << "Less ";
    }
    | Expression "+" Expression {
        std::cout << "Plus ";
    }
    | Expression "-" Expression {
        std::cout << "Minus ";
    }
    | Expression "*" Expression {
        std::cout << "Multiply ";
    }
    | Expression "[" Expression "]" {
        std::cout << "ArrayExpression ";
    }
    | Expression "." "length" {
        std::cout << "Length ";
    }
    | Expression "." Identifier "(" Expressions ")" {
        std::cout << "ExpressionCall ";
    }
    | INTEGER_LITERAL {
        std::cout << "Int " << $1 << " ";
    }
    | "true" {
        std::cout << "True ";
    }
    | "false" {
        std::cout << "False ";
    }
    | Identifier
    | "this" {
        std::cout << "This ";
    }
    | "new" "int" "[" Expression "]" {
        std::cout << "NewIntArray ";
    }
    | "new" Identifier "(" ")" {
        std::cout << "New ";
    }
    | "!" Expression {
        std::cout << "Not ";
    }
    | "(" Expression ")"
;

Expressions:
    %empty
    | Expression {
         std::cout << "Expression ";
    }
    | Expressions "," Expression {
        std::cout << "Expression ";
    }
;

Identifier:
    IDENTIFIER {
        std::cout << "Id " << $1 << " ";
    }
;
%%