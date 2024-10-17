#pragma once
#include "aurum/Common.h"

namespace aurum
{
    class Lexer
    {
        std::string input;
        size_t position = 0;

    public:
        Lexer(const std::string &in) : input(in) {}
        std::vector<Token> tokenize();

    private:
        char peek() const { return position < input.length() ? input[position] : '\0'; }
        char advance() { return position < input.length() ? input[position++] : '\0'; }
    };
}