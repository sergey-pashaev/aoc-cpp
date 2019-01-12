// Day 8, Part One

// Space on the sleigh is limited this year, and so Santa will be
// bringing his list as a digital copy. He needs to know how much
// space it will take up when stored.

// It is common in many programming languages to provide a way to
// escape special characters in strings. For example, C, JavaScript,
// Perl, Python, and even PHP handle special characters in very
// similar ways.

// However, it is important to realize the difference between the
// number of characters in the code representation of the string
// literal and the number of characters in the in-memory string
// itself.

// For example:

// "" is 2 characters of code (the two double quotes), but the string
// contains zero characters.

// "abc" is 5 characters of code, but 3 characters in the string data.

// "aaa\"aaa" is 10 characters of code, but the string itself contains
// six "a" characters and a single, escaped quote character, for a
// total of 7 characters in the string data.

// "\x27" is 6 characters of code, but the string itself contains just
// one - an apostrophe ('), escaped using hexadecimal notation.

// Santa's list is a file that contains many double-quoted string
// literals, one on each line. The only escape sequences used are \\
// (which represents a single backslash), \" (which represents a lone
// double-quote character), and \x plus two hexadecimal characters
// (which represents a single character with that ASCII code).

// Disregarding the whitespace in the file, what is the number of
// characters of code for string literals minus the number of
// characters in memory for the values of the strings in total for the
// entire file?

// For example, given the four strings above, the total number of
// characters of string code (2 + 5 + 10 + 6 = 23) minus the total
// number of characters in memory for string values (0 + 3 + 7 + 1 =
// 11) is 23 - 11 = 12.

#include <cassert>
#include <cctype>
#include <iostream>
#include <string>
#include <utility>

bool is_hex(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
           (c >= 'A' && c <= 'F');
}

std::pair<int, int> count(const std::string& s) {
    int code = 0;
    int mem = 0;

    const char* p = s.c_str();
    while (*p) {
        if (*p == '"') {
            // quote
            ++code;
            ++p;
        } else if (*p == '\\') {
            if (*(p + 1) == '\\' || *(p + 1) == '"') {
                // backslash or quoted quote
                p += 2;
                code += 2;
                ++mem;
            } else if (*(p + 1) == 'x' && is_hex(*(p + 2)) &&
                       is_hex(*(p + 3))) {
                // hex
                p += 4;
                code += 4;
                ++mem;
            }
        } else {
            // regular character
            ++p;
            ++code;
            ++mem;
        }
    }

    return std::make_pair(code, mem);
}

void tests() {
    assert(count(R"("")") == std::make_pair(2, 0));
    assert(count(R"("abc")") == std::make_pair(5, 3));
    assert(count(R"("aaa\"aaa")") == std::make_pair(10, 7));
    assert(count(R"("\x27")") == std::make_pair(6, 1));
}

int main() {
    tests();

    int code = 0;
    int mem = 0;
    for (std::string line; std::getline(std::cin, line);) {
        const auto ret = count(line);
        code += ret.first;
        mem += ret.second;
    }

    std::cout << (code - mem) << '\n';

    return 0;
}
