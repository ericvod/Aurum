#pragma once
#include "Common.h"
#include <optional>

namespace aurum
{
    class Interpreter
    {
        std::unordered_map<std::string, Variable> variables;

    public:
        std::optional<Value> interpret(const std::string &input);
        std::string getType(const std::string &varName);
        void runFile(const std::string &filename);
    };
}