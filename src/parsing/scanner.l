%option noyywrap nounput noinput

%{
#include <iostream>
#include <parser.hpp>

yy::location loc;

#define YY_DECL yy::parser::symbol_type yylex()
#define YY_USER_ACTION loc.columns(yyleng);
%}

DIGIT            [0-9]
CHARACTER        [a-zA-Z_]
IDENTIFIER       {CHARACTER}({CHARACTER}|{DIGIT})*
INTEGER_LITERAL  [1-9]{DIGIT}*|0
COMMENT          "//".*
BLANK            [ \t\r]

%%
{COMMENT}|({BLANK})+ { loc.step(); }
\n+      { loc.lines(yyleng); loc.step(); }

"!"  { return yy::parser::make_NOT(loc); }
"&&" { return yy::parser::make_AND(loc); }
"<"  { return yy::parser::make_LESS(loc); }
"+"  { return yy::parser::make_PLUS(loc); }
"-"  { return yy::parser::make_MINUS(loc); }
"*"  { return yy::parser::make_MUL(loc); }

"{" { return yy::parser::make_OCURLY(loc); }
"}" { return yy::parser::make_CCURLY(loc); }
"[" { return yy::parser::make_OSQUARE(loc); }
"]" { return yy::parser::make_CSQUARE(loc); }
"(" { return yy::parser::make_OPAREN(loc); }
")" { return yy::parser::make_CPAREN(loc); }
"=" { return yy::parser::make_ASSIGN(loc); }
"," { return yy::parser::make_COMMA(loc); }
"." { return yy::parser::make_DOT(loc); }
";" { return yy::parser::make_SCOLON(loc); }

"String"  { return yy::parser::make_STRING(loc); }
"int"     { return yy::parser::make_INT(loc); }
"boolean" { return yy::parser::make_BOOL(loc); }

"true"  { return yy::parser::make_TRUE(loc); }
"false" { return yy::parser::make_FALSE(loc); }

"class"   { return yy::parser::make_CLASS(loc); }
"public"  { return yy::parser::make_PUBLIC(loc); }
"static"  { return yy::parser::make_STATIC(loc); }
"void"    { return yy::parser::make_VOID(loc); }
"main"    { return yy::parser::make_MAIN(loc); }
"extends" { return yy::parser::make_EXTENDS(loc); }
"return"  { return yy::parser::make_RETURN(loc); }
"this"    { return yy::parser::make_THIS(loc); }
"new"     { return yy::parser::make_NEW(loc); }

"if"    { return yy::parser::make_IF(loc); }
"else"  { return yy::parser::make_ELSE(loc); }
"while" { return yy::parser::make_WHILE(loc); }

"System.out.println" { return yy::parser::make_PRINT(loc); }
".length" { return yy::parser::make_LENGTH(loc); }

{IDENTIFIER}      { return yy::parser::make_IDENTIFIER(std::string(yytext), loc); }
{INTEGER_LITERAL} { return yy::parser::make_INTEGER_LITERAL(atoi(yytext), loc); }

. { throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext)); }
<<EOF>> { return yy::parser::make_END(loc); }
%%