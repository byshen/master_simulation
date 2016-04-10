#include <iostream>
#include <stdio.h>
#include "def.h"

using namespace std;
#include <time.h>



int main()
{
    freopen("result.txt","w+",stdout);
    simulator* sim = new simulator();

    sim->print();




    clock_t stime , etime ;
    stime = clock();

    sim->run();

    etime = clock(); /* get end time */
    double duration = (double)(etime - stime) / CLOCKS_PER_SEC;
    printf( "%f seconds\n", duration );

    return 0;
}
