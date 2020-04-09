%option reentrant noyywrap never-interactive nounistd
%option bison-bridge

%{
    #include <iostream>
    #include <string>
    #include <MiniJavaParser.hh>
%}

DIGIT           [0-9]
LETTER          [a-zA-Z]
Id              {LETTER}({DIGIT}|{LETTER})*
IntegerLiteral  [1-9]{DIGIT}*|0

%%

"class"         std::cout << "CLASS ";
"extends"       std::cout << "EXTENDS ";
{Id}            { std::cout << "ID ("  << std::string(yytext, yyleng) << ")"; return ID;}
"+"             { std::cout << "PLUS "; return PLUS; }
"*"             { std::cout << "MUL "; return MUL; }
"-"             { std::cout << "MINUS "; return MINUS; }
"/"             { std::cout << "DIV "; return DIV; }
" "             {}

%%
