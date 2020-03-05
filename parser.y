%require "3.2"

%language "c++"
%define api.value.type variant

%lex-param { bool verbose }
%parse-param {MyScanner* scanner }
%parse-param { ASTRoot root }
%locations
%code {
    #undef yylex
    #define yylex scanner->yylex
}

%%

exp:
    "number"
    | "identifier" {$$ = driver.variables[$1];}
    | exp "+" exp {$$ = $1 + $3; }
    | exp "-" exp {$$ = $1 - $3; }
    | exp "*" exp {$$ = $1 * $3; }
    | exp "/" exp {$$ = $1 / $3; }
    | "(" exp ")" {$$ = $2; };

%%


// yyparse(...).
