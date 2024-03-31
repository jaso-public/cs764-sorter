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
        Providers/Provider.h
        Providers/SingleProvider.h
        Providers/SingleProvider.cpp
        Providers/EmptyProvider.h
        Providers/EmptyProvider.cpp
        Providers/StagedProvider.h
        Providers/StagedProvider.cpp
        Providers/StorageProvider.h
        Providers/StorageProvider.cpp
        Records/Record.cpp
        Records/Record.h
        Records/rng.cpp
        Records/rng.h
        OutlinedFiles/Scan.cpp
        OutlinedFiles/Scan.h
        Sort/Sort.cpp
        Sort/Sort.h
        TournamentPQ.cpp
        TournamentPQ.h
        Witness.cpp
        Witness.h
        IODevice.h
        IODevice.cpp
        Sim.cpp
        Testing/TestProviders/Printer.cpp
        Testing/TestProviders/Printer.h
        Sort/Sorter.h
        Config/SorterConfig.cpp
        Config/SorterConfig.h
        Config/StagingConfig.h
        Config/StagingConfig.cpp
        Testing/SortingHelpers/NoopSorter.h
        Testing/SortingHelpers/NoopSorter.cpp
        Sort/Sorter.cpp
        Run.h
        Run.cpp
        Providers/MemoryProvider.h
        Providers/MemoryProvider.cpp
        Records/CreateRecords.h
        Providers/Dedooper.cpp
        Providers/Dedooper.h
)

add_executable(createRecords
        Records/CreateRecords.h
        Records/CreateRecords.cpp
        Records/Record.cpp
        Records/Record.h
        Records/rng.cpp
        Records/rng.h
        Providers/Dedooper.h
)

add_custom_command(TARGET createRecords
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/createRecords
        COMMENT "Running createRecords..."
)

add_executable(testInOrderGenerator
        Records/Record.cpp
        Records/Record.h
        Records/rng.cpp
        Records/rng.h
        Testing/TestProviders/InOrderGenerator.cpp
        Testing/TestProviders/InOrderGenerator.h
        Testing/Tests/Providers/InOrderGeneratorTest.cpp
        Testing/Tests/Providers/InOrderGeneratorTest.h
)

add_custom_command(TARGET testInOrderGenerator
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testInOrderGenerator
        COMMENT "Running testInOrderGenerator..."
)

add_executable(testDedooper
        Records/Record.cpp
        Records/Record.h
        Records/rng.cpp
        Records/rng.h
        Testing/TestProviders/InOrderGenerator.cpp
        Testing/TestProviders/InOrderGenerator.h
        Testing/Tests/DedooperTest.cpp
        Testing/Tests/DedooperTest.h
        Providers/Dedooper.cpp
        Providers/Dedooper.h
)

add_custom_command(TARGET testDedooper
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testDedooper
        COMMENT "Running testDedooper..."
)

add_executable(testRandomGenerator
        Records/Record.cpp
        Records/Record.h
        Records/rng.cpp
        Records/rng.h
        Testing/TestProviders/RandomGenerator.cpp
        Testing/TestProviders/RandomGenerator.h
        Testing/Tests/Providers/RandomGeneratorTest.cpp
        Testing/Tests/Providers/RandomGeneratorTest.h
)

add_custom_command(TARGET testRandomGenerator
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testRandomGenerator
        COMMENT "Running testRandomGenerator..."
)

add_executable(testKey
        Testing/SortingHelpers/Key.cpp
        Testing/SortingHelpers/Key.h
        Testing/Tests/Sorters/KeyTest.cpp
        Testing/Tests/Sorters/KeyTest.h
)

add_custom_command(TARGET testKey
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testKey
        COMMENT "Running testKey..."
)

add_executable(testDropFirst
        Records/Record.cpp
        Records/Record.h
        Records/rng.cpp
        Records/rng.h
        Testing/TestProviders/InOrderGenerator.cpp
        Testing/TestProviders/InOrderGenerator.h
        Testing/TestProviders/DropFirst.cpp
        Testing/TestProviders/DropFirst.h
        Testing/Tests/Providers/DropFirstTest.cpp
        Testing/Tests/Providers/DropFirstTest.cpp
        Witness.h
        Witness.cpp
)

add_custom_command(TARGET testDropFirst
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testDropFirst
        COMMENT "Running testDropFirst..."
)

