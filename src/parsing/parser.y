%require "3.5"

%{
#include <string>

#include <parser.hpp>

GoalPtr goal;
extern yy::parser::symbol_type yylex();

%}

%code requires {
#include <class_declaration.hpp>
#include <expressions.hpp>
#include <goal.hpp>
#include <identifier.hpp>
#include <main_class.hpp>
#include <method_declaration.hpp>
#include <statements.hpp>
#include <types.hpp>
#include <var_declaration.hpp>
}

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
        goal = std::make_shared<Goal>(std::move($1), std::move($2));
    }
;

MainClass:
    "class" Identifier "{" "public" "static" "void" "main" "(" "String" "[" "]" Identifier ")" "{" Statement "}" "}" {
        $$ = std::make_shared<MainClass>(
            std::move($2),
            std::move($12),
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
        $$ = std::make_shared<VarDeclaration>(std::move($1), std::move($2));
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
                std::move($1),
                std::move($2)
            )
       );
    }
    | MethodArgs "," Type Identifier {
        $1.push_back(
            std::make_shared<VarDeclaration>(
                std::move($3),
                std::move($4)
            )
        );
        $$ = std::move($1);
    }
;

Type:
    "int" "[" "]" {
        $$ = std::make_shared<IntArrayType>();
    }
    | "int" {
        $$ = std::make_shared<IntType>();
    }
    | "boolean" {
        $$ = std::make_shared<BoolType>();
    }
    | Identifier {
        $$ = std::make_shared<IdentifierType>(std::move($1));
    }
;

Statements:
    %empty {
        $$ = Statements();
    }
    | Statements Statement {
        $1.push_back(std::move($2));
        $$ = std::move($1);
    }
;

Statement:
    "{" Statements "}" {
        $$ = std::make_shared<StatementList>(std::move($2));
    }
    | "if" "(" Expression ")" Statement "else" Statement {
        $$ = std::make_shared<IfElseStatement>(
            std::move($3),
            std::move($5),
            std::move($7)
        );
    }
    | "while" "(" Expression ")" Statement {
        $$ = std::make_shared<WhileStatement>(
            std::move($3),
            std::move($5)
        );
    }
    | "System.out.println" "(" Expression ")" ";" {
        $$ = std::make_shared<PrintStatement>(std::move($3));
    }
    | Identifier "=" Expression ";" {
        $$ = std::make_shared<AssignmentStatement>(
            std::move($1),
            std::move($3)
        );
    }
    | Identifier "[" Expression "]" "=" Expression ";" {
        $$ = std::make_shared<ArrayAssignmentStatement>(
            std::move($1),
            std::move($3),
            std::move($6)
        );
    }
;

Expression:
    Expression "&&" Expression {
        $$ = std::make_shared<AndExpression>(std::move($1), std::move($3));
    }
    | Expression "<" Expression {
        $$ = std::make_shared<LessExpression>(std::move($1), std::move($3));
    }
    | Expression "+" Expression {
        $$ = std::make_shared<AddExpression>(std::move($1), std::move($3));
    }
    | Expression "-" Expression {
        $$ = std::make_shared<SubtractExpression>(std::move($1), std::move($3));
    }
    | Expression "*" Expression {
        $$ = std::make_shared<MultiplicateExpression>(std::move($1), std::move($3));
    }
    | Expression "[" Expression "]" {
        $$ = std::make_shared<ArrayExpression>(std::move($1), std::move($3));
    }
    | Expression "." "length" {
        $$ = std::make_shared<LengthExpression>(std::move($1));
    }
    | Expression "." Identifier "(" Expressions ")" {
        $$ = std::make_shared<MethodCallExpression>(
            std::move($1),
            std::move($3),
            std::move($5)
        );
    }
    | INTEGER_LITERAL {
        $$ = std::make_shared<IntExpression>($1);
    }
    | "true" {
        $$ = std::make_shared<BoolExpression>(true);
    }
    | "false" {
        $$ = std::make_shared<BoolExpression>(false);
    }
    | Identifier {
        $$ = std::make_shared<IdentifierExpression>(std::move($1));
    }
    | "this" {
        $$ = std::make_shared<ThisExpression>();
    }
    | "new" "int" "[" Expression "]" {
        $$ = std::make_shared<NewIntArrayExpression>(std::move($4));
    }
    | "new" Identifier "(" ")" {
        $$ = std::make_shared<NewExpression>(std::move($2));
    }
    | "!" Expression {
        $$ = std::make_shared<NotExpression>(std::move($2));
    }
    | "(" Expression ")" {
        $$ = std::make_shared<BetweenBracketsExpression>(std::move($2));
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
        $$ = std::make_shared<Identifier>(std::move($1));
    }
;
%%