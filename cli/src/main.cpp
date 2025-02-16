#include <cstdlib>
#include <iostream>

#include "parser.h"
#include "sender.h"

void print_usage_error(const char* name)
{
    std::cerr << " " << "Usage:" << std::endl
            << "  " << name << " -c echo" << std::endl
            << "  " << name << " -e [expr]" << std::endl;
}

int main(int argc, char *argv[])
{
    auto parsed_info = app42::parse(argc, argv, "ce");
    if (!parsed_info) {
        print_usage_error(argv[0]);
        return EXIT_FAILURE;
    }
    switch (parsed_info->parameter)
    {
    case 'c':
        std::cout << app42::send("cmd", parsed_info->argument) << std::endl;
        break;
    case 'e':
        std::cout << app42::send("exp", parsed_info->argument) << std::endl;
        break;
    }
}
