cmake_minimum_required(VERSION 3.22)

project(cs764_sorter)

set(CMAKE_CXX_STANDARD 17++)

include_directories(.)
include_directories(src)

add_executable(sort
        src/Record.h
        src/Record.cpp
        src/Provider.h
        src/Provider.cpp
        src/Consumer.h
        src/Consumer.cpp
        src/IODevice.h
        src/IODevice.cpp
        src/Generator.h
        src/Generator.cpp
        src/StagedProvider.h
        src/StagedProvider.cpp
        src/StorageProvider.h
        src/StorageProvider.cpp
        src/TournamentPQ.cpp
        src/TournamentPQ.h
        src/Witness.h
        src/Sorter.h
        src/Sorter.cpp
        src/Convert.h
        src/tools/sort.cpp)

add_executable(generate
        src/Record.h
        src/Record.cpp
        src/Provider.h
        src/Provider.cpp
        src/Consumer.h
        src/Consumer.cpp
        src/IODevice.h
        src/IODevice.cpp
        src/Generator.h
        src/Generator.cpp
        src/tools/generate.cpp
        )

add_executable(copy
        src/Record.h
        src/Record.cpp
        src/Provider.h
        src/Provider.cpp
        src/Consumer.h
        src/Consumer.cpp
        src/IODevice.h
        src/IODevice.cpp
        src/Witness.h
        src/Generator.cpp
        src/tools/copy.cpp
        )

add_executable(verify
        src/Record.h
        src/Record.cpp
        src/Provider.h
        src/Provider.cpp
        src/Consumer.h
        src/Consumer.cpp
        src/IODevice.h
        src/IODevice.cpp
        src/Witness.h
        src/Generator.cpp
        src/tools/verify.cpp
        )

add_executable(testRecord
        test/RecordTest.cpp
        src/Record.cpp
        src/Record.h
        src/Generator.h
        src/Generator.cpp

        )

add_custom_command(TARGET testRecord
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testRecord
        COMMENT "Running testRecord...")


add_executable(testProvider
        test/ProviderTest.cpp
        src/Record.h
        src/Record.cpp
        src/Provider.h
        src/Provider.cpp
        src/Generator.h
        src/Generator.cpp
        src/IODevice.h
        src/IODevice.cpp)

add_custom_command(TARGET testProvider
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testProvider
        COMMENT "Running testProvider..."
)

add_executable(testWitness
        test/WitnessTest.cpp
        src/Record.h
        src/Record.cpp
        src/Provider.h
        src/Provider.cpp
        src/Witness.h
        src/Consumer.h
        src/Consumer.cpp
        src/IODevice.h
        src/IODevice.cpp
        src/Generator.h
        src/Generator.cpp
        test/helpers/TreeSorter.h
        test/helpers/TreeSorter.cpp
        test/helpers/Printer.h
        test/helpers/Printer.cpp
)

add_custom_command(TARGET testWitness
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testWitness
        COMMENT "Running testWitness..."
)

add_executable(testIODevice
        src/IODevice.cpp
        src/IODevice.h
        test/IoDeviceTest.cpp
        )

add_custom_command(TARGET testIODevice
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testIODevice
        COMMENT "Running testIODevice..."
)

add_executable(testConsumer
        src/Record.cpp
        src/Record.h
        src/Generator.h
        src/Generator.cpp
        src/Provider.h
        src/Provider.cpp
        Testing/ConsumerTest.cpp
        src/Consumer.h
        src/IODevice.h
        src/IODevice.cpp
)

add_custom_command(TARGET testConsumer
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testConsumer
        COMMENT "Running testConsumer..."
)


add_executable(testDeviceProvider
        Testing/DeviceProviderTest.cpp
        src/IODevice.cpp
        src/IODevice.h
        src/Record.cpp
        src/Record.h
        src/Provider.h
        src/Provider.cpp
        src/Witness.h
        src/Generator.h
        src/Generator.cpp
        src/Consumer.h
        test/helpers/TreeSorter.h
        test/helpers/TreeSorter.cpp
        test/helpers/Printer.h
        test/helpers/Printer.cpp
        src/Record.cpp
        src/Record.h
        src/IODevice.h
        src/IODevice.cpp
)

