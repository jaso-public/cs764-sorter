cmake_minimum_required(VERSION 3.23)
project(cs764_sorter)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(cs764_sorter
        OutlinedFiles/Assert.cpp
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
        OutlinedFiles/Scan.cpp
        OutlinedFiles/Scan.h
        Sort/Sort.cpp
        Sort/Sort.h
        TournamentPQ.cpp
        TournamentPQ.h
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
        Sort/Sorter.cpp
        Run.h
        Run.cpp
        Providers/MemoryProvider.h
        Providers/Dedooper.h
)

add_executable(testSorterConfig
        Config/SorterConfig.cpp
        Config/SorterConfig.h
        Testing/Tests/Config/SorterConfigTest.cpp
        Testing/Tests/Config/SorterConfigTest.h
        IODevice.h
        IODevice.cpp
)

add_custom_command(TARGET testSorterConfig
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testSorterConfig
        COMMENT "Running testSorterConfig..."
)

add_executable(testPrinter
        Testing/TestProviders/Printer.cpp
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Generators.h
        Testing/TestProviders/Generators.cpp
        Testing/TestProviders/ArrayProvider.cpp
        Testing/TestProviders/ArrayProvider.h
        Testing/Tests/Providers/PrinterTest.cpp
        Testing/Tests/Providers/PrinterTest.h
        Records/Record.cpp
        Records/Record.h
        Config/SorterConfig.cpp
        Config/SorterConfig.h
        IODevice.h
        IODevice.cpp
)

add_custom_command(TARGET testPrinter
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testPrinter
        COMMENT "Running testPrinter..."
)

add_executable(testIODevice
        IODevice.cpp
        IODevice.h
        Testing/Tests/IODevice/IoDeviceTest.cpp
        Testing/Tests/IODevice/IoDeviceTest.h
)

add_custom_command(TARGET testIODevice
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testIODevice
        COMMENT "Running testIODevice..."
)

add_executable(testArrayProvider
        Testing/TestProviders/Generators.h
        Testing/TestProviders/Generators.cpp
        Testing/TestProviders/ArrayProvider.h
        Testing/TestProviders/ArrayProvider.cpp
        Records/Record.cpp
        Records/Record.h
        Testing/Tests/Providers/ArrayProviderTest.cpp
        Testing/Tests/Providers/ArrayProviderTest.h
        Config/SorterConfig.cpp
        Config/SorterConfig.h
        IODevice.h
        IODevice.cpp
)

add_custom_command(TARGET testArrayProvider
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testArrayProvider
        COMMENT "Running testArrayProvider..."
)

add_executable(testSingleProvider
        Providers/SingleProvider.cpp
        Providers/SingleProvider.h
        Testing/Tests/Providers/SingleProviderTest.cpp
        Testing/Tests/Providers/SingleProviderTest.h
        Config/SorterConfig.cpp
        Config/SorterConfig.h
        IODevice.h
        IODevice.cpp
        Records/Record.cpp
        Records/Record.h
        )

add_custom_command(TARGET testSingleProvider
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testSingleProvider
        COMMENT "Running testSingleProvider..."
)

add_executable(testInOrderGenerator
        Records/Record.cpp
        Records/Record.h
        Testing/TestProviders/Generators.h
        Testing/TestProviders/Generators.cpp
        Testing/TestProviders/ArrayProvider.cpp
        Testing/TestProviders/ArrayProvider.h
        Testing/Tests/Providers/InOrderGeneratorTest.cpp
        Testing/Tests/Providers/InOrderGeneratorTest.h
        Config/SorterConfig.cpp
        Config/SorterConfig.h
        IODevice.h
        IODevice.cpp
)

add_custom_command(TARGET testInOrderGenerator
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testInOrderGenerator
        COMMENT "Running testInOrderGenerator..."
)

add_executable(testCrcRandomGenerator
        Records/Record.cpp
        Records/Record.h
        Testing/TestProviders/Generators.h
        Testing/TestProviders/Generators.cpp
        Testing/TestProviders/ArrayProvider.cpp
        Testing/TestProviders/ArrayProvider.h
        Testing/Tests/Helpers/CrcRandomGeneratorTest.cpp
        Testing/Tests/Helpers/CrcRandomGeneratorTest.h
        Config/SorterConfig.cpp
        Config/SorterConfig.h
        IODevice.h
        IODevice.cpp
)

