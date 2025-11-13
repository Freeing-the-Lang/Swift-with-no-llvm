#include "parser.hpp"
#include <sstream>

std::vector<StmtPtr> Parser::parseProgram() {
    std::vector<StmtPtr> result;

    std::istringstream ss(code);
    std::string line;

    while (std::getline(ss, line)) {
        if (line.rfind("print(", 0) == 0) {
            auto inside = line.substr(6, line.size() - 7);
            int v = std::stoi(inside);
            result.push_back(std::make_shared<ExprStmt>(
                std::make_shared<PrintExpr>(
                    std::make_shared<NumberExpr>(v)
                )
            ));
        }
    }
    return result;
}
