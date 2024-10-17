#pragma once
#include "aurum/Common.h"
#include "../ast/ASTNode.h"

namespace aurum
{
    class Parser
    {
        std::vector<Token> tokens;
        size_t position = 0;

    public:
        Parser(const std::vector<Token> &t) : tokens(t) {}
        std::unique_ptr<ASTNode> parse();

    private:
        Token peek() const { return position < tokens.size() ? tokens[position] : Token(TokenType::END, ""); }
        Token advance() { return position < tokens.size() ? tokens[position++] : Token(TokenType::END, ""); }
        std::unique_ptr<ASTNode> expression();
        std::unique_ptr<ASTNode> term();
        std::unique_ptr<ASTNode> factor();
    };
}