add_custom_command(TARGET testCrcRandomGenerator
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testCrcRandomGenerator
        COMMENT "Running testCrcRandomGenerator..."
)

add_executable(testDedooper
        Records/Record.cpp
        Records/Record.h
        Testing/TestProviders/Generators.h
        Testing/TestProviders/Generators.cpp
        Testing/TestProviders/ArrayProvider.cpp
        Testing/TestProviders/ArrayProvider.h
        Testing/Tests/Providers/DedooperTest.cpp
        Testing/Tests/Providers/DedooperTest.h
        Providers/Dedooper.h
        Config/SorterConfig.cpp
        Config/SorterConfig.h
        IODevice.h
        IODevice.cpp
)

add_custom_command(TARGET testDedooper
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testDedooper
        COMMENT "Running testDedooper..."
)

add_executable(testRandomGenerator
        Records/Record.cpp
        Records/Record.h
        Testing/TestProviders/Generators.h
        Testing/TestProviders/Generators.cpp
        Testing/TestProviders/ArrayProvider.cpp
        Testing/TestProviders/ArrayProvider.h
        Testing/Tests/Providers/RandomGeneratorTest.h
        Testing/Tests/Providers/RandomGeneratorTest.cpp
        Config/SorterConfig.cpp
        Config/SorterConfig.h
        IODevice.h
        IODevice.cpp
)

add_custom_command(TARGET testRandomGenerator
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testRandomGenerator
        COMMENT "Running testRandomGenerator..."
)

add_executable(testKey
        Testing/SortingHelpers/Key.cpp
        Testing/SortingHelpers/Key.h
        Testing/Tests/Helpers/KeyTest.cpp
        Testing/Tests/Helpers/KeyTest.h
)

add_custom_command(TARGET testKey
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testKey
        COMMENT "Running testKey..."
)

add_executable(testDropFirst
        Records/Record.cpp
        Records/Record.h
        Testing/TestProviders/Generators.h
        Testing/TestProviders/Generators.cpp
        Testing/TestProviders/ArrayProvider.cpp
        Testing/TestProviders/ArrayProvider.h
        Testing/TestProviders/DropFirst.cpp
        Testing/TestProviders/DropFirst.h
        Testing/Tests/Providers/DropFirstTest.cpp
        Testing/Tests/Providers/DropFirstTest.cpp
        Witness.h
        Config/SorterConfig.cpp
        Config/SorterConfig.h
        IODevice.h
        IODevice.cpp
)

add_custom_command(TARGET testDropFirst
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testDropFirst
        COMMENT "Running testDropFirst..."
)

add_executable(testTreeSorter
        Records/Record.cpp
        Records/Record.h
        Testing/SortingHelpers/TreeSorter.cpp
        Testing/SortingHelpers/TreeSorter.h
        Testing/Tests/Sorters/TreeSorterTest.cpp
        Testing/Tests/Sorters/TreeSorterTest.h
        Testing/TestProviders/Generators.h
        Testing/TestProviders/Generators.cpp
        Testing/TestProviders/ArrayProvider.cpp
        Testing/TestProviders/ArrayProvider.h
        Witness.h
        Testing/SortingHelpers/Key.h
        Testing/SortingHelpers/Key.cpp
        Config/SorterConfig.cpp
        Config/SorterConfig.h
        IODevice.h
        IODevice.cpp
)

add_custom_command(TARGET testTreeSorter
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testTreeSorter
        COMMENT "Running testTreeSorter..."
)

add_executable(testConsumer
        Records/Record.cpp
        Records/Record.h
        Testing/TestProviders/Generators.h
        Testing/TestProviders/Generators.cpp
        Testing/TestProviders/ArrayProvider.cpp
        Testing/TestProviders/ArrayProvider.h
        Testing/Tests/ConsumerTest.cpp
        Testing/Tests/ConsumerTest.h
        Consumer.cpp
        Consumer.h
        Config/SorterConfig.cpp
        Config/SorterConfig.h
        IODevice.h
        IODevice.cpp
)

add_custom_command(TARGET testConsumer
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testConsumer
        COMMENT "Running testConsumer..."
)

add_executable(testStagingConfig
        Config/StagingConfig.h
        Config/StagingConfig.cpp
        Testing/Tests/Config/StagingConfigTest.cpp
        Testing/Tests/Config/StagingConfigTest.h
        IODevice.cpp
        IODevice.h
)

add_custom_command(TARGET testStagingConfig
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testStagingConfig
        COMMENT "Running testStagingConfig..."
)

