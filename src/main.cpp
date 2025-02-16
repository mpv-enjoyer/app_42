#include <iostream>

#include "server.h"
#include "calculator.h"

int main(int argc, char *argv[])
{
    std::cout << ReversePolishCalculator("2 2 + 4 +").value() << "\n";
    std::cout << ReversePolishCalculator("1").value() << "\n";
    std::cout << ReversePolishCalculator("42 0 + 42 /").value() << "\n";
    std::cout << ReversePolishCalculator("2 2 * 2 +").value() << "\n";
    std::cout << ReversePolishCalculator("75 4 / 90 + 2 -").value() << "\n";

    Calculator c0("2 + 1");
    std::cout << c0.get_translated() << " = " << c0.value() << "\n";
    Calculator c1("2 + 2 * 2");
    std::cout << c1.get_translated() << " = " << c1.value() << "\n";
    Calculator c2("( 2 + 2 ) * 2");
    std::cout << c2.get_translated() << " = " << c2.value() << "\n";
    Calculator c3("1 / ( 1 * ( 2 + 4 ) / 4.13412 ) * ( 9 + 0 ) / 3");
    std::cout << c3.get_translated() << " = " << c3.value() << "\n";
    return app42::echoServer(argc, argv);
}