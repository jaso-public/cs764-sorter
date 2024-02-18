#include <stdio.h>

#if 0
#include <assert.h>
#else
#include <stdlib.h>
#endif

#include "defs.h"

/**
 * This function is utilized for checking errors in ???
 * @param predicate true of false value, unsure what it represents
 * @param file pointer to a constant char within a file?
 * @param line line that is producing error
 */
void Assert (bool const predicate,
		char const * const file, int const line)
{
	if (predicate)
		return;
    // forces stdout/stderr to standard output immediately
	fflush (stdout);
	fprintf (stderr, "failed assertion at %s, %d\n", file, line);
	fflush (stderr);

    // evaluated a compile time
#if 0
	assert (false);
#else
    // indicates that an error/interrupt has occured
	exit (1);
#endif
} // Assert
