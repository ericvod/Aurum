#include "Parser.h"
#include "../ast/ExpressionNodes.h"
#include <stdexcept>

namespace aurum
{
    std::unique_ptr<ASTNode> Parser::parse()
    {
        return expression();
    }

    std::unique_ptr<ASTNode> Parser::expression()
    {
        if (peek().type == TokenType::PRINT)
        {
            advance();
            if (peek().type != TokenType::LPAREN)
                throw std::runtime_error("Expected '(' after 'print'");
            advance();
            auto expr = expression();
            if (peek().type != TokenType::RPAREN)
                throw std::runtime_error("Expected ')' after print expression");
            advance();
            return std::make_unique<PrintNode>(std::move(expr));
        }
        if (peek().type == TokenType::VAR ||
            peek().type == TokenType::NUMBER_TYPE ||
            peek().type == TokenType::STRING_TYPE ||
            peek().type == TokenType::BOOL_TYPE)
        {
            TokenType typeToken = advance().type;
            auto identifier = advance();
            if (identifier.type != TokenType::IDENTIFIER)
                throw std::runtime_error("Expected identifier after type declaration");
            if (advance().type != TokenType::EQUALS)
                throw std::runtime_error("Expected '=' after identifier in variable declaration");
            auto value = expression();
            ValueType varType;
            switch (typeToken)
            {
            case TokenType::VAR:
                varType = ValueType::NUMBER;
                break; // Default to NUMBER for var
            case TokenType::NUMBER_TYPE:
                varType = ValueType::NUMBER;
                break;
            case TokenType::STRING_TYPE:
                varType = ValueType::STRING;
                break;
            case TokenType::BOOL_TYPE:
                varType = ValueType::BOOL;
                break;
            default:
                throw std::runtime_error("Invalid type token");
            }
            return std::make_unique<AssignmentNode>(identifier.value, std::move(value), varType);
        }

        auto node = term();
        while (peek().type == TokenType::PLUS || peek().type == TokenType::MINUS)
        {
            auto op = advance().type;
            auto right = term();
            node = std::make_unique<BinaryOpNode>(std::move(node), std::move(right), op);
        }
        return node;
    }

    std::unique_ptr<ASTNode> Parser::term()
    {
        auto node = factor();
        while (peek().type == TokenType::MULTIPLY || peek().type == TokenType::DIVIDE)
        {
            auto op = advance().type;
            auto right = factor();
            node = std::make_unique<BinaryOpNode>(std::move(node), std::move(right), op);
        }
        return node;
    }

    std::unique_ptr<ASTNode> Parser::factor()
    {
        if (peek().type == TokenType::NUMBER)
        {
            return std::make_unique<NumberNode>(std::stod(advance().value));
        }
        else if (peek().type == TokenType::STRING)
        {
            return std::make_unique<StringNode>(advance().value);
        }
        else if (peek().type == TokenType::BOOL)
        {
            return std::make_unique<BoolNode>(advance().value == "true");
        }
        else if (peek().type == TokenType::IDENTIFIER)
        {
            return std::make_unique<VariableNode>(advance().value);
        }
        else if (peek().type == TokenType::LPAREN)
        {
            advance(); // Consume '('
            auto node = expression();
            if (advance().type != TokenType::RPAREN)
                throw std::runtime_error("Expected ')'");
            return node;
        }
        throw std::runtime_error("Unexpected token");
    }
}