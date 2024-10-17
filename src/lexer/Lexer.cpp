#include "Lexer.h"
#include <cctype>
#include <stdexcept>

namespace aurum
{
    std::vector<Token> Lexer::tokenize()
    {
        std::vector<Token> tokens;
        while (peek() != '\0')
        {
            if (std::isdigit(peek()))
            {
                std::string num;
                while (std::isdigit(peek()) || peek() == '.')
                    num += advance();
                tokens.emplace_back(TokenType::NUMBER, num);
            }
            else if (peek() == '"')
            {
                advance();
                std::string str;
                while (peek() != '"' && peek() != '\0')
                    str += advance();
                if (peek() == '"')
                    advance();
                else
                    throw std::runtime_error("Unterminated string");
                tokens.emplace_back(TokenType::STRING, str);
            }
            else if (std::isalpha(peek()))
            {
                std::string identifier;
                while (std::isalnum(peek()))
                    identifier += advance();
                if (identifier == "var")
                {
                    tokens.emplace_back(TokenType::VAR, identifier);
                }
                else if (identifier == "number")
                {
                    tokens.emplace_back(TokenType::NUMBER_TYPE, identifier);
                }
                else if (identifier == "string")
                {
                    tokens.emplace_back(TokenType::STRING_TYPE, identifier);
                }
                else if (identifier == "bool")
                {
                    tokens.emplace_back(TokenType::BOOL_TYPE, identifier);
                }
                else if (identifier == "true" || identifier == "false")
                {
                    tokens.emplace_back(TokenType::BOOL, identifier);
                }
                else if (identifier == "print")
                {
                    tokens.emplace_back(TokenType::PRINT, identifier);
                }

                else
                {
                    tokens.emplace_back(TokenType::IDENTIFIER, identifier);
                }
            }
            else
            {
                switch (advance())
                {
                case '+':
                    tokens.emplace_back(TokenType::PLUS, "+");
                    break;
                case '-':
                    tokens.emplace_back(TokenType::MINUS, "-");
                    break;
                case '*':
                    tokens.emplace_back(TokenType::MULTIPLY, "*");
                    break;
                case '/':
                    tokens.emplace_back(TokenType::DIVIDE, "/");
                    break;
                case '(':
                    tokens.emplace_back(TokenType::LPAREN, "(");
                    break;
                case ')':
                    tokens.emplace_back(TokenType::RPAREN, ")");
                    break;
                case '=':
                    tokens.emplace_back(TokenType::EQUALS, "=");
                    break;
                case ' ':
                case '\t':
                case '\n':
                    break; // Ignore whitespace
                default:
                    throw std::runtime_error("Invalid character");
                }
            }
        }
        return tokens;
    }
}