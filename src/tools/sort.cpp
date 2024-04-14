/**
 * a bogus main function that just calls into sortMain.
 * This way the linker does not get unhappy because we
 * have more that obe main function.
 *
 * @param argc standard main number od args
 * @param argv char** args for the program
 * @return whatever sortMain returns.
 */

int sortMain(int argc, char** argv);

int main(int argc, char** argv)  {
    return sortMain(argc, argv);
}
