// Day 2, Part Two

// The elves are also running low on ribbon. Ribbon is all the same
// width, so they only have to worry about the length they need to
// order, which they would again like to be exact.

// The ribbon required to wrap a present is the shortest distance
// around its sides, or the smallest perimeter of any one face. Each
// present also requires a bow made out of ribbon as well; the feet of
// ribbon required for the perfect bow is equal to the cubic feet of
// volume of the present. Don't ask how they tie the bow, though;
// they'll never tell.

// For example:

// A present with dimensions 2x3x4 requires 2+2+3+3 = 10 feet of
// ribbon to wrap the present plus 2*3*4 = 24 feet of ribbon for the
// bow, for a total of 34 feet.

// A present with dimensions 1x1x10 requires 1+1+1+1 = 4 feet of
// ribbon to wrap the present plus 1*1*10 = 10 feet of ribbon for the
// bow, for a total of 14 feet.

// How many total feet of ribbon should they order?

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>

long ribbon(const char* s) {
    if (!s) return 0;

    char* end = 0;
    long dim[3] = {};
    int n = 0;
    while (*s) {
        if (*s == 'x') ++s;
        dim[n++] = std::strtol(s, &end, 10);
        s = end;
    }

    long perimeter[3] = {2 * (dim[0] + dim[1]), 2 * (dim[1] + dim[2]),
                         2 * (dim[2] + dim[0])};

    long min = std::min(perimeter[0], std::min(perimeter[1], perimeter[2]));

    long bow = dim[0] * dim[1] * dim[2];

    return min + bow;
}

void tests() {
    assert(ribbon(nullptr) == 0);
    assert(ribbon("") == 0);
    assert(ribbon("2x3x4") == 34);
    assert(ribbon("1x1x10") == 14);
}

int main() {
    tests();

    long total = 0;
    for (std::string line; std::getline(std::cin, line);) {
        total += ribbon(line.c_str());
    }

    std::cout << total << '\n';
    return 0;
}
