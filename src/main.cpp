#include "parser.hpp"
#include "codegen.hpp"
#include <fstream>
#include <sstream>

int main() {
    std::ifstream f("src/main.swift");
    if (!f.is_open()) {
        std::cerr << "main.swift not found\n";
        return 1;
    }

    std::stringstream ss;
    ss << f.rdbuf();

    Parser parser(ss.str());
    auto program = parser.parseProgram();

    Evaluator eval;
    eval.run(program);

    return 0;
}
