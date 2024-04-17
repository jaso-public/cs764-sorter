/**
 * a bogus main function that just calls into generateMain.
 * This way the linker does not get unhappy because we
 * have more that one main function. It was created to allow us to
 * write test cases that call generateMain().
 *
 * @param argc standard main number of args
 * @param argv char** args for the program
 * @return whatever generateMain returns.
 */

#include "Generate.h"

int main(int argc, char** argv)  {
    return generateMain(argc, argv);
}
