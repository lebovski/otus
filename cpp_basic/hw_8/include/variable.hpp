#pragma once

#include <string>
#include <iostream>

#include "astnode.hpp"

class Variable : public ASTNode
{
public:
    Variable(std::string val) : ASTNode(val) {}
};