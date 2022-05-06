#include "define.h"
#include "util.hpp"

void print_help() {
    printf("Welcome to SHARNN shell.\n");
    printf("Input: E - Show the example of SHARNN.\n");
    printf("       I - Show the introduction of SHARNN.\n");
    printf("       F - Input a file path and get its SHARNN.\n");
    printf("       S - Input a string and get its SHARNN.\n");
    printf("       H - Print this help.\n");
}

void print_example() {
    printf("We have no examples till now QAQ.\n");
}

void print_intro() {
    printf("SHARNN is a conbination of traditional Sponge Structure Hash & "
           "Recursive Neural Network(RNN).\n");
    printf("The algorithm is the 2nd homework of Introduction to Modern Cryptogrophy.\n");
    printf("Developed by Ashitemaru, c7w, lambda, xsun, ayf.\n");
}

/** @note: Read till a '\n', '\n' not included in the result string
 */
std::string read_line() {
    std::string buf = "";
    char ch = '\0';
    while (true) {
        ch = getchar();
        if (ch == '\n') break;
        else buf.push_back(ch);
    }
    return buf;
}

int main() {
    ByteStream::test();

    print_help();
    printf(">>> ");

    while (true) {
        std::string buf = read_line();

        // When the length of command is not 1,
        // print a new '>>>' and continue
        if (buf.length() != 1) {
            if (buf.length() > 1) printf("Invalid command!\n");
            printf(">>> ");
            continue;
        }

        switch (buf[0]) {
            case 'E': {
                print_example();
                break;
            }

            case 'F': {
                printf("... ");
                std::string input = read_line();
                if (input.length() == 0) {
                    printf("Length of input file path cannot be 0. Stopped.\n");
                } else {
                    printf("SHARNN: %s\n", file_hash(input).c_str());
                }
                break;
            }

            case 'S': {
                printf("... ");
                std::string input = read_line();
                if (input.length() == 0) {
                    printf("Length of input string cannot be 0. Stopped.\n");
                } else {
                    printf("SHARNN: %s\n", string_hash(input).c_str());
                }
                break;
            }

            case 'I': {
                print_intro();
                break;
            }
            
            case 'H': {
                print_help();
                break;
            }

            default: {
                printf("Invalid command!\n");
                break;
            }
        }

        printf(">>> ");
    }

    return 0;
}