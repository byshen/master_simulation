#include <iostream>
#include "def.h"
using namespace std;

int main()
{
    simulator* sim = new simulator();

    sim->print();
    sim->run();

    return 0;
}
