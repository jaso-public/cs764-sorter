cmake_minimum_required(VERSION 3.23)
project(cs764_sorter)

set(CMAKE_CXX_STANDARD 17++)

include_directories(.)
include_directories(src)

add_executable(cs764_sorter
        OutlinedFiles/Assert.cpp
        test/helpers/Consumer.h
        OutlinedFiles/defs.cpp
        OutlinedFiles/defs.h
        OutlinedFiles/Filter.cpp
        OutlinedFiles/Filter.h
        OutlinedFiles/Iterator.cpp
        OutlinedFiles/Iterator.h
        src/Provider.h
        src/StagedProvider.h
        src/StagedProvider.cpp
        src/StorageProvider.h
        src/StorageProvider.cpp
        src/Record.cpp
        src/Record.h
        OutlinedFiles/Scan.cpp
        OutlinedFiles/Scan.h
        OutlinedFiles/Sort.cpp
        OutlinedFiles/Sort.h
        src/TournamentPQ.cpp
        src/TournamentPQ.h
        src/Witness.h
        src/IODevice.h
        src/IODevice.cpp
        Testing/TestProviders/Printer.cpp
        Testing/TestProviders/Printer.h
        src/Sorter.h
        Testing/SortingHelpers/NoopSorter.h
        src/Sorter.cpp
                src/main.cpp src/Provider.cpp)


add_executable(testRecord
        test/RecordTest.cpp
        src/Record.cpp
        src/Record.h)

add_custom_command(TARGET testRecord
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testRecord
        COMMENT "Running testRecord...")


add_executable(testArrayProvider
        test/helpers/Generators.h
        test/helpers/Generators.cpp
        test/ArrayProviderTest.cpp
        src/Record.cpp
        src/Record.h)

add_custom_command(TARGET testArrayProvider
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testArrayProvider
        COMMENT "Running testArrayProvider...")

add_executable(testWitness
        test/WitnessTest.cpp

        src/Record.h
        src/Record.cpp
        src/Provider.h
        src/Witness.h

        test/helpers/Consumer.h
        test/helpers/Generators.h
        test/helpers/Generators.cpp

        Testing/SortingHelpers/NoopSorter.h

        #        Testing/TestProviders/DropFirst.h
        #        Testing/TestProviders/DropFirst.cpp
        #        Testing/SortingHelpers/TreeSorter.h
        #        Testing/SortingHelpers/TreeSorter.cpp
        #        Testing/SortingHelpers/Key.h
        #        Testing/SortingHelpers/Key.cpp
        #        Testing/TestProviders/Printer.h
        #        Testing/TestProviders/Printer.cpp
        #        Providers/Dedooper.h
        #        Config/SorterConfig.cpp
        #        Config/SorterConfig.h
        )

add_custom_command(TARGET testWitness
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testWitness
        COMMENT "Running testWitness..."
)


add_executable(testSorterConfig
        Testing/Tests/Config/SorterConfigTest.cpp
        Testing/Tests/Config/SorterConfigTest.h
        src/IODevice.h
        src/IODevice.cpp
)

add_custom_command(TARGET testSorterConfig
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testSorterConfig
        COMMENT "Running testSorterConfig..."
)

add_executable(testPrinter
        Testing/TestProviders/Printer.cpp
        Testing/TestProviders/Printer.h
        test/helpers/Generators.h
        test/helpers/Generators.cpp
        Testing/Tests/Providers/PrinterTest.cpp
        src/Record.cpp
        src/Record.h
        src/IODevice.h
        src/IODevice.cpp
)

add_custom_command(TARGET testPrinter
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testPrinter
        COMMENT "Running testPrinter..."
)

add_executable(testIODevice
        src/IODevice.cpp
        src/IODevice.h
        Testing/Tests/IODevice/IoDeviceTest.cpp
        Testing/Tests/IODevice/IoDeviceTest.h
)

add_custom_command(TARGET testIODevice
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testIODevice
        COMMENT "Running testIODevice..."
)

add_executable(testSingleProvider
        Testing/Tests/Providers/SingleProviderTest.cpp
        Testing/Tests/Providers/SingleProviderTest.h
        src/IODevice.h
        src/IODevice.cpp
        src/Record.cpp
        src/Record.h
        )

add_custom_command(TARGET testSingleProvider
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testSingleProvider
        COMMENT "Running testSingleProvider..."
)

add_executable(testInOrderGenerator
        src/Record.cpp
        src/Record.h
        test/helpers/Generators.h
        test/helpers/Generators.cpp
        Testing/Tests/Providers/InOrderGeneratorTest.cpp
        Testing/Tests/Providers/InOrderGeneratorTest.h
        src/IODevice.h
        src/IODevice.cpp
)

add_custom_command(TARGET testInOrderGenerator
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testInOrderGenerator
        COMMENT "Running testInOrderGenerator..."
)

