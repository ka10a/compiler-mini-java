%option noyywrap

%{
#include <iostream>
#include <parser.hpp>

#define YY_DECL yy::parser::symbol_type yylex()

%}

DIGIT            [0-9]
CHARACTER        [a-zA-Z_]
IDENTIFIER       {CHARACTER}({CHARACTER}|{DIGIT})*
INTEGER_LITERAL  [1-9]{DIGIT}*|0
COMMENT          "//".*

%%
[ \t\n]|{COMMENT} { }

"!"  { return yy::parser::make_NOT(); }
"&&" { return yy::parser::make_AND(); }
"<"  { return yy::parser::make_LESS(); }
"+"  { return yy::parser::make_PLUS(); }
"-"  { return yy::parser::make_MINUS(); }
"*"  { return yy::parser::make_MUL(); }

"{" { return yy::parser::make_OCURLY(); }
"}" { return yy::parser::make_CCURLY(); }
"[" { return yy::parser::make_OSQUARE(); }
"]" { return yy::parser::make_CSQUARE(); }
"(" { return yy::parser::make_OPAREN(); }
")" { return yy::parser::make_CPAREN(); }
"=" { return yy::parser::make_ASSIGN(); }
"," { return yy::parser::make_COMMA(); }
"." { return yy::parser::make_DOT(); }
";" { return yy::parser::make_SCOLON(); }

"String"  { return yy::parser::make_STRING(); }
"int"     { return yy::parser::make_INT(); }
"boolean" { return yy::parser::make_BOOL(); }

"true"  { return yy::parser::make_TRUE(); }
"false" { return yy::parser::make_FALSE(); }

"class"   { return yy::parser::make_CLASS(); }
"public"  { return yy::parser::make_PUBLIC(); }
"static"  { return yy::parser::make_STATIC(); }
"void"    { return yy::parser::make_VOID(); }
"main"    { return yy::parser::make_MAIN(); }
"extends" { return yy::parser::make_EXTENDS(); }
"return"  { return yy::parser::make_RETURN(); }
"this"    { return yy::parser::make_THIS(); }
"new"     { return yy::parser::make_NEW(); }

"if"    { return yy::parser::make_IF(); }
"else"  { return yy::parser::make_ELSE(); }
"while" { return yy::parser::make_WHILE(); }

"System.out.println" { return yy::parser::make_PRINT(); }
".length" { return yy::parser::make_LENGTH(); }

{IDENTIFIER}      { return yy::parser::make_IDENTIFIER(std::string(yytext)); }
{INTEGER_LITERAL} { return yy::parser::make_INTEGER_LITERAL(atoi(yytext)); }

. { std::cerr << "scanning error: " << yytext; }
%%