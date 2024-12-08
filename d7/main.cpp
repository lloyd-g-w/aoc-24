#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <vector>

namespace SolutionSpace {
using namespace std;

class Solution {
  public:
    Solution() {
        string line;

        while (std::getline(std::cin, line)) {
            istringstream iss(line);
            Equation eq;
            vector<int> numbers;

            string temp_num;

            int c;
            while (iss >> c && c != ':') {
                temp_num.push_back(c);
            }

            eq.result = stoi(temp_num);

            while (iss >> c && c != ' ') {
                temp_num.clear();
                temp_num.push_back(c);
            }
        }
    }

    int part_one() {
        int res = 0;
        return res;
    }

    int part_two(void) {
        int res = 0;
        return res;
    }

  private:
    struct Equation {
        int result;
        vector<int> numbers;
    };
    typedef vector<int> vInt;
    typedef vector<string> vString;

    vector<Equation> equations;
};

} // namespace SolutionSpace

int main(void) {
    SolutionSpace::Solution solution;
    std::cout << "Part 1 answer: " << solution.part_one() << std::endl;
    std::cout << "Part 2 answer: " << solution.part_two() << std::endl;
    return EXIT_SUCCESS;
}
