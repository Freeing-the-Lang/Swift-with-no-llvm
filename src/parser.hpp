#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "ast.hpp"

std::vector<Node*> parseSwift(const std::string &code) {
    std::vector<Node*> tree;
    std::istringstream ss(code);
    std::string line;

    while (std::getline(ss, line)) {
        if (line.find("func ") == 0) {
            auto *n = new Node();
            n->kind = "func";
            auto start = line.find("func ") + 5;
            auto end = line.find("(");
            n->name = line.substr(start, end - start);
            tree.push_back(n);
        } else if (line.find("let ") == 0) {
            auto *n = new Node();
            n->kind = "assign";
            auto eq = line.find("=");
            n->name = line.substr(4, eq - 5);
            n->value = line.substr(eq + 1);
            tree.push_back(n);
        } else if (line.find("print(") != std::string::npos) {
            auto *n = new Node();
            n->kind = "print";
            auto start = line.find("(") + 1;
            auto end = line.find(")");
            n->value = line.substr(start, end - start);
            tree.push_back(n);
        }
    }
    return tree;
}
