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
        Providers/Provider.cpp
        Providers/Provider.h
        Records/Record.cpp
        Records/Record.h
        Records/rng.cpp
        Records/rng.h
        Scan.cpp
        Scan.h
        Sort.cpp
        Sort.h
        Test.cpp
        NotDone/TournamentPQ.cpp
        NotDone/TournamentPQ.h
        Witness.cpp
        Witness.h
        Providers/ArrayProvider.h
        Providers/ArrayProvider.cpp
        Providers/DropFirst.h
        Providers/DropFirst.cpp
        Providers/InOrderGenerator.h
        Providers/InOrderGenerator.cpp
        IODevice.h
        IODevice.cpp
        Sim.h
        Sim.cpp
        Providers/SingleProvider.h
        Providers/SingleProvider.cpp
        Providers/SingleProvider.cpp
        ../../../../EmptyProvider.h
        Providers/EmptyProvider.h
        Providers/EmptyProvider.cpp
        Providers/EmptyProvider.cpp
        Providers/EmptyProvider.h)
