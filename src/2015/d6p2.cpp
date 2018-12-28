// Day 6, Part Two

// You just finish implementing your winning light pattern when you
// realize you mistranslated Santa's message from Ancient Nordic
// Elvish.

// The light grid you bought actually has individual brightness
// controls; each light can have a brightness of zero or more. The
// lights all start at zero.

// The phrase turn on actually means that you should increase the
// brightness of those lights by 1.

// The phrase turn off actually means that you should decrease the
// brightness of those lights by 1, to a minimum of zero.

// The phrase toggle actually means that you should increase the
// brightness of those lights by 2.

// What is the total brightness of all lights combined after following
// Santa's instructions?

// For example:

// turn on 0,0 through 0,0 would increase the total brightness by 1.

// toggle 0,0 through 999,999 would increase the total brightness by
// 2000000.

#include <array>
#include <iostream>
#include <sstream>
#include <string>

const int size = 1000;

struct point {
    std::size_t i = 0;
    std::size_t j = 0;
};

struct instruction {
    enum command : char { on, off, toggle };

    command cmd;
    point from;
    point to;
};

typedef std::array<std::array<char, size>, size> grid;

void process(const instruction& instr, grid& g) {
    for (std::size_t i = instr.from.i; i <= instr.to.i; ++i) {
        for (std::size_t j = instr.from.j; j <= instr.to.j; ++j) {
            switch (instr.cmd) {
                case instruction::on: {
                    ++g[i][j];
                    break;
                }
                case instruction::off: {
                    if (g[i][j] > 0) --g[i][j];
                    break;
                }
                case instruction::toggle: {
                    g[i][j] += 2;
                    break;
                }
            }
        }
    }
}

instruction get_instruction(const std::string& s) {
    instruction i{};

    std::istringstream ss(s);
    std::string token;
    std::getline(ss, token, ' ');
    if (token == "toggle") {
        i.cmd = instruction::toggle;
    } else {
        std::getline(ss, token, ' ');
        if (token == "on") {
            i.cmd = instruction::on;
        } else {
            i.cmd = instruction::off;
        }
    }

    std::getline(ss, token, ',');
    i.from.i = std::stoi(token);

    std::getline(ss, token, ' ');
    i.from.j = std::stoi(token);

    // 'through'
    std::getline(ss, token, ' ');

    std::getline(ss, token, ',');
    i.to.i = std::stoi(token);

    std::getline(ss, token, '\n');
    i.to.j = std::stoi(token);

    return i;
}

int main() {
    grid g{};

    for (std::string line; std::getline(std::cin, line);) {
        process(get_instruction(line), g);
    }

    int brightness = 0;
    const std::size_t sz = g.size();
    for (std::size_t i = 0; i < sz; ++i) {
        for (std::size_t j = 0; j < sz; ++j) {
            brightness += g[i][j];
        }
    }

    std::cout << brightness << '\n';
    return 0;
}
