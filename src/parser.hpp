#pragma once
#include <string>
#include <vector>
#include "ast.hpp"

class Parser {
public:
    Parser(const std::string& src) : code(src) {}
    std::vector<StmtPtr> parseProgram();

private:
    std::string code;
};
