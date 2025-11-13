#pragma once
#include "ast.hpp"
#include <unordered_map>
#include <iostream>

class Evaluator {
public:
    std::unordered_map<std::string, std::variant<double, std::string, bool>> env;

    void run(const std::vector<StmtPtr>& program);

private:
    std::variant<double, std::string, bool> evalExpr(const ExprPtr& e);
};
