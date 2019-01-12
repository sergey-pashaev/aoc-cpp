// Day 8, Part Two

// Now, let's go the other way. In addition to finding the number of
// characters of code, you should now encode each code representation
// as a new string and find the number of characters of the new
// encoded representation, including the surrounding double quotes.

// For example:

// "" encodes to "\"\"", an increase from 2 characters to 6.

// "abc" encodes to "\"abc\"", an increase from 5 characters to 9.

// "aaa\"aaa" encodes to "\"aaa\\\"aaa\"", an increase from 10 characters to 16.

// "\x27" encodes to "\"\\x27\"", an increase from 6 characters to 11.

// Your task is to find the total number of characters to represent
// the newly encoded strings minus the number of characters of code in
// each original string literal. For example, for the strings above,
// the total encoded length (6 + 9 + 16 + 11 = 42) minus the
// characters in the original code representation (23, just like in
// the first part of this puzzle) is 42 - 23 = 19.

#include <cassert>
#include <cctype>
#include <iostream>
#include <string>
#include <utility>

bool is_hex(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
           (c >= 'A' && c <= 'F');
}

std::pair<int, int> count(const std::string& s, bool encoded = false) {
    int code = 0;
    int mem = 0;

    const char* p = s.c_str();
    while (*p) {
        if (*p == '"') {
            // quote
            code += encoded ? 3 : 1;
            ++p;
        } else if (*p == '\\') {
            if (*(p + 1) == '\\' || *(p + 1) == '"') {
                // backslash or quoted quote
                p += 2;
                code += encoded ? 4 : 2;
                ++mem;
            } else if (*(p + 1) == 'x' && is_hex(*(p + 2)) &&
                       is_hex(*(p + 3))) {
                // hex
                p += 4;
                code += encoded ? 5 : 4;
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
    assert(count(R"("")", true) == std::make_pair(6, 0));
    assert(count(R"("abc")", true) == std::make_pair(9, 3));
    assert(count(R"("aaa\"aaa")", true) == std::make_pair(16, 7));
    assert(count(R"("\x27")", true) == std::make_pair(11, 1));
}

int main() {
    tests();

    int code_raw = 0;
    int code_enc = 0;
    for (std::string line; std::getline(std::cin, line);) {
        const auto raw = count(line);
        const auto enc = count(line, true);
        code_raw += raw.first;
        code_enc += enc.first;
    }

    std::cout << (code_enc - code_raw) << '\n';

    return 0;
}
