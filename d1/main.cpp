#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace solution {
struct Input {
    std::vector<int> list1;
    std::vector<int> list2;
};

std::vector<int> diff(Input input) {
    std::vector<int> result;
    std::sort(input.list1.begin(), input.list1.end());
    std::sort(input.list2.begin(), input.list2.end());

    for (int i = 0; i < input.list1.size(); i++) {
        result.push_back(std::abs(input.list1[i] - input.list2[i]));
    }
    return result;
}

int similarity(Input input) {
    std::unordered_map<int, int> hash_map;
    for (int i = 0; i < input.list1.size(); i++) {
        hash_map[input.list1[i]]++;
    }

    int similarity = 0;

    for (int i = 0; i < input.list2.size(); i++) {
        similarity += input.list2[i] * hash_map[input.list2[i]];
    }

    return similarity;
}

std::vector<std::string> split(const std::string &s,
                               const std::string &delimiter) {
    std::string copy = s;
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = copy.find(delimiter)) != std::string::npos) {
        token = copy.substr(0, pos);
        tokens.push_back(token);
        copy.erase(0, pos + delimiter.length());
    }
    tokens.push_back(copy);

    return tokens;
}

Input parse_input() {
    Input input;

    std::ifstream file("input.txt");
    std::string line;
    std::string delimiter = "   ";
    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, delimiter);
        input.list1.push_back(std::stoi(tokens[0]));
        input.list2.push_back(std::stoi(tokens[1]));
    }

    return input;
}
} // namespace solution

int main() {
    solution::Input input = solution::parse_input();
    std::vector<int> result = solution::diff(input);
    int sum = 0;
    for (int i = 0; i < result.size(); i++) {
        sum += result[i];
    }
    std::cout << "Part 1 answer: " << sum << std::endl;
    std::cout << "Part 2 answer: " << solution::similarity(input) << std::endl;

    return 0;
}
