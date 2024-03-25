cmake_minimum_required(VERSION 3.27)
project(cs764_sorter)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(cs764_sorter
        Assert.cpp
        Consumer.cpp
        Consumer.h
        OutlinedFiles/defs.cpp
        OutlinedFiles/defs.h
        OutlinedFiles/Filter.cpp
        OutlinedFiles/Filter.h
        OutlinedFiles/Iterator.cpp
        OutlinedFiles/Iterator.h
        Providers/Provider.cpp
        Providers/Provider.h
        Records/Record.cpp
        Records/Record.h
        Records/rng.cpp
        Records/rng.h
        OutlinedFiles/Scan.cpp
        OutlinedFiles/Scan.h
        Sort/Sort.cpp
        Sort/Sort.h
        Test.cpp
        TournamentPQ.cpp
        TournamentPQ.h
        Witness.cpp
        Witness.h
        IODevice.h
        IODevice.cpp
        Sim.cpp
        Providers/SingleProvider.h
        Providers/SingleProvider.cpp
        Providers/EmptyProvider.h
        Providers/EmptyProvider.cpp
        Providers/EmptyProvider.h
        Testing/TestProviders/Printer.cpp
        Testing/TestProviders/Printer.h
        Sort/Sorter.h
        Config/SorterConfig.cpp
        Config/SorterConfig.h
        Providers/StagedProvider.h
        Providers/StagedProvider.cpp
        Providers/StorageProvider.h
        Providers/StorageProvider.cpp
        Config/StagingConfig.h
        Testing/SortingHelpers/NoopSorter.h
        Testing/SortingHelpers/NoopSorter.cpp
        Sort/Sorter.cpp
        Run.h
        Run.cpp
        Providers/MemoryProvider.h
        Providers/MemoryProvider.cpp
)

add_executable(testing
    Testing/Tests/Practice.cpp
        Testing/Tests/Practice.h
)