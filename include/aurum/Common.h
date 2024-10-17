#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <variant>

namespace aurum
{
    enum class TokenType
    {
        NUMBER,
        STRING,
        BOOL,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        LPAREN,
        RPAREN,
        IDENTIFIER,
        EQUALS,
        VAR,
        NUMBER_TYPE,
        STRING_TYPE,
        BOOL_TYPE,
        PRINT,
        END,
    };

    struct Token
    {
        TokenType type;
        std::string value;
        Token(TokenType t, const std::string &v) : type(t), value(v) {}
    };

    enum class ValueType
    {
        NUMBER,
        STRING,
        BOOL,
    };

    using Value = std::variant<double, std::string, bool>;

    struct Variable
    {
        ValueType type;
        Value value;
    };
}
