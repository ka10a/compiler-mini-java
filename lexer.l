%option reentrant noyywrap never-interactive nounistd
%option bison-bridge

%{
    #include <iostream>
    #include <string>
    #include <MiniJavaParser.hh>
%}

DIGIT           [0-9]
LETTER          [a-zA-Z]
Id              ({LETTER}|_)({LETTER}|{DIGIT}|_)*
IntegerLiteral  [1-9]{DIGIT}*|0

%%
"class"         { std::cout << "CLASS";                                     }
"extends"       { std::cout << "EXTENDS";                                   }
{Id}            { std::cout << "ID(" << std::string(yytext, yyleng) << ")"; }
"+"             { std::cout << "PLUS";                                      }
"*"             { std::cout << "MUL";                                       }
"-"             { std::cout << "MINUS";                                     }
"/"             { std::cout << "DIV";                                       }
" "             { std::cout << " ";                                         }
%%
