#include <MiniJava.Lexer.h>

int main() {
// TODO: yy_scan_string
    const char *str = "abacaba haha";

    yy_scan_string(str);
    yylex();
    return 0;
}