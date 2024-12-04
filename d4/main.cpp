#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <vector>

typedef std::vector<int> vInt;
typedef std::string string;
typedef std::vector<string> vString;

class Solution {
  public:
    Solution() {
        std::string line;
        while (std::getline(std::cin, line)) {
            input.push_back(line);
        }
    }

    int part_one() {
        const string xmas = "XMAS";
        const string rev_xmas = "SAMX";

        int res = 0;

        res += find_count_vert(input, xmas);
        res += find_count_vert(input, rev_xmas);

        res += find_count_right_diag(input, xmas);
        res += find_count_right_diag(input, rev_xmas);

        res += find_count_left_diag(input, xmas);
        res += find_count_left_diag(input, rev_xmas);

        return res;
    }

    int part_two() {
        const string mas = "MAS";
        return find_count_x_mas(input, mas);
    }

  private:
    vString input;
    const ulong NPOS = std::string::npos;

    int find_count_hoz(const vString &text, const string &str) {
        int res = 0;

        for (auto line : text) {
            int pos = -1;
            while ((pos = line.find(str, pos + 1)) != (int)NPOS) {
                res++;
            }
        }

        return res;
    }

    int find_count_vert(const vString &text, const string &str) {
        int res = 0;

        for (size_t i = 0; i <= text.size() - str.size(); i++) {
            for (size_t j = 0; j < text.at(i).size(); j++) {
                string s;

                for (size_t k = 0; k < str.size(); k++) {
                    s.push_back((text.at(i + k)).at(j));
                }

                if (s == str) {
                    res++;
                }
            }
        }

        return res;
    }

    int find_count_right_diag(const vString &text, const string &str) {
        int res = 0;

        for (size_t i = 0; i <= text.size() - str.size(); i++) {
            for (size_t j = 0; j <= text.at(i).size() - str.size(); j++) {
                string s;

                for (size_t k = 0; k < str.size(); k++) {
                    s.push_back((text.at(i + k)).at(j + k));
                }

                if (s == str) {
                    res++;
                }
            }
        }

        return res;
    }

    int find_count_left_diag(const vString &text, const string &str) {
        int res = 0;

        for (size_t i = 0; i <= text.size() - str.size(); i++) {
            for (size_t j = text.at(i).size() - 1; j >= str.size() - 1; j--) {
                string s;

                for (size_t k = 0; k < str.size(); k++) {
                    s.push_back((text.at(i + k)).at(j - k));
                }

                if (s == str) {
                    res++;
                }
            }
        }

        return res;
    }

    int find_count_x_mas(const vString &text, const string &str) {
        string rev_str = str;
        std::reverse(rev_str.begin(), rev_str.end());
        int res = 0;

        for (size_t i = 0; i <= text.size() - str.size(); i++) {
            for (size_t j = 0; j <= text.at(i).size() - str.size(); j++) {
                string s1;
                string s2;

                // Right diag
                for (size_t k = 0; k < str.size(); k++) {
                    s1.push_back((text.at(i + k)).at(j + k));
                }

                // Left diag
                for (size_t k = 0; k < str.size(); k++) {
                    s2.push_back((text.at(i + k)).at((j + str.size() - 1) - k));
                }

                if ((s1 == str || s1 == rev_str) &&
                    (s2 == str || s2 == rev_str)) {
                    res++;
                }
            }
        }

        return res;
    }
};

int main(void) {
    Solution solution{};
    std::cout << "Part 1 answer: " << solution.part_one() << std::endl;
    std::cout << "Part 2 answer: " << solution.part_two() << std::endl;
}
