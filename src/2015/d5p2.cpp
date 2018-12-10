// Day 5, Part One

// Realizing the error of his ways, Santa has switched to a better
// model of determining whether a string is naughty or nice. None of
// the old rules apply, as they are all clearly ridiculous.

// Now, a nice string is one with all of the following properties:

// It contains a pair of any two letters that appears at least twice
// in the string without overlapping, like xyxy (xy) or aabcdefgaa
// (aa), but not like aaa (aa, but it overlaps).

// It contains at least one letter which repeats with exactly one
// letter between them, like xyx, abcdefeghi (efe), or even aaa.

// For example:

// qjhvhtzxzqqjkmpb is nice because is has a pair that appears twice
// (qj) and a letter that repeats with exactly one letter between them
// (zxz).

// xxyxx is nice because it has a pair that appears twice and a letter
// that repeats with one between, even though the letters used by each
// rule overlap.

// uurcxstgmygtbstg is naughty because it has a pair (tg) but no
// repeat with a single letter between them.

// ieodomkazucvgmuy is naughty because it has a repeating letter with
// one between (odo), but no pair that appears twice.

// How many strings are nice under these new rules?

#include <cassert>
#include <iostream>
#include <string>

bool is_nice(const std::string& str) {
    if (str.empty()) return false;

    bool pair = false;
    bool repeat = false;

    const std::size_t sz = str.size();
    for (std::size_t i = 0; i < sz; ++i) {
        if (i + 1 < sz) {
            if (str.find(str.c_str() + i, i + 2, 2) != std::string::npos) {
                if (repeat) return true;
                pair = true;
            }

            if (i + 2 < sz) {
                if (str.at(i) == str.at(i + 2)) {
                    if (pair) return true;
                    repeat = true;
                }
            }
        }
    }

    return pair && repeat;
}

void tests() {
    assert(is_nice("qjhvhtzxzqqjkmpb"));
    assert(is_nice("xxyxx"));
    assert(!is_nice("uurcxstgmygtbstg"));
    assert(!is_nice("ieodomkazucvgmuy"));
}

int main() {
    tests();

    int nice = 0;
    for (std::string line; std::getline(std::cin, line);) {
        nice += is_nice(line);
    }

    std::cout << nice << '\n';

    return 0;
}
