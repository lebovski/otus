#pragma once

#include <string>

#include "astnode.hpp"

class Sub : public ASTNode
{
public:
    Sub(ASTNode *root, ASTNode *term) : ASTNode("-", root, term) {}
};