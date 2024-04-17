# CS764-sorter
This is an external merge sort application that was written for the CS-764 class project. 

# Tools
The tools (in the ./src/tools directory) enable creating an input file with randomly generated, alphanumeric record and allowing the external merge sort to run.

## Generate
The generate tools enable the creation of an input.txt file that contains randomly generated, alphanumeric records. It will parse user input to customize the creation of records by allowing a user to determine: 
the name of the input file, record count, record size, probability, range, and the inclusion of a new line character at the end of each record.
An explanation of these customizations and their flags are explained below. 

### Flags
- -s: enables a user to determine the record size of the generated records. Its default value if 128.
- -f: enables a user to determine the name of the output file filled with generated records. Its default value is input.txt.
- -c: enables a user to determine the total number of records that are generated. Its default value is 1000.
- -p: enables a user to determine the percentage of records generated that will be required to fall within a set range. This percentage determines the likelihood that duplicate records are generated. Its default value is 0.
- -r: enables a user to set the upperbound of the range in which records of the specified percentage will be generated between. This range consists of 0 to the given range. Its default value is 100.
- -n: enables a user to decide if a new line character should be included at the end of each generated record. The inclusion of the new line character allows records to be easier to read within the given file. The default value is to not include this character.

### Compile and Run Generate Tool
#### Step 1: Build the CMake File
Navigate into the build directory and run cmake ..
#### Step 2: Run make generate
This will compile all the necessary classes to create the input file.
#### Step 3: Run ./generate 
If you would like to add customizations to this program, such as defining the record size, include all the necessary flags and values. Ex: ./generate -s 120

## Sort
The sort tools compile and run the external merge sort logic with an input.txt file. This logic can be found in SortMain.cpp. Like the generate method, it contains a variety of flags that allow the completion of the sort logic to be customized. 
The flags for this command are explained below.

### Flags
- -o: enables the user to determine the given trace file. Its default value is an empty string.
- -i: enables the user to determine the input file that will contain the unsorted records. Its default value is input.txt.
- -j: enables the user to determine the output file that the sorted records will be written to. Its default value is output.txt.
- -d: enables the user to determine the file that the SSD's staged records will be read/written to. Its default value is ssd.staging.
- -h: enables the user to determine the file that the HDD's staged records will be read/written to. Its default value is hdd.staging.
- -s: enables the user to determine the record size of the generated records. Its default value if 128.
- -x: enables the user to determine the cache size. Its default value is 1MB.
- -y: enables the user to determine the memory size. Its default value is 100MB.
- -z: enables the user to determine the SSD size. Its default value is 10GB.

### Compile and Run Sort
#### Step 1: Build the CMake File
Navigate into the build directory and run cmake ..
#### Step 2: Run make sort
This will compile all the necessary classes needed to preform the external sort.
#### Step 3: Run ./sort
If you would like to add customizations to this program, such as defining the record size, include all the necessary flags and values. Ex: ./sort -s 120

## Verify
The verify tool checks that user input can be parsed and a given input file can be properly handled by the IODevice and filtered through the providers, witness, and consumer. It contains 2 flags that allow the user to determine the input file and the record size.

### Flags
- -s: enables a user to determine the record size of the generated records. Its default value if 128.
- -i: enables the user to determine the input file that will contain the unsorted records. Its default value is input.txt.

### Compile and Run Verify
#### Step 1: Build the CMake File
Navigate into the build directory and run cmake ..
#### Step 2: Run make verify
This will compile all the necessary classes needed to run this verify function.
#### Step 3: Run ./verify
If you would like to add customizations to this program, such as defining the record size, include all the necessary flags and values. Ex: ./verify -s 120

# Classes
## Witness
The witness class is designed to verify the correctness of the sorting algorithm by comparing a witness before sorting to a witness after sorting.
### Class Constructor
Its class constructor takes in a provider that it will obtain records from. It initializes the class' values, including the count (number of returned records), checksum, and the default sorted value of true.

### next()
The next method returns the next record from the provider or a null pointer if the next record does not exist. It also continuously computes the class' checksum value which is used when verifying the sort order between the lower and upper witness. This method keeps track of the number of duplicate records that were uncovered, and it changes the class' sorted value to false if two unsorted, consecutive records were ucovered.

