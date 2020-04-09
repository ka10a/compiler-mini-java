//%require "3.0"

%define api.pure
%param { yyscan_t scanner }
//%parse-param { ASTRoot& root }
//%locations

%code requires {
    #ifndef YY_TYPEDEF_YY_SCANNER_T
    #define YY_TYPEDEF_YY_SCANNER_T
    typedef void* yyscan_t;
    #endif
    //class MyScanner;
    //class ASTRoot;
}

%code {
}

%{
    #include <MiniJavaParser.hh>
    #include <MiniJavaLexer.hh>
    #include <iostream>

    int yyerror( yyscan_t scanner, int& result, const char* msg )
    {
        std::cerr << "kerror called: '" << msg << "'" << std::endl;
        return 0;
    }
%}

%union {
    int Ptr;
}

%token <Ptr> ID
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
