%require "3.0"

%language "c++"
%define api.value.type variant

%lex-param { bool verbose }
%parse-param { MyScanner& scanner }
%parse-param { ASTRoot& root }
%locations

%code requires {
    class MyScanner;
    class ASTRoot;
}

%code {
    #include <MiniJavaLexer.hh>
    //#undef yylex
    //#define yylex yylex( scanner )
}

%union {
    const int Ptr;
}

%token <Ptr> ID
%token number
%token Class
%type <Ptr> exp

%%

exp:
    "number"
    | ID {$$ = $1;}
    | exp "+" exp {$$ = $1 + $3; }
    | exp "-" exp {$$ = $1 - $3; }
    | exp "*" exp {$$ = $1 * $3; }
    | exp "/" exp {$$ = $1 / $3; }
    | "(" exp ")" {$$ = $2; };

%%


// yyparse(...).
