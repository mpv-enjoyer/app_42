#include <stack>
#include <stdexcept>
#include <iostream>
#include <sstream>

#include "calculator.h"

std::optional<double> app42::ReversePolishCalculator::is_numeric(std::string const &str)
{
    double result = 0.0;
    auto i = std::istringstream(str);
    i >> result;
    
    if (!i.fail() && i.eof()) return result;
    else return std::optional<double>();
}

app42::ReversePolishCalculator::ReversePolishCalculator(std::string expression)
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
            if (values.size() < 2) throw std::invalid_argument("Numerical values mismatch");
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

double app42::ReversePolishCalculator::value()
{
    return m_value;
}

int app42::Calculator::get_precedence(std::string op)
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

std::string app42::Calculator::translate_to_reverse_polish(std::string expression)
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

app42::Calculator::Calculator(std::string expression)
: ReversePolishCalculator(translate_to_reverse_polish(expression)),
m_translated_expression(translate_to_reverse_polish(expression))
{

}

std::string app42::Calculator::getTranslated() const
{
    return m_translated_expression;
}
