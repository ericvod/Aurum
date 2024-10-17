#pragma once
#include "aurum/Common.h"

namespace aurum
{
    class ASTNode
    {
    public:
        virtual ~ASTNode() = default;
        virtual Value evaluate(std::unordered_map<std::string, Variable>& variables) = 0;
    };
}