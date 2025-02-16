#include "parser.h"

std::optional<app42::ParsedArgs> app42::parse(int argc, char *argv[], const std::string& parameters)
{
    if (argc < 3) return std::optional<ParsedArgs>();
    std::string input_parameter = argv[1];
    if (input_parameter[0] != '-') return std::optional<ParsedArgs>();
    if (input_parameter.size() != 2) return std::optional<ParsedArgs>();
    char input_parameter_char = input_parameter[1];
    for (auto c : parameters)
    {
        if (c == input_parameter_char)
        {
            std::string argument;
            for (int i = 2; i < argc; i++)
            {
                argument.append(argv[i]);
                if (i + 1 != argc) argument.append(" ");
            }
            return ParsedArgs{ .parameter = c, .argument = argument };
        }
    }
    return std::optional<ParsedArgs>();
}