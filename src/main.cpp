#include <iostream>
#include <fstream>
#include "parser.hpp"
#include "codegen.hpp"

int main() {
    std::ifstream in("swift_sample.swift");
    std::string code((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    auto ast = parseSwift(code);
    generateCPP(ast, "out.cpp");

    system("g++ -S -masm=intel out.cpp -o out.asm");
    std::cout << "✅ Generated out.cpp and out.asm\n";
    return 0;
}