add_custom_command(TARGET testDeviceProvider
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testDeviceProvider
        COMMENT "Running testDeviceProvider..."
)

add_executable(testPQ
        src/Provider.h
        src/Witness.h
        src/Generator.h
        src/Generator.cpp
        test/TournamentPqTest.cpp
        src/Consumer.h
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

add_executable(testSorter
        src/Record.h
        src/Record.cpp
        src/Provider.h
        src/Provider.cpp
        src/Consumer.h
        src/Consumer.cpp
        src/IODevice.h
        src/IODevice.cpp
        src/Generator.h
        src/Generator.cpp
        src/StorageProvider.h
        src/StorageProvider.cpp
        src/StagedProvider.cpp
        src/StagedProvider.h
        src/TournamentPQ.h
        src/TournamentPQ.cpp
        src/Sorter.h
        src/Sorter.cpp
        src/Witness.h
        test/helpers/Printer.h
        test/helpers/Printer.cpp
        test/SorterTest.cpp
        )

add_custom_command(TARGET testSorter
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testSorter
        COMMENT "Running testSorter..."
)

add_executable(testStorageProvider
        src/Provider.h
        src/Provider.cpp
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
        Testing/StorageProviderTest.cpp
        src/Sorter.cpp
        src/Sorter.h
        src/Consumer.h
        src/Witness.h
        test/helpers/Printer.h
        test/helpers/Printer.cpp
        src/Generator.h
        src/Generator.cpp
        )


add_custom_command(TARGET testStorageProvider
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testStorageProvider
        COMMENT "Running testStorageProvider..."
)

add_executable(testStagedProvider
        src/Provider.h
        src/Provider.cpp
        src/Record.cpp
        src/Record.h
        src/StagedProvider.cpp
        src/StagedProvider.h
        src/StorageProvider.cpp
        src/StorageProvider.h
        src/TournamentPQ.cpp
        src/TournamentPQ.h
        src/IODevice.h
        src/IODevice.cpp
        test/StagedProviderTest.cpp
        src/Sorter.cpp
        src/Sorter.h
        src/Consumer.h
        src/Witness.h
        test/helpers/Printer.h
        test/helpers/Printer.cpp
        src/Generator.h
        src/Generator.cpp
        )

add_custom_command(TARGET testStagedProvider
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testStagedProvider
        COMMENT "Running testStagedProvider..."
)

add_custom_target(runNonFaultTests
        COMMAND $<TARGET_FILE:testConsumer>
        COMMAND $<TARGET_FILE:testIODevice>
        COMMAND $<TARGET_FILE:testEmptyProvider>
        COMMAND $<TARGET_FILE:testDeviceProvider>
        COMMAND $<TARGET_FILE:testWitness>
        COMMAND $<TARGET_FILE:testPQ>
)

add_custom_command(TARGET runNonFaultTests
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/runNonFaultTests
        COMMENT "Running runNonFaultTests..."
)

add_custom_target(runFaultTests
        COMMAND $<TARGET_FILE:testSorter>
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
        COMMAND $<TARGET_FILE:testConsumer>
        COMMAND $<TARGET_FILE:testIODevice>
        COMMAND $<TARGET_FILE:testDeviceProvider>
        COMMAND $<TARGET_FILE:testWitness>
        COMMAND $<TARGET_FILE:testProvider>
        COMMAND $<TARGET_FILE:testPQ>
        COMMAND $<TARGET_FILE:testSorter>
        COMMAND $<TARGET_FILE:testRecord>
        COMMAND $<TARGET_FILE:testStagedProvider>
        COMMAND $<TARGET_FILE:testStorageProvider>
)

add_custom_command(TARGET runAllTests
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/runAllTests
        COMMENT "Running runAllTests..."
)
