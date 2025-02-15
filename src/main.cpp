#include <string>
#include <sstream>
#include <optional>
#include <stack>
#include <memory>
#include <iostream>

#include "server.h"

class Operation
{
protected:
    std::optional<double> m_left_value;
    Operation() { };
public:
    void setLeftValue(double left_value)
    {
        m_left_value.emplace(left_value);
    };
    bool isLeftValueSet() const
    {
        return m_left_value.has_value();
    };
    virtual double get(double right_value) const = 0;
};

class Add : public Operation
{
public:
    Add() { };
    double get(double right_value) const override
    {
        return m_left_value.value() + right_value;
    }
};

class Subtract : public Operation
{
public:
    Subtract() { };
    double get(double right_value) const override
    {
        return m_left_value.value() - right_value;
    }
};

class Product : public Operation
{
public:
    Product() { };
    double get(double right_value) const override
    {
        return m_left_value.value() * right_value;
    }
};

class Divide : public Operation
{
public:
    Divide() { };
    double get(double right_value) const override
    {
        return m_left_value.value() / right_value;
    }
};

// Polish notation
class Calculator
{
    std::stack<std::unique_ptr<Operation>> m_operations;
    double m_value = 0;
    std::optional<double> is_numeric(std::string const& str) 
    {
        double result = 0.0;
        auto i = std::istringstream(str);
        i >> result;
        
        if (!i.fail() && i.eof()) return result;
        else return std::optional<double>();
    }
    bool process_number(double value)
    {
        while (!m_operations.empty())
        {
            auto& operation = m_operations.top();
            if (!operation->isLeftValueSet())
            {
                operation->setLeftValue(value);
                return true;
            }
            else
            {
                value = operation->get(value);
                m_operations.pop();
            }
        }
        m_value = value;
        return false;
    }
public:
    Calculator(std::string expression)
    {
        auto i = std::istringstream(expression);
        std::string word;
        while (i >> word)
        {
            auto number = is_numeric(word);
            if (number)
            {
                if (!process_number(number.value())) break;
            }
            else
            {
                if (word == std::string("+")) m_operations.push(std::make_unique<Add>());
                if (word == std::string("-")) m_operations.push(std::make_unique<Subtract>());
                if (word == std::string("*")) m_operations.push(std::make_unique<Product>());
                if (word == std::string("/")) m_operations.push(std::make_unique<Divide>());
            }
        }
    }
    double value()
    {
        return m_value;
    };
};

int main(int argc, char *argv[])
{
    std::cout << Calculator("+ 2 + 2 4").value() << "\n";
    std::cout << Calculator("1").value() << "\n";
    std::cout << Calculator("+ 42 + 42 0").value() << "\n";
    std::cout << Calculator("+ 2 * 2 2").value() << "\n";
    std::cout << Calculator("/ 75 + * 4 90 2").value() << "\n";
    //return app42::echoServer(argc, argv);
}