add_executable(testTreeSorter
        Records/Record.cpp
        Records/Record.h
        Records/rng.cpp
        Records/rng.h
        Testing/TestProviders/RandomGenerator.h
        Testing/TestProviders/RandomGenerator.cpp
        Testing/SortingHelpers/TreeSorter.cpp
        Testing/SortingHelpers/TreeSorter.h
        Testing/Tests/Sorters/TreeSorterTest.cpp
        Testing/Tests/Sorters/TreeSorterTest.h
        Witness.h
        Witness.cpp
        Testing/SortingHelpers/Key.h
        Testing/SortingHelpers/Key.cpp
)

add_custom_command(TARGET testTreeSorter
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testTreeSorter
        COMMENT "Running testTreeSorter..."
)

add_executable(testConsumer
        Records/Record.cpp
        Records/Record.h
        Records/rng.cpp
        Records/rng.h
        Testing/TestProviders/InOrderGenerator.cpp
        Testing/TestProviders/InOrderGenerator.h
        Testing/Tests/ConsumerTest.cpp
        Testing/Tests/ConsumerTest.h
        Consumer.cpp
        Consumer
)

add_custom_command(TARGET testConsumer
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testConsumer
        COMMENT "Running testConsumer..."
)

add_executable(testDuplicateRemoval
        Testing/Tests/DuplicateRemoval/TestDuplicateRemoval.cpp
        Testing/Tests/DuplicateRemoval/TestDuplicateRemoval.h
        DuplicateRemoval/RemoveDuplicates.cpp
        DuplicateRemoval/RemoveDuplicates.h
)

add_custom_command(TARGET testDuplicateRemoval
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testDuplicateRemoval
        COMMENT "Running testDuplicateRemoval..."
)

add_executable(testWitness
        Providers/Provider.h
        Witness.h
        Witness.cpp
        Testing/TestProviders/InOrderGenerator.h
        Testing/TestProviders/InOrderGenerator.cpp
        Testing/SortingHelpers/NoopSorter.h
        Testing/SortingHelpers/NoopSorter.cpp
        Consumer.h
        Consumer.cpp
        Testing/TestProviders/DropFirst.h
        Testing/TestProviders/DropFirst.cpp
        Testing/SortingHelpers/TreeSorter.h
        Testing/SortingHelpers/TreeSorter.cpp
        Testing/SortingHelpers/Key.h
        Testing/SortingHelpers/Key.cpp
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Printer.cpp
        Testing/TestProviders/RandomGenerator.h
        Testing/TestProviders/RandomGenerator.cpp
        Records/Record.cpp
        Records/Record.h
        Records/rng.cpp
        Records/rng.h
        Testing/Tests/WitnessTest.cpp
        Testing/Tests/WitnessTest.h
        Providers/Dedooper.cpp
        Providers/Dedooper.h
)

add_custom_command(TARGET testWitness
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testWitness
        COMMENT "Running testWitness..."
)

add_executable(testPQ
        Providers/Provider.h
        Witness.h
        Witness.cpp
        Testing/TestProviders/InOrderGenerator.h
        Testing/TestProviders/InOrderGenerator.cpp
        Testing/Tests/TournamentPqTest.cpp
        Testing/Tests/TournamentPqTest.h
        Testing/TestProviders/InOrderGenerator.cpp
        Consumer.h
        Consumer.cpp
        TournamentPQ.cpp
        TournamentPQ.h
        Testing/TestProviders/ArrayProvider.cpp
        Testing/TestProviders/ArrayProvider.h
        Records/Record.cpp
        Records/Record.h
        Records/rng.cpp
        Records/rng.h
)

add_custom_command(TARGET testPQ
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testPQ
        COMMENT "Running testPQ..."
)

add_executable(testSorting
        Providers/Provider.h
        Records/Record.cpp
        Records/Record.h
        Records/rng.cpp
        Records/rng.h
        Config/SorterConfig.h
        Config/SorterConfig.cpp
        Config/StagingConfig.h
        Config/StagingConfig.cpp
        Run.cpp
        Run.h
        Providers/SingleProvider.cpp
        Providers/SingleProvider.h
        Providers/EmptyProvider.cpp
        Providers/EmptyProvider.h
        Providers/MemoryProvider.cpp
        Providers/MemoryProvider.h
        Providers/StorageProvider.h
        Providers/StorageProvider.cpp
        Providers/StagedProvider.cpp
        Providers/StagedProvider.h
        TournamentPQ.cpp
        TournamentPQ.h
        IODevice.h
        IODevice.cpp
        Testing/Tests/Sorters/SorterTest.cpp
        Testing/Tests/Sorters/SorterTest.h
        Sort/Sorter.cpp
        Sort/Sorter.h
        Consumer.cpp
        Consumer.h
        Witness.cpp
        Witness.h
        Testing/TestProviders/RandomGenerator.h
        Testing/TestProviders/RandomGenerator.cpp
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Printer.cpp
)

