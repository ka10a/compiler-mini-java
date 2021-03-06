%require "3.5"

%{
#include <string>

#include <parser.hpp>

extern yy::parser::symbol_type yylex();
void yy::parser::error(const location_type& loc, const std::string& msg) {
    throw yy::parser::syntax_error(loc, msg);
}

GoalPtr goal;
extern yy::location loc;
%}

%code requires {
#include <ast/class_declaration.hpp>
#include <ast/expressions.hpp>
#include <ast/goal.hpp>
#include <ast/identifier.hpp>
#include <ast/main_class.hpp>
#include <ast/method_declaration.hpp>
#include <ast/statements.hpp>
#include <ast/types.hpp>
#include <ast/var_declaration.hpp>
}

%language "c++"
%define api.value.type variant
%define api.token.constructor
%locations

%token NOT "!"
%token AND "&&"
%token LESS "<"
%token PLUS "+"
%token MINUS "-"
%token MUL "*"

%nonassoc NOT
%left AND
%left LESS
%left PLUS
%left MINUS
%left MUL

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

%right OSQUARE
%right DOT

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

%left LENGTH


%token <std::string> IDENTIFIER
%token <int> INTEGER_LITERAL
%token END 0

%type <GoalPtr> Goal
%type <MainClassPtr> MainClass
%type <ClassDeclarations> ClassDeclarations
%type <ClassDeclarationPtr> ClassDeclaration
%type <IdentifierPtr> Extends
%type <VarDeclarations> VarDeclarations
%type <VarDeclarationPtr> VarDeclaration
%type <TypePtr> Type
%type <MethodDeclarations> MethodDeclarations
%type <MethodDeclarationPtr> MethodDeclaration
%type <VarDeclarations> MethodArgs
%type <Statements> Statements
%type <StatementPtr> Statement
%type <ExpressionPtr> Expression
%type <Expressions> Expressions
%type <IdentifierPtr> Identifier

%start Goal

%%
Goal:
    MainClass ClassDeclarations {
        goal = std::make_shared<Goal>(std::make_shared<yy::location>(loc), std::move($1), std::move($2));
    }
;

MainClass:
    "class" Identifier "{" "public" "static" "void" "main" "(" "String" "[" "]" Identifier ")" "{" Statement "}" "}" {
        $$ = std::make_shared<MainClass>(
            std::make_shared<yy::location>(loc),
            std::move($2),
            std::move($15)
        );
    }
;

ClassDeclarations:
    %empty {
        $$ = ClassDeclarations();
    }
    | ClassDeclarations ClassDeclaration {
        $1.push_back(std::move($2));
        $$ = std::move($1);
    }
;

ClassDeclaration:
    "class" Identifier Extends "{" VarDeclarations MethodDeclarations "}" {
        $$ = std::make_shared<ClassDeclaration>(
            std::make_shared<yy::location>(loc),
            std::move($2),
            std::move($3),
            std::move($5),
            std::move($6)
        );
    }
;

Extends:
    %empty {
        $$ = nullptr;
    }
    | "extends" Identifier {
        $$ = std::move($2);
    }
;

VarDeclarations:
    %empty {
        $$ = VarDeclarations();
    }
    | VarDeclarations VarDeclaration {
        $1.push_back(std::move($2));
        $$ = std::move($1);
    }
;

VarDeclaration:
    Type Identifier ";" {
        $$ = std::make_shared<VarDeclaration>(std::make_shared<yy::location>(loc), std::move($1), std::move($2));
    }
;

MethodDeclarations:
    %empty {
        $$ = MethodDeclarations();
    }
    | MethodDeclarations MethodDeclaration {
        $1.push_back(std::move($2));
        $$ = std::move($1);
    }
;

MethodDeclaration:
    "public" Type Identifier "(" MethodArgs ")" "{" VarDeclarations Statements "return" Expression ";" "}" {
        $$ = std::make_shared<MethodDeclaration>(
            std::make_shared<yy::location>(loc),
            std::move($2),
            std::move($3),
            std::move($5),
            std::move($8),
            std::move($9),
            std::move($11)
        );
    }
;

MethodArgs:
    %empty {
        $$ = VarDeclarations();
    }
    | Type Identifier {
        $$ = VarDeclarations();
        $$.push_back(
            std::make_shared<VarDeclaration>(
                std::make_shared<yy::location>(loc),
                std::move($1),
                std::move($2)
            )
       );
    }
    | MethodArgs "," Type Identifier {
        $1.push_back(
            std::make_shared<VarDeclaration>(
                std::make_shared<yy::location>(loc),
                std::move($3),
                std::move($4)
            )
        );
        $$ = std::move($1);
    }
;

