#pragma once

#include <string>

#include "astnode.hpp"

class Number : public ASTNode
{
public:
  Number(int val) : ASTNode(std::to_string(val)) {}
};