### getCount()
This method returns the total number of records that have been returned by the class

### getDuplicateCount()
This method returns the total number of duplicates that the class has seen.

### getChecksum()
This method returns the class' computed checksum value that can be used to verify the validity between two witnesses

### isSorted()
This method returns a boolean value to display if the class was sorted or not.

### writeStats(std::ostream& out, string name)
This method will print out the class' statistics, including the count (number of records returned by the class), checksum, sorted, and duplicate count values.

## TournamentPQ
This class is utilized to obtain the next record with the smallest key from a vector of providers.
### Class Constructor
The constructor initializes a tournament between the given providers.

### next()
This method will return the next record with the smallest key from the given providers in the tournament or a null pointer if the tournament is complete. It will continue to run the tournament between the providers until the tournament is complete.

### isFirstWinner()
This method compares two records and is utilized to assist in the completion of the tournament. If the first given record exists and is smaller than the second given record or the second given record does not exist, then it returns true. In all other cases, it returns false.

## Storage Config
The Storage Config class is a class that stores values to be utilized within the Storage Provider class. It helps guide the reading of records from SSD chunks.

## Storage Provider
This class it utilized to read chunks from the SSD until all SSD chunks have been read.

### Class Constructor
The class constructor initializes the class' initial values and Storage Config.

### next()
The next method will read the next record from the current SSD chunk or obtain a new SSD chunk to return a record from if it exists. If there are no more records/chunks to read, it will return a null pointer.

## StagingConfig
This class contains values to be used within the Staged Provider class.

## Staged Provider
This class is utilized to obtain and read records between the HDD and SSD. It will continue to transfer chunks between the HDD to the SSD until there are no longer any records on the HDD.

### Class Constructor
The constructor sets the class' default values and Staging Config class.

### next()
The next method will continue to pull chunks out of the HDD and place them into the SSD for reading. If all records have been read from the HDD, then a null pointer will be returned.

## SorterConfig
The sorter configuration class contains values to provide to the Sorter class such as the size of memory and the size of the SSD.

### writeStats(std::ostream& out)
This method will print the values held by the class to the output stream including: spill fraction, cache size, memory size, HDD read size, SSD read size, and SSD size.

## Sorter
This class contains all of our logic for completing the sort including: graceful degradation, spilling, and merging.

### Class Constructor
The constructor initializes the class' values and ensures that an IO device was created for both the SSD and HDD. It begins the sorting algorithm by calling startSort().

### next()
This method will return the next sorted record.

### writeStats(std::ostream& out)
This method prints out the statistics of the sorting algorithm to a given output stream including its time of completion and comparison count.

### startSort()
This method completes the external merge sort logic. It returns a provider that will return records in sorted order.

### makeFreeSpace()
This method preforms spilling from a higher memory hierarchy to a lower one. It enables graceful degradation by defining a spill fraction.

### releaseMemory(int numberBuffersToRelease)
This method is able to free up memory before or after a merge by writing runs to the SSD and/or HDD via storeRun().

### storeRun(shared_ptr<Provider> provider, long recordCount)
This method will store runs by writing them to the SSD or HDD depending on the available space of the SSD.

### roundUp(long value, long multiple)
This method will return the nearest, rounded up multiple of the variable multiple in comparison to the given value.

## Run
This class represents a run which is a group of records that can fit into memory. It is used as a type in the Sorter class.

## Record
The record class is utilized to store and to preform operations on the records.

### Class Constructor
The class constructor stores the record within the class' data variable.

### staticInitialize(uint32_t recordSize)
This method is utilized to set the static variables of the class, recordSize and compareCount.

### compareTo(const shared_ptr<Record> &other)
This method will compare a given record (other) to the current record. It will return a value 1, 0, or -1 to indicate how the two records compare to each other. 

### store(uint8_t *dst)
This method copies the contents of the record into the specified memory location.

### store(uint8_t *dst, int offset, int numToCopy)
This method will copy a part of the record, starting at the offset value, into the specified memory location.

### checksum()
This method computes and returns the checksum of the record

### dump(string message)
This method will print out the contents of the record and its checksum.

### getRecordSize()
This method returns the size of the record.

### getCompareCount()
This method will return the number of times the record has been compared to another record.