Type:
    "int" "[" "]" {
        $$ = std::make_shared<IntArrayType>(std::make_shared<yy::location>(loc));
    }
    | "int" {
        $$ = std::make_shared<IntType>(std::make_shared<yy::location>(loc));
    }
    | "boolean" {
        $$ = std::make_shared<BoolType>(std::make_shared<yy::location>(loc));
    }
    | Identifier {
        $$ = std::make_shared<ClassType>(std::make_shared<yy::location>(loc), std::move($1));
    }
;

Statements:
    %empty {
        $$ = Statements();
    }
    | Statement Statements {
        $2.push_front(std::move($1));
        $$ = std::move($2);
    }
;

Statement:
    "{" Statements "}" {
        $$ = std::make_shared<StatementList>(std::make_shared<yy::location>(loc), std::move($2));
    }
    | "if" "(" Expression ")" Statement "else" Statement {
        $$ = std::make_shared<IfElseStatement>(
            std::make_shared<yy::location>(loc),
            std::move($3),
            std::move($5),
            std::move($7)
        );
    }
    | "while" "(" Expression ")" Statement {
        $$ = std::make_shared<WhileStatement>(
            std::make_shared<yy::location>(loc),
            std::move($3),
            std::move($5)
        );
    }
    | "System.out.println" "(" Expression ")" ";" {
        $$ = std::make_shared<PrintStatement>(std::make_shared<yy::location>(loc), std::move($3));
    }
    | Identifier "=" Expression ";" {
        $$ = std::make_shared<AssignmentStatement>(
       	    std::make_shared<yy::location>(loc),
            std::move($1),
            std::move($3)
        );
    }
    | Identifier "[" Expression "]" "=" Expression ";" {
        $$ = std::make_shared<ArrayAssignmentStatement>(
            std::make_shared<yy::location>(loc),
            std::move($1),
            std::move($3),
            std::move($6)
        );
    }
;

Expression:
    Expression "&&" Expression {
        $$ = std::make_shared<AndExpression>(std::make_shared<yy::location>(loc), std::move($1), std::move($3));
    }
    | Expression "<" Expression {
        $$ = std::make_shared<LessExpression>(std::make_shared<yy::location>(loc), std::move($1), std::move($3));
    }
    | Expression "+" Expression {
        $$ = std::make_shared<AddExpression>(std::make_shared<yy::location>(loc), std::move($1), std::move($3));
    }
    | Expression "-" Expression {
        $$ = std::make_shared<SubtractExpression>(std::make_shared<yy::location>(loc), std::move($1), std::move($3));
    }
    | Expression "*" Expression {
        $$ = std::make_shared<MultiplyExpression>(std::make_shared<yy::location>(loc), std::move($1), std::move($3));
    }
    | Expression "[" Expression "]" {
        $$ = std::make_shared<ArrayExpression>(std::make_shared<yy::location>(loc), std::move($1), std::move($3));
    }
    | Expression "length" {
        $$ = std::make_shared<LengthExpression>(std::make_shared<yy::location>(loc), std::move($1));
    }
    | Expression "." Identifier "(" Expressions ")" {
        $$ = std::make_shared<MethodCallExpression>(
            std::make_shared<yy::location>(loc),
            std::move($1),
            std::move($3),
            std::move($5)
        );
    }
    | INTEGER_LITERAL {
        $$ = std::make_shared<IntExpression>(std::make_shared<yy::location>(loc), $1);
    }
    | "true" {
        $$ = std::make_shared<BoolExpression>(std::make_shared<yy::location>(loc), true);
    }
    | "false" {
        $$ = std::make_shared<BoolExpression>(std::make_shared<yy::location>(loc), false);
    }
    | Identifier {
        $$ = std::make_shared<IdentifierExpression>(std::make_shared<yy::location>(loc), std::move($1));
    }
    | "this" {
        $$ = std::make_shared<ThisExpression>(std::make_shared<yy::location>(loc));
    }
    | "new" "int" "[" Expression "]" {
        $$ = std::make_shared<NewIntArrayExpression>(std::make_shared<yy::location>(loc), std::move($4));
    }
    | "new" Identifier "(" ")" {
        $$ = std::make_shared<NewExpression>(std::make_shared<yy::location>(loc), std::move($2));
    }
    | "!" Expression {
        $$ = std::make_shared<NotExpression>(std::make_shared<yy::location>(loc), std::move($2));
    }
    | "(" Expression ")" {
        $$ = std::move($2);
    }
;

Expressions:
    %empty {
        $$ = Expressions();
    }
    | Expression {
        $$ = Expressions();
        $$.push_back(std::move($1));
    }
    | Expressions "," Expression {
        $1.push_back(std::move($3));
        $$ = std::move($1);
    }
;

Identifier:
    IDENTIFIER {
        $$ = std::make_shared<Identifier>(std::make_shared<yy::location>(loc), std::move($1));
    }
;
%%
