#include <algorithm>
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
        while (getline(cin, line)) {
            string temp_line = line;
            Equation eq;

            // Remove ':'
            int pos = temp_line.find(':');
            temp_line.erase(pos, 1);

            istringstream iss(temp_line);
            long num;

            // Get result
            iss >> num;
            eq.result = num;

            // Get numbers
            while (iss >> num) {
                eq.numbers.push_back(num);
            }

            equations.push_back(eq);
        }
    }

    long part_one() {
        long res = 0;

        for (const auto &eq : equations) {
            res += get_true_test_val(eq);
        }

        return res;
    }

    long part_two(void) {
        long res = 0;

        for (const auto &eq : equations) {
            res += get_true_test_val_with_concat(eq);
        }

        return res;
    }

  private:
    struct Equation {
        long result;
        vector<long> numbers;
    };
    enum Operation { ADD, MUL, CONCAT };
    typedef vector<int> vInt;
    typedef vector<string> vString;

    vector<Equation> equations;

    long get_true_test_val(const Equation &eq) {
        for (int num_muls = 0; num_muls < (int)eq.numbers.size(); num_muls++) {
            vector<Operation> operations(eq.numbers.size() - 1, ADD);

            for (int i = 0; i < num_muls; i++) {
                operations[operations.size() - 1 - i] = MUL;
            }

            do {

                if (evaluate_exp(eq, operations) == eq.result) {
                    return eq.result;
                }
            } while (next_permutation(operations.begin(), operations.end()));
        }

        return 0;
    }

    long evaluate_exp(const Equation &eq, const vector<Operation> &operations) {
        long res = eq.numbers[0];
        for (int i = 0; i < (int)operations.size(); i++) {
            if (operations[i] == ADD) {
                res += eq.numbers[i + 1];
            } else if (operations[i] == MUL) {
                res *= eq.numbers[i + 1];
            } else {
                res = concat_op(res, eq.numbers[i + 1]);
            }
        }

        return res;
    }

    long concat_op(int a, int b) {
        int num_digits = log10(b) + 1;
        return a * pow(10, num_digits) + b;
    }

    long get_true_test_val_with_concat(const Equation &eq) {
        for (int num_muls = 0; num_muls < (int)eq.numbers.size(); num_muls++) {
            for (int num_concats = 0;
                 num_concats < (int)eq.numbers.size() - num_muls;
                 num_concats++) {

                vector<Operation> operations(eq.numbers.size() - 1, ADD);

                for (int i = 0; i < num_concats; i++) {
                    operations[operations.size() - 1 - i] = CONCAT;
                }

                for (int i = 0; i < num_muls; i++) {
                    operations[operations.size() - 1 - num_concats - i] = MUL;
                }

                do {

                    if (evaluate_exp(eq, operations) == eq.result) {
                        return eq.result;
                    }
                } while (
                    next_permutation(operations.begin(), operations.end()));
            }
        }

        return 0;
    }
};

} // namespace SolutionSpace

int main(void) {
    SolutionSpace::Solution solution;
    std::cout << "Part 1 answer: " << solution.part_one() << std::endl;
    std::cout << "Part 2 answer: " << solution.part_two() << std::endl;
    return EXIT_SUCCESS;
}
