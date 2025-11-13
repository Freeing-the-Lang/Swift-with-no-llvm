#include "parser.hpp"
#include "codegen.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

int main() {
    std::ifstream f("src/main.swift");
    if (!f.is_open()) {
        std::cerr << "src/main.swift not found\n";
        return 1;
    }

    std::stringstream ss;
    ss << f.rdbuf();

    Parser p(ss.str());
    auto program = p.parseProgram();

    CodeGen cg;
    std::string cpp = cg.generate(program);

    std::ofstream out("out.cpp");
    out << cpp;
    out.close();

    std::cout << "Generated out.cpp\n";
    return 0;
}
