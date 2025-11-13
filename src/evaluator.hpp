#pragma once

#include "ast.hpp"
#include <vector>
#include <iostream>

class Evaluator {
public:
    void run(const std::vector<StmtPtr>& stmts);
};
