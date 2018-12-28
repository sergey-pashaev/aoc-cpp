// Day 7, Part Two

// Now, take the signal you got on wire a, override wire b to that
// signal, and reset the other wires (including wire a). What new
// signal is ultimately provided to wire a?

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

int main() {
    Wires wires{};
    for (std::string line; std::getline(std::cin, line);) {
        auto tokens = parse(line);
        std::string w = tokens.back().second.s;
        tokens.pop_back();  // remove output wire token

        // -1 is undefined value of wire
        wires[w] = std::make_pair(-1, tokens);
    }

    uint16_t a = eval("a", wires);

    for (auto& kv : wires) {
        // invalidate cached values
        kv.second.first = -1;

        // reset all signals
        auto& tokens = kv.second.second;
        if (tokens.size() == 1 && tokens[0].first == TokenType::NUMBER) {
            tokens[0].second.n = 0;
        }
    }

    // override b to a
    wires["b"].second[0].second.n = a;

    std::cout << eval("a", wires) << '\n';

    return 0;
}