add_executable(testEmptyProvider
        Providers/EmptyProvider.cpp
        Providers/EmptyProvider.h
        Testing/Tests/Providers/EmptyProviderTest.cpp
        Testing/Tests/Providers/EmptyProviderTest.h
)

add_custom_command(TARGET testEmptyProvider
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testEmptyProvider
        COMMENT "Running testEmptyProvider..."
)

add_executable(testRecordProvider
        Providers/RecordProvider.cpp
        Providers/RecordProvider.h
        Testing/Tests/Providers/RecordProviderTest.cpp
        Testing/Tests/Providers/RecordProviderTest.h
        Config/SorterConfig.cpp
        Config/SorterConfig.h
        IODevice.cpp
        IODevice.h
        Records/Record.cpp
        Records/Record.h
        Providers/Provider.h
        Witness.h
        Testing/TestProviders/Generators.h
        Testing/TestProviders/Generators.cpp
        Testing/TestProviders/ArrayProvider.cpp
        Testing/TestProviders/ArrayProvider.h
        Testing/SortingHelpers/NoopSorter.h
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
        Records/Record.cpp
        Records/Record.h
        Providers/Dedooper.h
        Config/SorterConfig.cpp
        Config/SorterConfig.h
        IODevice.h
        IODevice.cpp
)

add_custom_command(TARGET testRecordProvider
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testRecordProvider
        COMMENT "Running testRecordProvider..."
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
        Testing/TestProviders/Generators.h
        Testing/TestProviders/Generators.cpp
        Testing/TestProviders/ArrayProvider.cpp
        Testing/TestProviders/ArrayProvider.h
        Testing/SortingHelpers/NoopSorter.h
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
        Records/Record.cpp
        Records/Record.h
        Testing/Tests/WitnessTest.cpp
        Testing/Tests/WitnessTest.h
        Providers/Dedooper.h
        Config/SorterConfig.cpp
        Config/SorterConfig.h
        IODevice.h
        IODevice.cpp
)

add_custom_command(TARGET testWitness
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testWitness
        COMMENT "Running testWitness..."
)

add_executable(testPQ
        Providers/Provider.h
        Witness.h
        Testing/TestProviders/Generators.h
        Testing/TestProviders/Generators.cpp
        Testing/TestProviders/ArrayProvider.cpp
        Testing/TestProviders/ArrayProvider.h
        Testing/Tests/TournamentPqTest.cpp
        Testing/Tests/TournamentPqTest.h
        Consumer.h
        Consumer.cpp
        TournamentPQ.cpp
        TournamentPQ.h
        Testing/TestProviders/ArrayProvider.cpp
        Testing/TestProviders/ArrayProvider.h
        Records/Record.cpp
        Records/Record.h
        Config/SorterConfig.cpp
        Config/SorterConfig.h
        IODevice.h
        IODevice.cpp
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
        Witness.h
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
        Witness.h
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Printer.cpp
        Testing/TestProviders/Generators.h
        Testing/TestProviders/Generators.cpp
        Testing/TestProviders/ArrayProvider.cpp
        Testing/TestProviders/ArrayProvider.h
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
        Witness.h
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Printer.cpp
        Testing/TestProviders/Generators.h
        Testing/TestProviders/Generators.cpp
        Testing/TestProviders/ArrayProvider.cpp
        Testing/TestProviders/ArrayProvider.h
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
        Witness.h
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Printer.cpp
        Testing/TestProviders/Generators.h
        Testing/TestProviders/Generators.cpp
        Testing/TestProviders/ArrayProvider.cpp
        Testing/TestProviders/ArrayProvider.h
)

add_custom_command(TARGET testSpillToOneBlockToSdd
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testSpillToOneBlockToSdd
        COMMENT "Running testSpillToOneBlockToSdd..."
)

add_executable(testRecord
        Testing/Tests/Record/RecordTest.cpp
        Testing/Tests/Record/RecordTest.h
        Records/Record.cpp
        Records/Record.h
        Config/SorterConfig.cpp
        Config/SorterConfig.h
        IODevice.h
        IODevice.cpp
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
        Witness.h
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Printer.cpp
        Testing/TestProviders/Generators.h
        Testing/TestProviders/Generators.cpp
        Testing/TestProviders/ArrayProvider.cpp
        Testing/TestProviders/ArrayProvider.h
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
        Witness.h
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Printer.cpp
        Testing/TestProviders/Generators.h
        Testing/TestProviders/Generators.cpp
        Testing/TestProviders/ArrayProvider.cpp
        Testing/TestProviders/ArrayProvider.h
)

