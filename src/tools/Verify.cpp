/**
 * a bogus main function that just calls into verifyMain.
 * This way the linker does not get unhappy because we
 * have more that one main function.
 *
 * @param argc standard main number of args
 * @param argv char** args for the program
 * @return whatever verifyMain returns.
 */

#include "VerifyMain.h"

int main(int argc, char** argv)  {
    return verifyMain(argc, argv);
}