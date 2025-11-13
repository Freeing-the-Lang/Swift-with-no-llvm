#include "codegen.hpp"
#include <sstream>

std::string CodeGen::generate(const std::vector<StmtPtr>& stmts) {
    std::ostringstream out;

    out << "#include <iostream>\nusing namespace std;\nint main(){\n";

    for (auto& s : stmts) {
        if (auto es = std::dynamic_pointer_cast<ExprStmt>(s)) {
            if (auto p = std::dynamic_pointer_cast<PrintExpr>(es->expr)) {
                out << "    cout << " << genExpr(p->value) << " << endl;\n";
            }
        }
    }

    out << "    return 0;\n}\n";
    return out.str();
}

std::string CodeGen::genExpr(const ExprPtr& e) {
    if (auto n = std::dynamic_pointer_cast<NumberExpr>(e)) {
        return std::to_string(n->value);
    }
    return "0";
}
