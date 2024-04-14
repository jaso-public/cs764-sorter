# CS764-sorter
CS 764 class project for doing external sorts

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

## next()
The next method will continue to pull chunks out of the HDD and place them into the SSD for reading. If all records have been read from the HDD, then a null pointer will be returned.


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




