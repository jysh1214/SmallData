#include "smalldata.h"

int main()
{
    sd::Parser p;
    sd::DataFrame df = p.readCVS("../../data/task2.csv").splitBy(',').withDefaultHeaders().createDF();

    return 0;
}
