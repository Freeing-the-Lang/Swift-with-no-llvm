#pragma once
#include <iostream>
#include <fstream>
#include "ast.hpp"

void generateCPP(const std::vector<Node*> &tree, const std::string &out) {
    std::ofstream f(out);
    f << "#include <iostream>\nusing namespace std;\n\n";

    bool opened = false;
    for (auto *n : tree) {
        if (n->kind == "func") {
            f << "int " << n->name << "() {\n";
            opened = true;
        } else if (n->kind == "assign") {
            f << "    auto " << n->name << " = " << n->value << ";\n";
        } else if (n->kind == "print") {
            f << "    cout << " << n->value << " << endl;\n";
        }
    }

    // ✅ 자동 보정 — 함수 블록이 없으면 main 생성
    if (opened) {
        f << "    return 0;\n}\n";
    } else {
        f << "int main() {\n";
        for (auto *n : tree) {
            if (n->kind == "assign") {
                f << "    auto " << n->name << " = " << n->value << ";\n";
            } else if (n->kind == "print") {
                f << "    cout << " << n->value << " << endl;\n";
            }
        }
        f << "    return 0;\n}\n";
    }

    f.close();
}