add_custom_command(TARGET testSorting
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testSorting
        COMMENT "Running testSorting..."
)

add_executable(testLotsOfHddRuns
        Providers/Provider.h
        Records/Record.cpp
        Records/Record.h
        Records/rng.cpp
        Records/rng.h
        Config/SorterConfig.h
        Config/SorterConfig.cpp
        Config/StagingConfig.h
        Config/StagingConfig.cpp
        Run.cpp
        Run.h
        Providers/SingleProvider.cpp
        Providers/SingleProvider.h
        Providers/EmptyProvider.cpp
        Providers/EmptyProvider.h
        Providers/MemoryProvider.cpp
        Providers/MemoryProvider.h
        Providers/StorageProvider.h
        Providers/StorageProvider.cpp
        Providers/StagedProvider.cpp
        Providers/StagedProvider.h
        TournamentPQ.cpp
        TournamentPQ.h
        IODevice.h
        IODevice.cpp
        Testing/Tests/LotsOfHddRuns.cpp
        Testing/Tests/LotsOfHddRuns.h
        Sort/Sorter.cpp
        Sort/Sorter.h
        Consumer.cpp
        Consumer.h
        Witness.cpp
        Witness.h
        Testing/TestProviders/RandomGenerator.h
        Testing/TestProviders/RandomGenerator.cpp
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Printer.cpp
        Testing/SortingHelpers/CrcRandomGenerator.cpp
        Testing/SortingHelpers/CrcRandomGenerator.h
)

add_custom_command(TARGET testLotsOfHddRuns
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testLotsOfHddRuns
        COMMENT "Running testLotsOfHddRuns..."
)

add_executable(testSpillToHdd
        Providers/Provider.h
        Records/Record.cpp
        Records/Record.h
        Records/rng.cpp
        Records/rng.h
        Config/SorterConfig.h
        Config/SorterConfig.cpp
        Config/StagingConfig.h
        Config/StagingConfig.cpp
        Run.cpp
        Run.h
        Providers/SingleProvider.cpp
        Providers/SingleProvider.h
        Providers/EmptyProvider.cpp
        Providers/EmptyProvider.h
        Providers/MemoryProvider.cpp
        Providers/MemoryProvider.h
        Providers/StorageProvider.h
        Providers/StorageProvider.cpp
        Providers/StagedProvider.cpp
        Providers/StagedProvider.h
        TournamentPQ.cpp
        TournamentPQ.h
        IODevice.h
        IODevice.cpp
        Testing/Tests/Spilling/SpillToHdd.cpp
        Testing/Tests/Spilling/SpillToHdd.h
        Sort/Sorter.cpp
        Sort/Sorter.h
        Consumer.cpp
        Consumer.h
        Witness.cpp
        Witness.h
        Testing/TestProviders/RandomGenerator.h
        Testing/TestProviders/RandomGenerator.cpp
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Printer.cpp
        Testing/SortingHelpers/CrcRandomGenerator.cpp
        Testing/SortingHelpers/CrcRandomGenerator.h
)

add_custom_command(TARGET testSpillToHdd
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testSpillToHdd
        COMMENT "Running testSpillToHdd..."
)

add_executable(testSpillToOneBlockToSdd
        Providers/Provider.h
        Records/Record.cpp
        Records/Record.h
        Records/rng.cpp
        Records/rng.h
        Config/SorterConfig.h
        Config/SorterConfig.cpp
        Config/StagingConfig.h
        Config/StagingConfig.cpp
        Run.cpp
        Run.h
        Providers/SingleProvider.cpp
        Providers/SingleProvider.h
        Providers/EmptyProvider.cpp
        Providers/EmptyProvider.h
        Providers/MemoryProvider.cpp
        Providers/MemoryProvider.h
        Providers/StorageProvider.h
        Providers/StorageProvider.cpp
        Providers/StagedProvider.cpp
        Providers/StagedProvider.h
        TournamentPQ.cpp
        TournamentPQ.h
        IODevice.h
        IODevice.cpp
        Testing/Tests/Spilling/SpillOneBlockToSsd.cpp
        Testing/Tests/Spilling/SpillOneBlockToSsd.cpp
        Sort/Sorter.cpp
        Sort/Sorter.h
        Consumer.cpp
        Consumer.h
        Witness.cpp
        Witness.h
        Testing/TestProviders/RandomGenerator.h
        Testing/TestProviders/RandomGenerator.cpp
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Printer.cpp
        Testing/SortingHelpers/CrcRandomGenerator.cpp
        Testing/SortingHelpers/CrcRandomGenerator.h
)

