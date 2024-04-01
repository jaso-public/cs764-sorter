#include <stdio.h>

#if 0
#include <assert.h>
#else
#include <stdlib.h>
#endif

#include "OutlinedFiles/defs.h"

/**
 * This class is a testing class
 * @param predicate a predicate value indicating a failure if false; if true, nothing prints to terminal
 * @param file the file being read
 * @param line the line within the file that is causing the error
 */

void Assert (bool const predicate,
		char const * const file, int const line)
{
	if (predicate)
		return;

	fflush (stdout);
	fprintf (stderr, "failed assertion at %s, %d\n", file, line);
	fflush (stderr);

#if 0
	assert (false);
#else
	exit (1);
#endif
} // Assert
