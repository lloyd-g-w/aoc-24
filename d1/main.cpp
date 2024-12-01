#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
  public:
    struct Input {
        std::vector<int> list1;
        std::vector<int> list2;
    };

    Input input;

    Solution() {
        std::string line;
        while (std::getline(std::cin, line)) {
            int a, b;
            std::istringstream iss(line);
            iss >> a >> b;
            input.list1.push_back(a);
            input.list2.push_back(b);
        }
    }

    int diff_sum() {
        std::vector<int> result;
        std::sort(input.list1.begin(), input.list1.end());
        std::sort(input.list2.begin(), input.list2.end());

        for (int i = 0; i < input.list1.size(); i++) {
            result.push_back(std::abs(input.list1[i] - input.list2[i]));
        }

        int sum = 0;
        for (int i = 0; i < result.size(); i++) {
            sum += result[i];
        }
        return sum;
    }

    int similarity() {
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
};

int main() {
    Solution solution;
    std::cout << "Part 1 answer: " << solution.diff_sum() << std::endl;
    std::cout << "Part 2 answer: " << solution.similarity() << std::endl;

    return 0;
}
