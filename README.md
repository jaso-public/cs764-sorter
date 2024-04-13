# CS764-sorter
CS 764 class project for doing external sorts

# Functions

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

## Record Sizes
### 20B
### 1,000B
### 2,000B

# Individual Contributions
## Jaso

## Morgan




