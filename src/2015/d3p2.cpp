// Day 3, Part Two

// The next year, to speed up the process, Santa creates a robot
// version of himself, Robo-Santa, to deliver presents with him.

// Santa and Robo-Santa start at the same location (delivering two
// presents to the same starting house), then take turns moving based
// on instructions from the elf, who is eggnoggedly reading from the
// same script as the previous year.

// This year, how many houses receive at least one present?

// For example:

// ^v delivers presents to 3 houses, because Santa goes north, and
// then Robo-Santa goes south.

// ^>v< now delivers presents to 3 houses, and Santa and Robo-Santa
// end up back where they started.

// ^v^v^v^v^v now delivers presents to 11 houses, with Santa going one
// direction and Robo-Santa going the other.

#include <cassert>
#include <cstddef>
#include <iostream>
#include <unordered_set>
#include <utility>

struct pair_hash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        std::size_t h1 = std::hash<T1>()(pair.first);
        std::size_t h2 = std::hash<T2>()(pair.second);
        return h1 ^ h2;
    }
};

typedef std::pair<int, int> position;

void move(position& pos, char direction) {
    switch (direction) {
        case '>': {
            ++pos.first;
            break;
        }
        case '<': {
            --pos.first;
            break;
        }
        case '^': {
            ++pos.second;
            break;
        }
        case 'v': {
            --pos.second;
            break;
        }
    }
}

int delivery(const char* path) {
    if (!path) return 0;

    std::unordered_set<position, pair_hash> houses;

    // start pos   X  Y
    position santa(0, 0);
    position robot(0, 0);

    houses.insert(santa);
    houses.insert(robot);

    while (*path) {
        move(santa, *path++);
        houses.insert(santa);

        if (*path) {
            move(robot, *path++);
            houses.insert(robot);
        }
    }

    return houses.size();
}

void tests() {
    assert(delivery(nullptr) == 0);
    assert(delivery("") == 1);
    assert(delivery("^v") == 3);
    assert(delivery("^>v<") == 3);
    assert(delivery("^v^v^v^v^v") == 11);
}

int main() {
    tests();

    for (std::string line; std::getline(std::cin, line);) {
        std::cout << delivery(line.c_str()) << '\n';
    }

    return 0;
}
