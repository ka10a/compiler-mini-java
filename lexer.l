%option header-file="MiniJavaLexer.hh"
%option reentrant noyywrap never-interactive nounistd
%option bison-bridge
%option bison-locations

%{
#include <iostream>
#include <string>
#include <MiniJavaParser.hh>

int yylen;

%}

DIGIT           [0-9]
LETTER          [a-zA-Z]
Id              {LETTER}({DIGIT}|{LETTER})*
IntegerLiteral  [1-9]{DIGIT}*|0

%%

"class"         std::cout << "CLASS ";
"extends"       std::cout << "EXTENDS ";
{Id}            std::cout << "ID ("  << std::string(yytext, yylen) << ")";

%%
