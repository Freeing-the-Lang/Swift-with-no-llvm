#pragma once
#include "ast.hpp"
#include <string>
#include <vector>

class CodeGen {
public:
    std::string generate(const std::vector<StmtPtr>& prog);

private:
    std::string genExpr(const ExprPtr& e);
};