add_custom_command(TARGET testStagedProvider
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testStagedProvider
        COMMENT "Running testStagedProvider..."
)

add_custom_target(runNonFaultTests
        COMMAND $<TARGET_FILE:testDuplicateRemoval>
        COMMAND $<TARGET_FILE:testInOrderGenerator>
        COMMAND $<TARGET_FILE:testConsumer>
        COMMAND $<TARGET_FILE:testDropFirst>
        COMMAND $<TARGET_FILE:testRandomGenerator>
        COMMAND $<TARGET_FILE:testDedooper>
        COMMAND $<TARGET_FILE:testIODevice>
        COMMAND $<TARGET_FILE:testSorterConfig>
        COMMAND $<TARGET_FILE:testEmptyProvider>
        COMMAND $<TARGET_FILE:testSingleProvider>
        COMMAND $<TARGET_FILE:testKey>
        COMMAND $<TARGET_FILE:testStagingConfig>
        COMMAND $<TARGET_FILE:testPrinter>
        COMMAND $<TARGET_FILE:testCrcRandomGenerator>
        COMMAND $<TARGET_FILE:testRecordProvider>
        COMMAND $<TARGET_FILE:testWitness>
        COMMAND $<TARGET_FILE:testArrayProvider>
        COMMAND $<TARGET_FILE:testTreeSorter>
        COMMAND $<TARGET_FILE:testPQ>
)

add_custom_command(TARGET runNonFaultTests
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/runNonFaultTests
        COMMENT "Running runNonFaultTests..."
)

add_custom_target(runFaultTests
        COMMAND $<TARGET_FILE:testSorting>
        COMMAND $<TARGET_FILE:testSpillToOneBlockToSdd>
        COMMAND $<TARGET_FILE:testSpillToHdd>
        COMMAND $<TARGET_FILE:testLotsOfHddRuns>
)

add_custom_command(TARGET runFaultTests
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/runFaultTests
        COMMENT "Running runFaultTests..."
)

add_custom_command(TARGET testStagedProvider
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testStagedProvider
        COMMENT "Running testStagedProvider..."
)

add_custom_target(runErrorTests
        COMMAND $<TARGET_FILE:testRecord>
        COMMAND $<TARGET_FILE:testStagedProvider>
        COMMAND $<TARGET_FILE:testStorageProvider>
)

add_custom_command(TARGET runErrorTests
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/runErrorTests
        COMMENT "Running runErrorTests..."
)

add_custom_target(runAllTests
        COMMAND $<TARGET_FILE:testDuplicateRemoval>
        COMMAND $<TARGET_FILE:testInOrderGenerator>
        COMMAND $<TARGET_FILE:testConsumer>
        COMMAND $<TARGET_FILE:testDropFirst>
        COMMAND $<TARGET_FILE:testRandomGenerator>
        COMMAND $<TARGET_FILE:testDedooper>
        COMMAND $<TARGET_FILE:testIODevice>
        COMMAND $<TARGET_FILE:testSorterConfig>
        COMMAND $<TARGET_FILE:testEmptyProvider>
        COMMAND $<TARGET_FILE:testSingleProvider>
        COMMAND $<TARGET_FILE:testKey>
        COMMAND $<TARGET_FILE:testStagingConfig>
        COMMAND $<TARGET_FILE:testPrinter>
        COMMAND $<TARGET_FILE:testCrcRandomGenerator >
        COMMAND $<TARGET_FILE:testRecordProvider>
        COMMAND $<TARGET_FILE:testWitness>
        COMMAND $<TARGET_FILE:testArrayProvider>
        COMMAND $<TARGET_FILE:testTreeSorter>
        COMMAND $<TARGET_FILE:testPQ>
        COMMAND $<TARGET_FILE:testSorting>
        COMMAND $<TARGET_FILE:testSpillToOneBlockToSdd>
        COMMAND $<TARGET_FILE:testSpillToHdd>
        COMMAND $<TARGET_FILE:testLotsOfHddRuns>
        COMMAND $<TARGET_FILE:testRecord>
        COMMAND $<TARGET_FILE:testStagedProvider>
        COMMAND $<TARGET_FILE:testStorageProvider>
)

add_custom_command(TARGET runAllTests
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/runAllTests
        COMMENT "Running runAllTests..."
)
