#pragma once
#include <string>
#include <vector>

struct Node {
    std::string kind;     // "func", "assign", "print"
    std::string name;
    std::string value;
    std::vector<Node*> children;
};
