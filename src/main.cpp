#include <iostream>
#include <string>
#include "compiler.h"

int main() {
    Compiler compiler;
    std::string sourceFileName;

    std::cout << "Enter test file name to test(make sure it ends with """".txt""""): ";
    std::cin >> sourceFileName;
    compiler.run(sourceFileName);

    return 0;
}
