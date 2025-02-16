/*
 *    Copyright (c) <2002-2005> <Jean-Philippe Barrette-LaPierre>
 *    
 *    Permission is hereby granted, free of charge, to any person obtaining
 *    a copy of this software and associated documentation files 
 *    (curlpp), to deal in the Software without restriction, 
 *    including without limitation the rights to use, copy, modify, merge,
 *    publish, distribute, sublicense, and/or sell copies of the Software,
 *    and to permit persons to whom the Software is furnished to do so, 
 *    subject to the following conditions:
 *    
 *    The above copyright notice and this permission notice shall be included
 *    in all copies or substantial portions of the Software.
 *    
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 *    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 *    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
 *    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 *    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 *    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
/**
* \file
* Using options::Url as stream input.
* 
*/
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