add_custom_command(TARGET testSpillToOneBlockToSdd
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testSpillToOneBlockToSdd
        COMMENT "Running testSpillToOneBlockToSdd..."
)

add_executable(testRecord
    Testing/Tests/Record/RecordTest.cpp
        Testing/Tests/Record/RecordTest.h
)

add_custom_command(TARGET testRecord
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testRecord
        COMMENT "Running testRecord..."
)

add_executable(testStorageProvider
        Providers/Provider.h
        Records/Record.cpp
        Records/Record.h
        Records/rng.cpp
        Records/rng.h
        Config/SorterConfig.h
        Config/SorterConfig.cpp
        Config/StagingConfig.h
        Config/StagingConfig.cpp
        Run.cpp
        Run.h
        Providers/SingleProvider.cpp
        Providers/SingleProvider.h
        Providers/EmptyProvider.cpp
        Providers/EmptyProvider.h
        Providers/MemoryProvider.cpp
        Providers/MemoryProvider.h
        Providers/StorageProvider.h
        Providers/StorageProvider.cpp
        Providers/StagedProvider.cpp
        Providers/StagedProvider.h
        TournamentPQ.cpp
        TournamentPQ.h
        IODevice.h
        IODevice.cpp
        Testing/Tests/Providers/StorageProviderTest.h
        Testing/Tests/Providers/StorageProviderTest.cpp
        Sort/Sorter.cpp
        Sort/Sorter.h
        Consumer.cpp
        Consumer.h
        Witness.cpp
        Witness.h
        Testing/TestProviders/RandomGenerator.h
        Testing/TestProviders/RandomGenerator.cpp
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Printer.cpp
        Testing/SortingHelpers/CrcRandomGenerator.cpp
        Testing/SortingHelpers/CrcRandomGenerator.h
)


add_custom_command(TARGET testStorageProvider
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testStorageProvider
        COMMENT "Running testStorageProvider..."
)

add_executable(testStagedProvider
        Providers/Provider.h
        Records/Record.cpp
        Records/Record.h
        Records/rng.cpp
        Records/rng.h
        Config/SorterConfig.h
        Config/SorterConfig.cpp
        Config/StagingConfig.h
        Config/StagingConfig.cpp
        Run.cpp
        Run.h
        Providers/SingleProvider.cpp
        Providers/SingleProvider.h
        Providers/EmptyProvider.cpp
        Providers/EmptyProvider.h
        Providers/MemoryProvider.cpp
        Providers/MemoryProvider.h
        Providers/StorageProvider.h
        Providers/StorageProvider.cpp
        Providers/StagedProvider.cpp
        Providers/StagedProvider.h
        TournamentPQ.cpp
        TournamentPQ.h
        IODevice.h
        IODevice.cpp
        Testing/Tests/Providers/StagedProviderTest.cpp
        Testing/Tests/Providers/StagedProviderTest.h
        Sort/Sorter.cpp
        Sort/Sorter.h
        Consumer.cpp
        Consumer.h
        Witness.cpp
        Witness.h
        Testing/TestProviders/RandomGenerator.h
        Testing/TestProviders/RandomGenerator.cpp
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Printer.cpp
        Testing/SortingHelpers/CrcRandomGenerator.cpp
        Testing/SortingHelpers/CrcRandomGenerator.h
)

add_custom_command(TARGET testStagedProvider
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testStagedProvider
        COMMENT "Running testStagedProvider..."
)

add_custom_target(runAllTests
        COMMAND $<TARGET_FILE:testDuplicateRemoval>
        COMMAND $<TARGET_FILE:testWitness>
        COMMAND $<TARGET_FILE:testPQ>
        COMMAND $<TARGET_FILE:testSorting>
        COMMAND $<TARGET_FILE:testLotsOfHddRuns>
        COMMAND $<TARGET_FILE:testSpillToHdd>
        COMMAND $<TARGET_FILE:testRecord>
        COMMAND $<TARGET_FILE:testStorageProvider>
        COMMAND $<TARGET_FILE:testStagedProvider>
        COMMAND $<TARGET_FILE:testInOrderGenerator>
        COMMAND $<TARGET_FILE:testConsumer>
        COMMAND $<TARGET_FILE:testDropFirst>
        COMMAND $<TARGET_FILE:testRandomGenerator>
        COMMAND $<TARGET_FILE:testTreeSorter>
        COMMAND $<TARGET_FILE:testDedooper>
)

add_custom_command(TARGET runAllTests
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/runAllTests
        COMMENT "Running runAllTests..."
)