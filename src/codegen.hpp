#pragma once
#include <iostream>
#include <fstream>
#include "ast.hpp"

void generateCPP(const std::vector<Node*> &tree, const std::string &out) {
    std::ofstream f(out);
    f << "#include <iostream>\nusing namespace std;\n\n";

    for (auto *n : tree) {
        if (n->kind == "func") {
            f << "int " << n->name << "() {\n";
        } else if (n->kind == "assign") {
            f << "    auto " << n->name << " = " << n->value << ";\n";
        } else if (n->kind == "print") {
            f << "    cout << " << n->value << " << endl;\n";
        }
    }

    f << "    return 0;\n}\n";
    f.close();
}
