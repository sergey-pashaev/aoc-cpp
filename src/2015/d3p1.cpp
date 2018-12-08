// Day 3, Part One

// Santa is delivering presents to an infinite two-dimensional grid of
// houses.

// He begins by delivering a present to the house at his starting
// location, and then an elf at the North Pole calls him via radio and
// tells him where to move next. Moves are always exactly one house to
// the north (^), south (v), east (>), or west (<). After each move,
// he delivers another present to the house at his new location.

// However, the elf back at the north pole has had a little too much
// eggnog, and so his directions are a little off, and Santa ends up
// visiting some houses more than once. How many houses receive at
// least one present?

// For example:

// > delivers presents to 2 houses: one at the starting location, and
// > one to the east.

// ^>v< delivers presents to 4 houses in a square, including twice to
// the house at his starting/ending location.

// ^v^v^v^v^v delivers a bunch of presents to some very lucky children
// at only 2 houses.

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

    houses.insert(santa);

    while (*path) {
        const char direction = *path++;
        move(santa, direction);
        houses.insert(santa);
    }

    return houses.size();
}

void tests() {
    assert(delivery(nullptr) == 0);
    assert(delivery("") == 1);
    assert(delivery(">") == 2);
    assert(delivery("^>v<") == 4);
    assert(delivery("^v^v^v^v^v") == 2);
}

int main() {
    tests();

    for (std::string line; std::getline(std::cin, line);) {
        std::cout << delivery(line.c_str()) << '\n';
    }

    return 0;
}
