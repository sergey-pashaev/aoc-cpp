// Day 7, Part One

// This year, Santa brought little Bobby Tables a set of wires and
// bitwise logic gates! Unfortunately, little Bobby is a little under
// the recommended age range, and he needs help assembling the
// circuit.

// Each wire has an identifier (some lowercase letters) and can carry
// a 16-bit signal (a number from 0 to 65535). A signal is provided to
// each wire by a gate, another wire, or some specific value. Each
// wire can only get a signal from one source, but can provide its
// signal to multiple destinations. A gate provides no signal until
// all of its inputs have a signal.

// The included instructions booklet describes how to connect the
// parts together: x AND y -> z means to connect wires x and y to an
// AND gate, and then connect its output to wire z.

// For example:

// 123 -> x means that the signal 123 is provided to wire x.

// x AND y -> z means that the bitwise AND of wire x and wire y is
// provided to wire z.

// p LSHIFT 2 -> q means that the value from wire p is left-shifted by
// 2 and then provided to wire q.

// NOT e -> f means that the bitwise complement of the value from wire
// e is provided to wire f.

// Other possible gates include OR (bitwise OR) and RSHIFT
// (right-shift). If, for some reason, you'd like to emulate the
// circuit instead, almost all programming languages (for example, C,
// JavaScript, or Python) provide operators for these gates.

// For example, here is a simple circuit:

// 123 -> x
// 456 -> y
// x AND y -> d
// x OR y -> e
// x LSHIFT 2 -> f
// y RSHIFT 2 -> g
// NOT x -> h
// NOT y -> i

// After it is run, these are the signals on the wires:

// d: 72
// e: 507
// f: 492
// g: 114
// h: 65412
// i: 65079
// x: 123
// y: 456

// In little Bobby's kit's instructions booklet (provided as your
// puzzle input), what signal is ultimately provided to wire a?

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct Operand {
    enum Gate : char { NONE, AND, OR, LSHIFT, RSHIFT, NOT };
    Gate op;        // operation
    uint16_t n;     // number
    std::string s;  // wire name
};

enum TokenType : char { NUMBER, WIRE, OPERATION };
typedef std::pair<TokenType, Operand> Token;

std::vector<Token> parse(const std::string& s) {
    std::istringstream ss(s);
    std::vector<Token> tokens;
    for (std::string token; std::getline(ss, token, ' ');) {
        const char c = token[0];
        if (std::isdigit(c)) {
            // number token
            tokens.emplace_back(
                TokenType::NUMBER,
                Operand{Operand::NONE, static_cast<uint16_t>(std::stoi(token)),
                        ""});
        } else if ('a' <= c && c <= 'z') {
            // wire name token
            tokens.emplace_back(TokenType::WIRE,
                                Operand{Operand::NONE, 0, token});
        } else if ('A' <= c && c <= 'Z') {
            // operation token
            Operand o{};
            if (token == "AND") {
                o.op = Operand::AND;
            } else if (token == "OR") {
                o.op = Operand::OR;
            } else if (token == "LSHIFT") {
                o.op = Operand::LSHIFT;
            } else if (token == "RSHIFT") {
                o.op = Operand::RSHIFT;
            } else if (token == "NOT") {
                o.op = Operand::NOT;
            }

            tokens.emplace_back(TokenType::OPERATION, o);
        }
    }

    return tokens;
}

// map wire name -> <current value, token> pair
typedef std::unordered_map<std::string, std::pair<int, std::vector<Token>>>
    Wires;

uint16_t eval(const std::string& wire, Wires& wires) {
    // evaluate signal for wire only once
    int v = wires[wire].first;
    if (v != -1) return v;

    const auto& tokens = wires[wire].second;

    // SIGNAL or WIRE
    if (tokens.size() == 1) {
        uint16_t v = 0;
        if (tokens[0].first == TokenType::NUMBER) {
            v = tokens[0].second.n;
        } else if (tokens[0].first == TokenType::WIRE) {
            v = eval(tokens[0].second.s, wires);
        }

        // cache wire's value
        wires[wire].first = v;
        return v;
    }

    // NOT
    if (tokens.size() == 2 && tokens[0].first == TokenType::OPERATION) {
        uint16_t v = ~eval(tokens[1].second.s, wires);
        // cache wire's value
        wires[wire].first = v;
        return v;
    }

    // other gates
    if (tokens.size() == 3 && tokens[1].first == TokenType::OPERATION) {
        Operand::Gate op = tokens[1].second.op;

        uint16_t v1 = 0;
        if (tokens[0].first == TokenType::NUMBER) {
            v1 = tokens[0].second.n;
        } else if (tokens[0].first == TokenType::WIRE) {
            v1 = eval(tokens[0].second.s, wires);
        }

        uint16_t v2 = 0;
        if (tokens[2].first == TokenType::NUMBER) {
            v2 = tokens[2].second.n;
        } else if (tokens[2].first == TokenType::WIRE) {
            v2 = eval(tokens[2].second.s, wires);
        }

        uint16_t v = 0;
        if (op == Operand::AND) {
            v = v1 & v2;
        } else if (op == Operand::OR) {
            v = v1 | v2;
        } else if (op == Operand::LSHIFT) {
            v = v1 << v2;
        } else if (op == Operand::RSHIFT) {
            v = v1 >> v2;
        }

        // cache wire's value
        wires[wire].first = v;
        return v;
    }

    return 0;
}

int usage(const char* bin) {
    std::cout << "Usage: " << bin << " <wire name to evaluate>\n";
    return 1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return usage(argv[0]);
    }

    if (!std::isalpha(argv[1][0])) {
        return usage(argv[0]);
    }

    Wires wires{};
    for (std::string line; std::getline(std::cin, line);) {
        auto tokens = parse(line);
        std::string w = tokens.back().second.s;
        tokens.pop_back();  // remove output wire token

        // -1 is undefined value of wire
        wires[w] = std::make_pair(-1, tokens);
    }

    std::cout << eval(argv[1], wires) << '\n';

    return 0;
}
