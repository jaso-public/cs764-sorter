
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "rng.h"

// A Generic Random Number Generator from: https://github.com/thompsonsed/RandomNumberGeneration/blob/main/Xoshiro256plus.h
// declares unsigned integer/array with 64 bits
static uint64_t x = 12345;
// a table used to produce random numbers
static uint64_t shuffle_table[4] = {UINT64_C(0x94D049BB133111EB), 
                                    UINT64_C(0x9E3779B97F4A7C15), 
                                    UINT64_C(0xBF58476D1CE4E5B9),
                                    UINT64_C(0xF384A7BD1945DEB1)};


/**
 * Creates a hash value for x
 * the SplitMix64 taken from above
 * this is just used to initialize the Xoshiro256plus generator
 */
uint64_t shift() {
    uint64_t z = (x += UINT64_C(0x9E3779B97F4A7C15));
    z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
    z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB);
    return z ^ (z >> 31);
}

/**
 * initialize the Xoshiro256plus random generator with some seed.
 * Creates a hash value for the seed and hashes shuffle_table
 */
void seed(uint64_t seed) {
    x = seed;
    for(int i=0 ; i<8; i++) shift();
    for(int i=0 ; i<4; i++) shuffle_table[i] = shift();  
}

/**
 * rotate left a 64 bit value by the specified number of bits. 
 */
uint64_t rotl(const uint64_t &value, uint8_t bits) {
    return (value << bits) | (value >> (64 - bits));
}

/**
 * get the next pseudo random number from the Xoshiro256plus generator
 */
uint64_t next() {
    const uint64_t result_plus = shuffle_table[0] + shuffle_table[3];

    const uint64_t t = shuffle_table[1] << 17;

    shuffle_table[2] ^= shuffle_table[0];
    shuffle_table[3] ^= shuffle_table[1];
    shuffle_table[1] ^= shuffle_table[2];
    shuffle_table[0] ^= shuffle_table[3];

    shuffle_table[2] ^= t;

    shuffle_table[3] = rotl(shuffle_table[3], 45);

    return result_plus;
}

/**
 * fill an array of size bytes with a bunch of random bytes.
 */
void fill(int size, void* array) {
    // TODO: what does int & int do?
    int extra = size & 7;
    int num = size >> 3;

    uint64_t *a = (uint64_t*) array;
    for(int i=0; i<num ; i++) a[i] = next(); 

    if(extra) {
        uint64_t tmp = next();
        void* ending = a + num; 
        memcpy(ending, &tmp, extra);   
    }
}

/**
    Measure the rate of random byte generation.  Note this is not a very
    sophisticated test, and very susceptible to the L1,L2,L3 caching.  But
    It does give a sense for how fast we can generated random bytes.

    running on my MacAir compiled with gcc -O3 I got just shy of 8 GB/s.

    count:1000000 size: 100000 rate:7.838664 GB/s
    count:100000000 size: 1000 rate:7.837057 GB/s
    count:100000000 size: 100 rate:7.220394 GB/s
*/
double bytesPerSecond(uint32_t count, uint32_t size) {
    struct timespec start;
    struct timespec end;


    void* buffer = malloc(size);
    if(buffer == NULL) {
        perror("malloc");
        return -1;
    }

    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        perror("clock_gettime");
        free(buffer);
        return -1;
    }

    // do the work of generating the random arrays
    for(int i=0 ; i<count ; i++) {
        fill(size, buffer);
    }

    free(buffer);
      
    if (clock_gettime(CLOCK_REALTIME, &end) == -1) {
        perror("clock_gettime");   
        return -1;
    }

    uint64_t elapsed = end.tv_sec - start.tv_sec;
    elapsed *= (1000 * 1000 * 1000);
    elapsed += (end.tv_nsec - start.tv_nsec);

    double result = count;
    result = result * size;
    result = result / (1024 * 1024 * 1024); // bytes -> gigabytes
    result = result / elapsed;
    result = result * (1000 * 1000 * 1000); // nanos -> seconds

    return result;
}

/*
int main() {
    uint32_t count, size;
    seed(4);

    count = 1000000; size = 100000;
    printf("count:%u size: %d rate:%f GB/s\n", count, size, bytesPerSecond(count, size));

    count = 100000000; size = 1000;
    printf("count:%u size: %d rate:%f GB/s\n", count, size, bytesPerSecond(count, size));

    count = 100000000; size = 100;
    printf("count:%u size: %d rate:%f GB/s\n", count, size, bytesPerSecond(count, size));
    return 0;
}
*/