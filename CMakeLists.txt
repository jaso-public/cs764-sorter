cmake_minimum_required(VERSION 3.27)
project(cs764_sorter)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cs764_sorter
        Assert.cpp
        Consumer.cpp
        Consumer.h
        defs.cpp
        defs.h
        Filter.cpp
        Filter.h
        Iterator.cpp
        Iterator.h
        Provider.cpp
        Provider.h
        Record.cpp
        Record.h
        rng.cpp
        rng.h
        Scan.cpp
        Scan.h
        Sort.cpp
        Sort.h
        Test.cpp
        TournamentPQ.cpp
        TournamentPQ.h
        Witness.cpp
        Witness.h
        ArrayProvider.h
        ArrayProvider.cpp
        DropFirst.h
        DropFirst.cpp)
