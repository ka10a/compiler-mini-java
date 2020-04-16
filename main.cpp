#include <MiniJavaParser.hh>
#include <MiniJavaLexer.hh>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        throw std::runtime_error("No filename provided");
    }

    yyscan_t scanner;
    if (yylex_init(&scanner)) {
        throw std::runtime_error("Scanner initialization failed");
    }

    const std::string file_name = argv[1];
    std::ifstream file(file_name);
    const std::string content(std::istreambuf_iterator<char>(file), {});

    YY_BUFFER_STATE state = yy_scan_string(content.c_str(), scanner);
    if (!state) {
        throw std::runtime_error("File scanning failed");
    }

    YYSTYPE val;
    std::cout << yylex(&val, scanner);
    return 0;
}
