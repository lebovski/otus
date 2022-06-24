#pragma once

#include <string>

#include "astnode.hpp"

class Div : public ASTNode
{
public:
    Div(ASTNode *root, ASTNode *term) : ASTNode("\\", root, term) {}
};