### resetCompareCount()
This method will reset the record's compare count back to 0.

## Provider
The provider class will generate all the desired records. It contains a virtual next() method that all other providers must implement. 

### next()
This method is the virtual method that each Provider must implement. With each call to next(), a record is received in some order that is determined by the Provider type. For example, if the records are being provided by a file, then they will be returned in the order that they were in within the file. If the Provider is the Sorter, then records will be returned in sorted order. This method will continue to return a record until all records have been returned. Then, it returns a null pointer.

## SingleProvider
This class is a simple provider that can easily be reused. It will return only one record, that is set by reset() before returning null pointers. Its reset() function can be called multiple times.

### Class constructor
The constructor sets the class' record variable to be a null pointer. This means that a call to next() will continue to return a null pointer until a record is set via reset().

### reset()
This method will set the record to be returned by the Single Provider to a record that will be returned by the next call to next(). The record is only returned once then, the next calls to next() will continue to return null pointers.

### next()
This method will return a pointer to a record or a null pointer if the record has already been returned after being reset().

## MemoryProvider
The Memory Provider extracts records from a packed buffer of records. It requires that records are sorted within the buffer and that each record consumes exactly recordSize number of bytes. You must know how many records are stored in the buffer when you use the MemoryProvider  (There are no sentinels in the buffers)

### Class Constructor
The class constructor obtains the buffer to extract records from and initializes class variables.

### next()
This method will return the next record from the buffer. If all records from the buffer have been returned, it will return a null pointer.

## EmptyProvider
This class is an empty provider that only returns null pointers via its next() method. It was created to by utilized by the Sorter when there are no more records to return.

### next()
This method will continue to return null pointers, indicating that there are no records to be returned.

## RandomProvider
This class will generate random records based on various user specifications including the record count, duplicate probability, duplicate range, and/or the inclusion of a new line character at the end of the record. It is utilized for testing purposes to generate records instead of reading from an input file.

### Class Constructors
This class has multiple class constructors that enables a user to determine how many values for record generation that they would like to customize. The recordCount value represents how many records that this provider should return. The newLine boolean value will determine if a new line character is added to the end of the record. This option was included as it makes records easier to read and identify when printing them out or writing them to files. The duplicateProbability variable is the percentage of records that should be generated within the specified range (0-duplicateRange). This enables use to generate duplicates with a likely probability. 

### next() 
This method returns the generated record with the specified characteristics or a null pointer if the total number of records has already been generated.

## DeviceProvider
This is a provider that reads records from a device (file) and provides them to other providers via its next() method. It will eventually read the entire contents of the file. If the final read is not a complete record, it will write an error message to cerr, and it will return a null pointer instead of a record. This class is used to read records from the given input.txt file.

### Class Constructor
The class constructor initializes the class' initial values including the IODevice that will allow records from the particular file to be read.

### next()
This method will continue to read records from the given file until the end of the file has been reached. It will print out an error message to cerr that will indicate only a partial record was left as the final read. If this error occurs, a null pointer will be returned. If all records were successfully returned, it will return a null pointer.

## DropFirst
This class is a provider that will drop the first record (will not return it) before returning records with each next() call. It is only utilized for testing purposes.

### Class Constructor
The class constructor automatically drops the first record from the given source, so it is not returned.

### next()
This method returns the next record from the provider or a null pointer if all records have been returned.

## IODevice
This class will read and write data from a file. It is utilized to read data from the input file and to read/write from temporary files and the final output file.

### Class Constructor
The class constructor will initialize the class' variables and open the given file for reading and writing. It will catch an exception if the given file cannot be open.

### Class Destructor
The class destructor will close the file that the class is reading/writing from.

### read(uint64_t offset, uint8_t* dst, uint32_t len)
This method will read the desired number of bytes from the file at the specified offset into the given buffer. 

### write(uint64_t offset, uint8_t* src, uint32_t len)
This method will write the specified number of bytes from the file into the given buffer at the specified offset.

This method will print out statistics from the read/write operations to the given stream. Some of the statistics it displays are the read count, read size, and write size.

### Get methods
This class contains a variety of get methods, such as getReadCount(), getReadSize(), and getTotalRead(). These methods will return the appropriate class variables corresponding to their method name. These methods are able to display simple statistics about the class' read and write operations.

