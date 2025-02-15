#include <string>
#include <sstream>
#include <optional>
#include <stack>
#include <memory>
#include <iostream>
#include <stdexcept>

#include "server.h"

// Reverse polish notation
class ReversePolishCalculator
{
    double m_value = 0;
protected:
    std::optional<double> is_numeric(std::string const& str) 
    {
        double result = 0.0;
        auto i = std::istringstream(str);
        i >> result;
        
        if (!i.fail() && i.eof()) return result;
        else return std::optional<double>();
    }
public:
    ReversePolishCalculator(std::string expression)
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

class Calculator : public ReversePolishCalculator
{
    const std::string m_translated_expression;
    int get_precedence(std::string op)
    {
        switch (op[0])
        {
        case '(': return 2;
        case '+': return 1;
        case '-': return 1;
        case '*': return 0;
        case '/': return 0;
        default: throw std::invalid_argument("Invalid operator");
        };
    }
    std::string translate_to_reverse_polish(std::string expression)
    {
        auto i = std::istringstream(expression);
        std::string word;
        std::stack<std::string> operators;
        std::string output;
        output.reserve(expression.size());
        while (i >> word)
        {
            auto number = is_numeric(word);
            if (number)
            {
                output.append(std::to_string(number.value()));
                output.append(" ");
                continue;
            }
            if (word == std::string("("))
            {
                operators.push("(");
                continue;
            }
            if (word == std::string(")"))
            {
                while (operators.top() != std::string("("))
                {
                    output.append(operators.top());
                    output.append(" ");
                    operators.pop();
                }
                operators.pop();
                continue;
            }
            while (!operators.empty() && get_precedence(operators.top()) <= get_precedence(word))
            {
                output.append(operators.top());
                output.append(" ");
                operators.pop();
            }
            operators.push(word);
        }
        while (!operators.empty())
        {
            output.append(operators.top());
            output.append(" ");
            operators.pop();
        }
        return output;
    }
public:
    Calculator(std::string expression)
    : ReversePolishCalculator(translate_to_reverse_polish(expression)), m_translated_expression(translate_to_reverse_polish(expression))
    { }
    std::string get_translated() const
    {
        return m_translated_expression;
    };
};

int main(int argc, char *argv[])
{
    std::cout << ReversePolishCalculator("2 2 + 4 +").value() << "\n";
    std::cout << ReversePolishCalculator("1").value() << "\n";
    std::cout << ReversePolishCalculator("42 0 + 42 /").value() << "\n";
    std::cout << ReversePolishCalculator("2 2 * 2 +").value() << "\n";
    std::cout << ReversePolishCalculator("75 4 / 90 + 2 -").value() << "\n";

    Calculator c1("2 + 2 * 2");
    std::cout << c1.get_translated() << " = " << c1.value() << "\n";
    Calculator c2("( 2 + 2 ) * 2");
    std::cout << c2.get_translated() << " = " << c2.value() << "\n";
    Calculator c3("1 / ( 1 * ( 2 + 4 ) / 4.13412 ) * ( 9 + 0 ) / 3");
    std::cout << c3.get_translated() << " = " << c3.value() << "\n";
    //return app42::echoServer(argc, argv);
}