add_executable(testCrcRandomGenerator
        src/Record.cpp
        src/Record.h
        test/helpers/Generators.h
        test/helpers/Generators.cpp
        Testing/Tests/Helpers/CrcRandomGeneratorTest.cpp
        Testing/Tests/Helpers/CrcRandomGeneratorTest.h
        src/IODevice.h
        src/IODevice.cpp
)

add_custom_command(TARGET testCrcRandomGenerator
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testCrcRandomGenerator
        COMMENT "Running testCrcRandomGenerator..."
)

add_executable(testDedooper
        src/Record.cpp
        src/Record.h
        test/helpers/Generators.h
        test/helpers/Generators.cpp
        Testing/Tests/Providers/DedooperTest.cpp
        Testing/Tests/Providers/DedooperTest.h
        src/IODevice.h
        src/IODevice.cpp
)

add_custom_command(TARGET testDedooper
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testDedooper
        COMMENT "Running testDedooper..."
)

add_executable(testRandomGenerator
        src/Record.cpp
        src/Record.h
        test/helpers/Generators.h
        test/helpers/Generators.cpp
        Testing/Tests/Providers/RandomGeneratorTest.h
        Testing/Tests/Providers/RandomGeneratorTest.cpp
        src/IODevice.h
        src/IODevice.cpp
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
        src/Record.cpp
        src/Record.h
        test/helpers/Generators.h
        test/helpers/Generators.cpp
        Testing/TestProviders/DropFirst.cpp
        Testing/TestProviders/DropFirst.h
        Testing/Tests/Providers/DropFirstTest.cpp
        Testing/Tests/Providers/DropFirstTest.cpp
        src/Witness.h
        src/IODevice.h
        src/IODevice.cpp
)

add_custom_command(TARGET testDropFirst
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testDropFirst
        COMMENT "Running testDropFirst..."
)

add_executable(testTreeSorter
        src/Record.cpp
        src/Record.h
        Testing/SortingHelpers/TreeSorter.cpp
        Testing/SortingHelpers/TreeSorter.h
        Testing/Tests/Sorters/TreeSorterTest.cpp
        Testing/Tests/Sorters/TreeSorterTest.h
        test/helpers/Generators.h
        test/helpers/Generators.cpp
        src/Witness.h
        Testing/SortingHelpers/Key.h
        Testing/SortingHelpers/Key.cpp
        src/IODevice.h
        src/IODevice.cpp
)

add_custom_command(TARGET testTreeSorter
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testTreeSorter
        COMMENT "Running testTreeSorter..."
)

add_executable(testConsumer
        src/Record.cpp
        src/Record.h
        test/helpers/Generators.h
        test/helpers/Generators.cpp
        Testing/Tests/ConsumerTest.cpp
        Testing/Tests/ConsumerTest.h
        test/helpers/Consumer.h
        src/IODevice.h
        src/IODevice.cpp
)

add_custom_command(TARGET testConsumer
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testConsumer
        COMMENT "Running testConsumer..."
)

add_executable(testStagingConfig
        Testing/Tests/Config/StagingConfigTest.cpp
        Testing/Tests/Config/StagingConfigTest.h
        src/IODevice.cpp
        src/IODevice.h
)

add_custom_command(TARGET testStagingConfig
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testStagingConfig
        COMMENT "Running testStagingConfig..."
)

add_executable(testEmptyProvider
        Testing/Tests/Providers/EmptyProviderTest.cpp
        Testing/Tests/Providers/EmptyProviderTest.h
)

add_custom_command(TARGET testEmptyProvider
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testEmptyProvider
        COMMENT "Running testEmptyProvider..."
)

