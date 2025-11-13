#pragma once
#include <string>
#include <vector>
#include "ast.hpp"

class CodeGen {
public:
    std::string generate(const std::vector<StmtPtr>& stmts);

private:
    std::string genExpr(const ExprPtr& e);
};
