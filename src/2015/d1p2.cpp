// Day 1, Part Two

// Now, given the same instructions, find the position of the first
// character that causes him to enter the basement (floor -1). The
// first character in the instructions has position 1, the second
// character has position 2, and so on.

// For example:

//   ) causes him to enter the basement at character position 1.
//   ()()) causes him to enter the basement at character position 5.

// What is the position of the character that causes Santa to first
// enter the basement?

#include <cassert>
#include <iostream>
#include <string>

int AtBasement(const char *s) {
    int floor = 0;
    int pos = 0;
    for (char c = '\0'; (c = *s); ++s) {
        ++pos;
        switch (c) {
            case '(': {
                ++floor;
                break;
            }
            case ')': {
                --floor;
                break;
            }
        }
        if (floor == -1) return pos;
    }
    return 0;
}

void tests() {
    assert(AtBasement(")") == 1);
    assert(AtBasement("()())") == 5);
}

int main() {
    tests();

    for (std::string line; std::getline(std::cin, line);) {
        std::cout << AtBasement(line.c_str()) << '\n';
    }
    return 0;
}
