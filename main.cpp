#include <MiniJava.Lexer.h>
#include <fstream>
#include <sstream>
#include <string>
#include <streambuf>
//#include <ios_ba>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        throw std::runtime_error("No filename for scan");
    }

// TODO: add more options: lex, bison, etc.

    yyscan_t scanner;
    if (yylex_init(&scanner)) {
        throw std::runtime_error("Failed initialization scanner");
    }

    const std::string file_name = argv[1];
    std::cerr << file_name << std::endl;

    std::ifstream file(file_name, std::ios_base::in);
    std::stringstream content;
    content << file.rdbuf();

//    std::cout << content.str() << std::endl;


//    std::string my_string(
//            std::istreambuf_iterator<char>(file),
//            std::istreambuf_iterator<char>()
//                    );
//
//    std::cout << my_string << std::endl;

    YY_BUFFER_STATE state = yy_scan_string(content.str().c_str(), scanner);

//    if (state) {
//        throw std::runtime_error("Failed scanning string");
//    }

    std::cout << yylex(scanner);


    return 0;
}