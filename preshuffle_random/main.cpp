#include <iostream>
#include <stdio.h>
#include "def.h"
using namespace std;

int main()
{
    simulator* sim = new simulator();

    freopen("result.txt", "w+", stdout);
    sim->print();
    sim->run();

    return 0;
}
