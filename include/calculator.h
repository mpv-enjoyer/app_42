#pragma once

#include <string>
#include <optional>

namespace app42
{
    class ReversePolishCalculator
    {
        double m_value = 0;
    protected:
        std::optional<double> is_numeric(std::string const& str);
    public:
        ReversePolishCalculator(std::string expression);
        double value();
    };
    
    class Calculator : public ReversePolishCalculator
    {
        const std::string m_translated_expression;
        int get_precedence(std::string op);
        std::string translate_to_reverse_polish(std::string expression);
    public:
        Calculator(std::string expression);
        std::string getTranslated() const;
    };
}