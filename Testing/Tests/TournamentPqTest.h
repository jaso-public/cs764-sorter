#ifndef CS764_SORTER_TOURNAMENTPQTEST_H
#define CS764_SORTER_TOURNAMENTPQTEST_H
#include "Testing/TestProviders/InOrderGenerator.h"
#include "Testing/TestProviders/ArrayProvider.h"
#include "TournamentPQ.h"
#include "Consumer.h"
#include "Witness.h"
#include <iostream>
#include <vector>
#include <list>
#include <cassert>
using namespace std;


class TournamentPqTest {
public:
    void doTest(int numProviders);
    void testVariousNumberOfProviders();
    TournamentPqTest();
};


#endif //CS764_SORTER_TOURNAMENTPQTEST_H
