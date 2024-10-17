#pragma once
#include "ASTNode.h"

namespace aurum
{
    class NumberNode : public ASTNode
    {
        double value;

    public:
        NumberNode(double v) : value(v) {}
        Value evaluate(std::unordered_map<std::string, Variable> &variables) override;
    };

    class StringNode : public ASTNode
    {
        std::string value;

    public:
        StringNode(const std::string &v) : value(v) {}
        Value evaluate(std::unordered_map<std::string, Variable> &variables) override;
    };

    class BoolNode : public ASTNode
    {
        bool value;

    public:
        BoolNode(bool v) : value(v) {}
        Value evaluate(std::unordered_map<std::string, Variable> &variables) override;
    };

    class BinaryOpNode : public ASTNode
    {
        std::unique_ptr<ASTNode> left, right;
        TokenType op;

    public:
        BinaryOpNode(std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r, TokenType o)
            : left(std::move(l)), right(std::move(r)), op(o) {}
        Value evaluate(std::unordered_map<std::string, Variable> &variables) override;
    };

    class VariableNode : public ASTNode
    {
        std::string name;

    public:
        VariableNode(const std::string &n) : name(n) {}
        Value evaluate(std::unordered_map<std::string, Variable> &variables) override;
    };

    class PrintNode : public ASTNode
    {
        std::unique_ptr<ASTNode> expression;

    public:
        PrintNode(std::unique_ptr<ASTNode> expr) : expression(std::move(expr)) {}
        Value evaluate(std::unordered_map<std::string, Variable> &variables) override;
    };

    class AssignmentNode : public ASTNode
    {
        std::string name;
        std::unique_ptr<ASTNode> value;
        ValueType type;

    public:
        AssignmentNode(const std::string &n, std::unique_ptr<ASTNode> v, ValueType t)
            : name(n), value(std::move(v)), type(t) {}
        Value evaluate(std::unordered_map<std::string, Variable> &variables) override;
    };

}