#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <unordered_map>
#include <vector>

class Solution {
  public:
    Solution() {
        std::string line;

        while (std::getline(std::cin, line)) {
            if (line.empty()) {
                break;
            }
            std::istringstream iss(line);
            string page;

            std::getline(iss, page, '|');
            int x = std::stoi(page);
            std::getline(iss, page, '|');
            int y = std::stoi(page);

            rule_map[x].push_back(y);
        }

        while (std::getline(std::cin, line)) {
            vInt update;

            std::istringstream iss(line);
            string page;
            while (std::getline(iss, page, ',')) {
                update.push_back(std::stoi(page));
            }

            updates.push_back(update);
        }
    }

    int part_one() {
        int res = 0;

        for (auto update : updates) {
            bool valid = true;
            for (size_t i = 0; i < update.size(); i++) {
                if (!is_valid_page_pos(update, i)) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                res += update.at(std::floor((update.size() / 2)));
            }
        }

        return res;
    }

    int part_two() {
        int res = 0;

        for (auto update : updates) {
            bool valid = true;
            for (size_t i = 0; i < update.size(); i++) {
                if (!is_valid_page_pos(update, i)) {
                    valid = false;
                    break;
                }
            }

            if (!valid) {
                std::sort(update.begin(), update.end(),
                          [this](int a, int b) { return compare_page(a, b); });

                res += update.at(std::floor((update.size() / 2)));
            }
        }
        return res;
    }

  private:
    typedef std::string string;
    typedef std::vector<int> vInt;
    typedef std::vector<string> vString;

    typedef std::vector<vInt> vUpdate;

    std::unordered_map<int, vInt> rule_map;
    vUpdate updates;

    bool is_valid_page_pos(vInt update, size_t pos) {
        int page = update.at(pos);
        for (auto rule : rule_map[page]) {
            for (size_t i = 0; i < update.size(); i++) {
                if (update.at(i) == rule && pos > i) {
                    return false;
                }
            }
        }

        return true;
    }

    bool compare_page(int a, int b) {
        bool b_in_front = false;
        for (auto num : rule_map[a]) {
            if (num == b) {
                b_in_front = true;
                break;
            }
        }

        return b_in_front;
    }
};

int main(void) {
    Solution solution{};
    std::cout << "Part 1 answer: " << solution.part_one() << std::endl;
    std::cout << "Part 2 answer: " << solution.part_two() << std::endl;
}
