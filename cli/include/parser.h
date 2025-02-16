#pragma once

#include <string>
#include <optional>

namespace app42
{
    struct ParsedArgs
    {
        char parameter;
        std::string argument;
    };
    std::optional<ParsedArgs> parse(int argc, char* argv[], const std::string& parameters);
}
