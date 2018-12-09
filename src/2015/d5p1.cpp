// Day 5, Part One

// Santa needs help figuring out which strings in his text file are
// naughty or nice.

// A nice string is one with all of the following properties:

// It contains at least three vowels (aeiou only), like aei, xazegov,
// or aeiouaeiouaeiou.

// It contains at least one letter that appears twice in a row, like
// xx, abcdde (dd), or aabbccdd (aa, bb, cc, or dd).

// It does not contain the strings ab, cd, pq, or xy, even if they are
// part of one of the other requirements.

// For example:

// ugknbfddgicrmopn is nice because it has at least three vowels
// (u...i...o...), a double letter (...dd...), and none of the
// disallowed substrings.

// aaa is nice because it has at least three vowels and a double
// letter, even though the letters used by different rules overlap.

// jchzalrnumimnmhp is naughty because it has no double letter.

// haegwjzuvuyypxyu is naughty because it contains the string xy.

// dvszwmarrgswjxmb is naughty because it contains only one vowel.

#include <cassert>
#include <iostream>
#include <string>

bool is_nice(const char* s) {
    if (!s) return false;

    int vowels = 0;
    bool twice = false;

    const char* forbidden[] = {"ab", "cd", "pq", "xy"};
    bool has_forbidden = false;

    while (*s) {
        const char c = *s;

        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            ++vowels;
        }

        if (*(s + 1)) {
            if (*(s + 1) == *s) {
                twice = true;
            }

            for (int i = 0; i < 4; ++i) {
                if (*s == forbidden[i][0] && *(s + 1) == forbidden[i][1]) {
                    has_forbidden = true;
                    break;
                }
            }
        }

        ++s;
    }

    return !has_forbidden && (vowels >= 3 && twice);
}

void tests() {
    assert(is_nice("ugknbfddgicrmopn"));
    assert(is_nice("aaa"));
    assert(!is_nice("jchzalrnumimnmhp"));
    assert(!is_nice("haegwjzuvuyypxyu"));
    assert(!is_nice("dvszwmarrgswjxmb"));
}

int main() {
    tests();

    int nice = 0;
    for (std::string line; std::getline(std::cin, line);) {
        nice += is_nice(line.c_str());
    }

    std::cout << nice << '\n';

    return 0;
}
