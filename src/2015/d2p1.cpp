// Day 2, Part One

// The elves are running low on wrapping paper, and so they need to
// submit an order for more. They have a list of the dimensions
// (length l, width w, and height h) of each present, and only want to
// order exactly as much as they need.

// Fortunately, every present is a box (a perfect right rectangular
// prism), which makes calculating the required wrapping paper for
// each gift a little easier: find the surface area of the box, which
// is 2*l*w + 2*w*h + 2*h*l. The elves also need a little extra paper
// for each present: the area of the smallest side.

// For example:

// A present with dimensions 2x3x4 requires 2*6 + 2*12 + 2*8 = 52
// square feet of wrapping paper plus 6 square feet of slack, for a
// total of 58 square feet.

// A present with dimensions 1x1x10 requires 2*1 + 2*10 + 2*10 = 42
// square feet of wrapping paper plus 1 square foot of slack, for a
// total of 43 square feet.

// All numbers in the elves' list are in feet. How many total square
// feet of wrapping paper should they order?

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>

long surface(const char* s) {
    if (!s) return 0;

    char* end = 0;
    long dim[3] = {};
    int n = 0;
    while (*s) {
        if (*s == 'x') ++s;
        dim[n++] = std::strtol(s, &end, 10);
        s = end;
    }

    long side[3] = {dim[0] * dim[1], dim[1] * dim[2], dim[2] * dim[0]};
    long min = std::min(side[0], std::min(side[1], side[2]));

    return 2 * (side[0] + side[1] + side[2]) + min;
}

void tests() {
    assert(surface(nullptr) == 0);
    assert(surface("") == 0);
    assert(surface("2x3x4") == 58);
    assert(surface("1x1x10") == 43);
}

int main() {
    tests();

    long total = 0;
    for (std::string line; std::getline(std::cin, line);) {
        total += surface(line.c_str());
    }

    std::cout << total << '\n';
    return 0;
}