add_executable(testRecordProvider
        Testing/Tests/Providers/RecordProviderTest.cpp
        Testing/Tests/Providers/RecordProviderTest.h
        src/IODevice.cpp
        src/IODevice.h
        src/Record.cpp
        src/Record.h
        src/Provider.h
        src/Witness.h
        test/helpers/Generators.h
        test/helpers/Generators.cpp
        Testing/SortingHelpers/NoopSorter.h
        test/helpers/Consumer.h
        Testing/TestProviders/DropFirst.h
        Testing/TestProviders/DropFirst.cpp
        Testing/SortingHelpers/TreeSorter.h
        Testing/SortingHelpers/TreeSorter.cpp
        Testing/SortingHelpers/Key.h
        Testing/SortingHelpers/Key.cpp
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Printer.cpp
        src/Record.cpp
        src/Record.h
        src/IODevice.h
        src/IODevice.cpp
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

add_executable(testPQ
        src/Provider.h
        src/Witness.h
        test/helpers/Generators.h
        test/helpers/Generators.cpp
        test/TournamentPqTest.cpp
        Testing/Tests/TournamentPqTest.h
        test/helpers/Consumer.h
        src/TournamentPQ.cpp
        src/TournamentPQ.h
        src/Record.cpp
        src/Record.h
        src/IODevice.h
        src/IODevice.cpp
)

add_custom_command(TARGET testPQ
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testPQ
        COMMENT "Running testPQ..."
)

add_executable(testSorting
        src/Provider.h
        src/Record.cpp
        src/Record.h
        src/StorageProvider.h
        src/StorageProvider.cpp
        src/StagedProvider.cpp
        src/StagedProvider.h
        src/TournamentPQ.cpp
        src/TournamentPQ.h
        src/IODevice.h
        src/IODevice.cpp
        Testing/Tests/Sorters/SorterTest.cpp
        Testing/Tests/Sorters/SorterTest.h
        src/Sorter.cpp
        src/Sorter.h
        test/helpers/Consumer.h
        src/Witness.h
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Printer.cpp
)

add_custom_command(TARGET testSorting
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testSorting
        COMMENT "Running testSorting..."
)

add_executable(testLotsOfHddRuns
        src/Provider.h
        src/Record.cpp
        src/Record.h
        src/StorageProvider.h
        src/StorageProvider.cpp
        src/StagedProvider.cpp
        src/StagedProvider.h
        src/TournamentPQ.cpp
        src/TournamentPQ.h
        src/IODevice.h
        src/IODevice.cpp
        Testing/Tests/LotsOfHddRuns.cpp
        Testing/Tests/LotsOfHddRuns.h
        src/Sorter.cpp
        src/Sorter.h
        test/helpers/Consumer.h
        src/Witness.h
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Printer.cpp
        test/helpers/Generators.h
        test/helpers/Generators.cpp
        )

add_custom_command(TARGET testLotsOfHddRuns
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testLotsOfHddRuns
        COMMENT "Running testLotsOfHddRuns..."
)

add_executable(testSpillToHdd
        src/Provider.h
        src/Record.cpp
        src/Record.h
        src/StorageProvider.h
        src/StorageProvider.cpp
        src/StagedProvider.cpp
        src/StagedProvider.h
        src/TournamentPQ.cpp
        src/TournamentPQ.h
        src/IODevice.h
        src/IODevice.cpp
        Testing/Tests/Spilling/SpillToHdd.cpp
        Testing/Tests/Spilling/SpillToHdd.h
        src/Sorter.cpp
        src/Sorter.h
        test/helpers/Consumer.h
        src/Witness.h
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Printer.cpp
        test/helpers/Generators.h
        test/helpers/Generators.cpp
        )

add_custom_command(TARGET testSpillToHdd
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testSpillToHdd
        COMMENT "Running testSpillToHdd..."
)

add_executable(testSpillToOneBlockToSdd
        src/Provider.h
        src/Record.cpp
        src/Record.h
        src/StorageProvider.h
        src/StorageProvider.cpp
        src/StagedProvider.cpp
        src/StagedProvider.h
        src/TournamentPQ.cpp
        src/TournamentPQ.h
        src/IODevice.h
        src/IODevice.cpp
        Testing/Tests/Spilling/SpillOneBlockToSsd.cpp
        Testing/Tests/Spilling/SpillOneBlockToSsd.cpp
        src/Sorter.cpp
        src/Sorter.h
        test/helpers/Consumer.h
        src/Witness.h
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Printer.cpp
        test/helpers/Generators.h
        test/helpers/Generators.cpp
        )

add_custom_command(TARGET testSpillToOneBlockToSdd
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testSpillToOneBlockToSdd
        COMMENT "Running testSpillToOneBlockToSdd..."
)

add_executable(testStorageProvider
        src/Provider.h
        src/Record.cpp
        src/Record.h
        src/StorageProvider.h
        src/StorageProvider.cpp
        src/StagedProvider.cpp
        src/StagedProvider.h
        src/TournamentPQ.cpp
        src/TournamentPQ.h
        src/IODevice.h
        src/IODevice.cpp
        Testing/Tests/Providers/StorageProviderTest.h
        Testing/Tests/Providers/StorageProviderTest.cpp
        src/Sorter.cpp
        src/Sorter.h
        test/helpers/Consumer.h
        src/Witness.h
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Printer.cpp
        test/helpers/Generators.h
        test/helpers/Generators.cpp
        )


add_custom_command(TARGET testStorageProvider
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testStorageProvider
        COMMENT "Running testStorageProvider..."
)

add_executable(testStagedProvider
        src/Provider.h
        src/Record.cpp
        src/Record.h
        src/StagedProvider.cpp
        src/StagedProvider.h
        src/TournamentPQ.cpp
        src/TournamentPQ.h
        src/IODevice.h
        src/IODevice.cpp
        test/StagedProviderTest.cpp
        src/Sorter.cpp
        src/Sorter.h
        test/helpers/Consumer.h
        src/Witness.h
        Testing/TestProviders/Printer.h
        Testing/TestProviders/Printer.cpp
        test/helpers/Generators.h
        test/helpers/Generators.cpp
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
