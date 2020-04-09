%require "3.0"

// %language "c++"
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
// %token <Number> Number
%token Class
%type <Ptr> exp

%token PLUS
%token MUL
%token MINUS
%token DIV

%%

exp:
    ID {$$ = $1;}
    | exp[L] PLUS exp[R] {$$ = $L + $R; }
    | exp[L] MINUS exp[R] {$$ = $L - $R; }
    | exp[L] MUL exp[R] {$$ = $L * $R; }
    | exp[L] DIV exp[R] {$$ = $L / $R; }
    | "(" exp ")" {$$ = $2; };

%%


// yyparse(...).
