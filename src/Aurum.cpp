#include "aurum/Aurum.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace aurum
{
    std::optional<Value> Interpreter::interpret(const std::string &input)
    {
        if (input.substr(0, 8) == "getType(")
        {
            size_t end = input.find(')', 8);
            if (end != std::string::npos)
            {
                std::string varName = input.substr(8, end - 8);
                if (varName.front() == '"' && varName.back() == '"')
                {
                    varName = varName.substr(1, varName.length() - 2);
                }
                std::cout << "Type of '" << varName << "': " << getType(varName) << std::endl;
                return std::nullopt; // Retorna um valor opcional vazio
            }
        }

        Lexer lexer(input);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.parse();
        Value result = ast->evaluate(variables);
        variables["_last"] = {
            std::holds_alternative<double>(result) ? ValueType::NUMBER : std::holds_alternative<std::string>(result) ? ValueType::STRING
                                                                                                                     : ValueType::BOOL,
            result};
        return result;
    }

    std::string Interpreter::getType(const std::string &varName)
    {
        if (variables.find(varName) == variables.end())
        {
            return "undefined";
        }

        switch (variables[varName].type)
        {
        case ValueType::NUMBER:
            return "number";
        case ValueType::STRING:
            return "string";
        case ValueType::BOOL:
            return "bool";
        default:
            return "unknown";
        }
    }

    void Interpreter::runFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Unable to open file: " + filename);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();

        std::istringstream iss(content);
        std::string line;
        while (std::getline(iss, line))
        {
            if (!line.empty())
            {
                try
                {
                    interpret(line);
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            }
        }
    }
}