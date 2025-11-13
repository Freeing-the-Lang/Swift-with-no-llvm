#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "parser.hpp"
#include "codegen.hpp"
#include "evaluator.hpp"

int main() {
    std::ifstream fin("src/main.swift");
    if (!fin.is_open()) {
        std::cout << "No Swift file found.\n";
        return 0;
    }

    std::string src((std::istreambuf_iterator<char>(fin)),
                     std::istreambuf_iterator<char>());

    Parser p(src);
    auto program = p.parseProgram();

    Evaluator eval;
    eval.run(program);

    CodeGen cg;
    std::string cpp = cg.generate(program);

    std::ofstream fout("out.cpp");
    fout << cpp;
    fout.close();

    std::cout << "[Generated C++] out.cpp created\n";
    return 0;
}
