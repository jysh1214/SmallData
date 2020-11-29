#include "smalldata.h"
#include <iostream>

int main()
{
    sd::Parser p;
    sd::DataFrame df = p.readCVS("../../data/test.csv").splitBy(',').withDefaultHeaders().createDF();


    for (auto row: df.dfIterator()) {
        std::cout << row[0] << "\n";
        std::cout << row[1] << "\n";
        std::cout << row[2] << "\n";
        std::cout << row[3] << "\n";
        std::cout << row[4] << "\n";
    }

    return 0;
}
