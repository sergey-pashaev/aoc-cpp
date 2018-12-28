// Day 6, Part One

// Because your neighbors keep defeating you in the holiday house
// decorating contest year after year, you've decided to deploy one
// million lights in a 1000x1000 grid.

// Furthermore, because you've been especially nice this year, Santa
// has mailed you instructions on how to display the ideal lighting
// configuration.

// Lights in your grid are numbered from 0 to 999 in each direction;
// the lights at each corner are at 0,0, 0,999, 999,999, and
// 999,0. The instructions include whether to turn on, turn off, or
// toggle various inclusive ranges given as coordinate pairs. Each
// coordinate pair represents opposite corners of a rectangle,
// inclusive; a coordinate pair like 0,0 through 2,2 therefore refers
// to 9 lights in a 3x3 square. The lights all start turned off.

// To defeat your neighbors this year, all you have to do is set up
// your lights by doing the instructions Santa sent you in order.

// For example:

// turn on 0,0 through 999,999 would turn on (or leave on) every
// light.

// toggle 0,0 through 999,0 would toggle the first line of 1000
// lights, turning off the ones that were on, and turning on the ones
// that were off.

// turn off 499,499 through 500,500 would turn off (or leave off) the
// middle four lights.

// After following the instructions, how many lights are lit?

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

typedef std::array<std::array<bool, size>, size> grid;

void process(const instruction& instr, grid& g) {
    for (std::size_t i = instr.from.i; i <= instr.to.i; ++i) {
        for (std::size_t j = instr.from.j; j <= instr.to.j; ++j) {
            switch (instr.cmd) {
                case instruction::on: {
                    g[i][j] = true;
                    break;
                }
                case instruction::off: {
                    g[i][j] = false;
                    break;
                }
                case instruction::toggle: {
                    g[i][j] = !g[i][j];
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

    int lit = 0;
    const std::size_t sz = g.size();
    for (std::size_t i = 0; i < sz; ++i) {
        for (std::size_t j = 0; j < sz; ++j) {
            if (g[i][j]) ++lit;
        }
    }

    std::cout << lit << '\n';
    return 0;
}
