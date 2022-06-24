#pragma once

#include <string>

#include "astnode.hpp"

class Add : public ASTNode
{
public:
    Add(ASTNode *root, ASTNode *term) : ASTNode("+", root, term) {}
};