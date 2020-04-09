%require "3.0"

%language "c++"
// %define api.value.type variant

%lex-param { bool verbose }
%parse-param { MyScanner& scanner }
%parse-param { ASTRoot& root }
%locations

%code requires {
    class MyScanner;
    class ASTRoot;
}

%code {
    //#include <MiniJavaLexer.hh>
    //#undef yylex
    //#define yylex yylex( scanner )
}

%{
    #include <MiniJavaParser.hh>
    #include <MiniJavaLexer.hh>
    #include <iostream>
%}

%union {
    const int Ptr;
}

%token <Ptr> ID
%token <Number> Number
%token Class
%type <Ptr> exp

%%

exp:
    Number ID {$$ = $1;}
    | exp[L] "+" exp[R] {$$ = $L + $R; }
    | exp[L] "-" exp[R] {$$ = $L - $R; }
    | exp[L] "*" exp[R] {$$ = $L * $R; }
    | exp[L] "/" exp[R] {$$ = $L / $R; }
    | "(" exp ")" {$$ = $2; };

%%


// yyparse(...).
