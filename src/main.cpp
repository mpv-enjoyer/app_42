#include <string>
#include <sstream>
#include <optional>
#include <stack>
#include <memory>
#include <iostream>
#include <stdexcept>

#include "server.h"

// Reverse polish notation
class Calculator
{
    double m_value = 0;
    std::optional<double> is_numeric(std::string const& str) 
    {
        double result = 0.0;
        auto i = std::istringstream(str);
        i >> result;
        
        if (!i.fail() && i.eof()) return result;
        else return std::optional<double>();
    }
public:
    Calculator(std::string expression)
    {
        auto i = std::istringstream(expression);
        std::string word;
        std::stack<double> values;
        while (i >> word)
        {
            auto number = is_numeric(word);
            if (number)
            {
                values.push(number.value());
            }
            else
            {
                double right = values.top();
                values.pop();
                double left = values.top();
                values.pop();
                if (word == std::string("+")) values.push(left + right);
                if (word == std::string("-")) values.push(left - right);
                if (word == std::string("*")) values.push(left * right);
                if (word == std::string("/")) values.push(left / right);
            }
        }
        if (values.size() == 0)
        {
            m_value = 0;
        }
        else
        {
            m_value = values.top();
        }
    }
    double value()
    {
        return m_value;
    };
};

int main(int argc, char *argv[])
{
    std::cout << Calculator("2 2 + 4 +").value() << "\n";
    std::cout << Calculator("1").value() << "\n";
    std::cout << Calculator("42 0 + 42 /").value() << "\n";
    std::cout << Calculator("2 2 * 2 +").value() << "\n";
    std::cout << Calculator("75 4 / 90 + 2 -").value() << "\n";
    //return app42::echoServer(argc, argv);
}