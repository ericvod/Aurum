#include "aurum/Aurum.h"
#include <iostream>

int main(int argc, char *argv[])
{
    aurum::Interpreter interpreter;
    if (argc > 1)
    {
        try
        {
            interpreter.runFile(argv[1]);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }
    else
    {
        // Modo interativo
        std::string input;
        while (true)
        {
            std::cout << "Aurum> ";
            std::getline(std::cin, input);
            if (input == "exit")
                break;

            try
            {
                auto result = interpreter.interpret(input);
                if (result)
                {
                    if (std::holds_alternative<double>(*result))
                    {
                        std::cout << std::get<double>(*result) << std::endl;
                    }
                    else if (std::holds_alternative<std::string>(*result))
                    {
                        std::cout << '"' << std::get<std::string>(*result) << '"' << std::endl;
                    }
                    else if (std::holds_alternative<bool>(*result))
                    {
                        std::cout << (std::get<bool>(*result) ? "true" : "false") << std::endl;
                    }
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
    return 0;
}