#include <iostream>
#include <sstream>
#include <vector>

class Solution {
  private:
    enum Monotonicity { INCREASING, DECREASING, NON_MONOTONIC };

    typedef struct Input {
        std::vector<std::vector<int>> reports;
    } Input_t;

    bool is_valid_adjacent(int a, int b) {
        int diff = std::abs(a - b);
        if (diff >= 1 && diff <= 3) {
            return true;
        }
        return false;
    }

    bool is_increasing(int a, int b) {
        int diff = a - b;
        if (diff < 0) {
            return true;
        }
        return false;
    }

    bool is_decreasing(int a, int b) {
        int diff = a - b;
        if (diff > 0) {
            return true;
        }
        return false;
    }

    Monotonicity determine_monotonicity(int a, int b) {
        int diff = a - b;
        if (diff < 0) {
            return INCREASING;
        } else if (diff > 0) {
            return DECREASING;
        }
        return NON_MONOTONIC;
    }

    bool is_safe_level(std::vector<int> &level, int &unsafe_pos) {
        int first = level[0], second = level[1];

        if (!is_valid_adjacent(first, second)) {
            unsafe_pos = 0;
            return false;
        }

        Monotonicity monotonicity = determine_monotonicity(first, second);
        if (monotonicity == NON_MONOTONIC) {
            unsafe_pos = 0;
            return false;
        }

        for (size_t j = 1; j < level.size() - 1; j++) {
            if (!is_valid_adjacent(level[j], level[j + 1])) {
                unsafe_pos = j;
                return false;
            }

            if ((monotonicity == INCREASING &&
                 !is_increasing(level[j], level[j + 1])) ||
                (monotonicity == DECREASING &&
                 !is_decreasing(level[j], level[j + 1]))) {
                unsafe_pos = j;
                return false;
            }
        }

        return true;
    }

  public:
    Input input;

    Solution() {
        std::string line;
        while (std::getline(std::cin, line)) {
            std::istringstream iss(line);
            std::vector<int> tmp;
            int a;
            while (iss >> a) {
                tmp.push_back(a);
            }
            input.reports.push_back(tmp);
        }
    }

    int num_safe_reports() {
        int count = 0;

        for (auto &level : input.reports) {
            int unsafe_pos;
            if (is_safe_level(level, unsafe_pos)) {
                count++;
            }
        }

        return count;
    }

    int num_safe_reports_dampener() {
        int count = 0;

        for (auto &level : input.reports) {
            int unsafe_pos;
            if (is_safe_level(level, unsafe_pos)) {
                count++;
                continue;
            }

            std::vector<int> unsafe_pos_removed = level;
            std::vector<int> adj_unsafe_pos_removed = level;
            std::vector<int> first_pos_removed;
            unsafe_pos_removed.erase(unsafe_pos_removed.begin() + unsafe_pos);
            adj_unsafe_pos_removed.erase(adj_unsafe_pos_removed.begin() +
                                         unsafe_pos + 1);

            int tmp;
            if (unsafe_pos == 1) {
                first_pos_removed = level;
                first_pos_removed.erase(first_pos_removed.begin());
                if (is_safe_level(first_pos_removed, tmp)) {
                    count++;
                    continue;
                }
            }

            if (is_safe_level(unsafe_pos_removed, tmp) ||
                is_safe_level(adj_unsafe_pos_removed, tmp)) {
                count++;
                continue;
            }
        }

        return count;
    }

    int num_safe_reports_dampener_brute_force() {
        int count = 0;

        for (auto &level : input.reports) {
            int unsafe_pos;
            if (is_safe_level(level, unsafe_pos)) {
                count++;
                continue;
            }

            for (size_t i = 0; i < level.size(); i++) {
                std::vector<int> one_removed = level;
                one_removed.erase(one_removed.begin() + i);
                int tmp;
                if (is_safe_level(one_removed, tmp)) {
                    count++;
                    break;
                }
            }
        }

        return count;
    }
};

int main(void) {
    Solution solution{};
    std::cout << "Part 1 answer: " << solution.num_safe_reports() << std::endl;
    std::cout << "Part 2 answer without brute force: "
              << solution.num_safe_reports_dampener() << std::endl;
    std::cout << "Part 2 answer using brute force: "
              << solution.num_safe_reports_dampener_brute_force() << std::endl;
    return 0;
}