## Convert
This method is utilized with SortMain.cpp and GenerateMain.cpp to parse the given arguments from the user. It enables the flags, such as -s, to be parsed from the users input when generating and sorting records.
### parseInteger(const char* str, IntegerType& outValue)
This method will parse integers from the input argument. It obtains and sets values such as the record size and record count from the input arguments.

### parseFloatingPoint(const std::string& str, T& value)
This method will parse floating points from the input arguments. It obtains and sets the probability value, indicated by the -p flag, when generating records.

## Consumer
The Consumer class is utilized to continuously consume records from a provider until all records have been consumed. Like the Provider class, the Consumer class is a virtual class that will be implemented by various Consumers

### consume()
This method is a virtual method that must be implemented by all other Consumers. It will continue to consume all records from a provider until there are no records left.

## NoopConsumer
This class is a testing class that simply just continues to call the providers next() method until all records have been returned (a null pointer was reached).

### Class Constructor
The constructor sets the given source provider to the class' provider, so it can return records.

### consume()
This method will continue to call the provider's next() method until all records have been returned (a null pointer is returned).

## DeviceConsumer
This is a class that will write the records that it consumes from the provider to a particular file. This consumer is utilized to write our sorted records to the output.txt file.

### Class Constructor
The constructor initializes the class' variables and creates a buffer of the desired size. This buffer will be used to store records before writing them to the output file.

### consume()
This method contains to obtain records from the provider and passes them to the appendRecord() function, so they are placed within the buffer. This function continues to run until all records have been obtained (a null pointer has been returned).

### doWrite()
This method writes records from the buffer to the output file via the IO Device. It then clears the buffer, so it can store more records.

### appendRecord(shared_ptr<Record> &ptr)
This method will continue to store records until the buffer until the buffer is full. Once the buffer is full, it will call doWrite() to write the buffer contents to the output file.

## Generator
This class contains methods that can create two different types of records, one filled with alphanumeric values and one filled with an integer.

### makeRandomRecord(std::mt19937 &gen, bool newLine)
This method creates a record filled with random alphanumeric values. The newLine parameter indicates whether a new line character should be included at the end of the record. The inclusion of this new line character can make viewing the generated record in a file or through a stream easier.

### makeIntegerRecord(uint32_t value, bool newLine)
This method creates a record filled with a given integer value. The newLine parameter indicates whether a new line character should be included at the end of the record. The inclusion of this new line character can make viewing the generated record in a file or through a stream easier.

### isCrcValid(shared_ptr<Record> record)
This method will check the correctness and validity of a given record's CRC value.

# Implemented Techniques
## Tournament Tree
The tournament tree can be seen within the TournamentPQ.cpp and TournamentPQ.h files located within the ./src directory

## Variable Size Records
The generator class accepts various flags including the "-s" flag for record size and the "-c" flag for record count. This enables a user to generate records of variable sizes and counts. This can be seen within the generate.cpp file in the ./src/tools directory.

## Minimum Count of Row

## Duplicate Removal

## Cache Size Mini Runs

## Device Optimized Page Sizes

## Spilling Memory-to-SSD
 
## Spilling Memory from SSD to Disk

## Graceful Degradation
### Into Merging
### Beyond One Merge Step

## Optimized Merge Patterns
We completed optimized merge patterns through the sorter class.

## Verifying Sort Order
The verification of the sort order is completed via the Witness class. It ensures that each next() record is greater than the previously returned record. If not, the class' sorted variable is set to false (line 34). This boolean value can be obtained from the class' isSorted() method (lines 66-68). This class can be found in the Witness.h file in ./src.

# Time Taken for Test Case
## Input Sizes
### 50MB
### 125MB
### 12GB
### 120GB
record count: 1073741824
record size: 120
probability: 0.01
range: 9999
new line: 1
Device: input.txt
write
count        : 491520 calls
size         : 128849018880 bytes
time         : 33.204455 seconds
average      : 3880473812 bytes/second
maxTime      : 0.030100 seconds
Witness: generate
record count     : 1073741824
checksum         : 2323403496170342774
sorted           : false
duplicate count  : 7


## Record Sizes
### 20B
### 1,000B
### 2,000B

# Individual Contributions
## Jaso

## Morgan




