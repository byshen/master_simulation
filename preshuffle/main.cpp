#include <iostream>
#include <stdio.h>
#include "def.h"
using namespace std;

int main()
{
    freopen("out.txt","w+",stdout);
    simulator* sim = new simulator();

    sim->print();
    sim->run();

    return 0;
}
