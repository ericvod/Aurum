#include "ExpressionNodes.h"
#include <stdexcept>
#include <iostream>

namespace aurum
{
    Value NumberNode::evaluate(std::unordered_map<std::string, Variable> &variables)
    {
        return value;
    }

    Value StringNode::evaluate(std::unordered_map<std::string, Variable> &variables)
    {
        return value;
    }

    Value BoolNode::evaluate(std::unordered_map<std::string, Variable> &variables)
    {
        return value;
    }

    Value BinaryOpNode::evaluate(std::unordered_map<std::string, Variable> &variables)
    {
        Value l = left->evaluate(variables);
        Value r = right->evaluate(variables);

        if (std::holds_alternative<double>(l) && std::holds_alternative<double>(r))
        {
            double lv = std::get<double>(l);
            double rv = std::get<double>(r);
            switch (op)
            {
            case TokenType::PLUS:
                return lv + rv;
            case TokenType::MINUS:
                return lv - rv;
            case TokenType::MULTIPLY:
                return lv * rv;
            case TokenType::DIVIDE:
                if (rv == 0)
                    throw std::runtime_error("Division by zero");
                return lv / rv;
            default:
                throw std::runtime_error("Invalid operator for numbers");
            }
        }
        else if (std::holds_alternative<std::string>(l) && std::holds_alternative<std::string>(r))
        {
            std::string lv = std::get<std::string>(l);
            std::string rv = std::get<std::string>(r);
            if (op == TokenType::PLUS)
                return lv + rv;
            else
                throw std::runtime_error("Invalid operator for strings");
        }
        else
        {
            throw std::runtime_error("Type mismatch in binary operation");
        }
    }

    Value VariableNode::evaluate(std::unordered_map<std::string, Variable> &variables)
    {
        if (variables.find(name) == variables.end())
            throw std::runtime_error("Undefined variable: " + name);
        return variables[name].value;
    }

    Value PrintNode::evaluate(std::unordered_map<std::string, Variable> &variables)
    {
        Value result = expression->evaluate(variables);
        if (std::holds_alternative<double>(result))
        {
            std::cout << std::get<double>(result);
        }
        else if (std::holds_alternative<std::string>(result))
        {
            std::cout << std::get<std::string>(result);
        }
        else if (std::holds_alternative<bool>(result))
        {
            std::cout << (std::get<bool>(result) ? "true" : "false");
        }
        std::cout << std::endl;
        return result;
    }

    Value AssignmentNode::evaluate(std::unordered_map<std::string, Variable> &variables)
    {
        Value val = value->evaluate(variables);

        if (type == ValueType::NUMBER && !std::holds_alternative<double>(val))
        {
            throw std::runtime_error("Type mismatch: expected number");
        }
        else if (type == ValueType::STRING && !std::holds_alternative<std::string>(val))
        {
            throw std::runtime_error("Type mismatch: expected string");
        }
        else if (type == ValueType::BOOL && !std::holds_alternative<bool>(val))
        {
            throw std::runtime_error("Type mismatch: expected boolean");
        }

        variables[name] = {type, val};
        return val;
    }
}