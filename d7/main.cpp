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
#define ll long long

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
            ll num;

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

    ll part_one() {
        ll res = 0;

        for (const auto &eq : equations) {
            res += get_true_test_val(eq);
        }

        return res;
    }

    ll part_two(void) {
        ll res = 0;

        for (const auto &eq : equations) {
            res += get_true_test_val_with_concat(eq);
        }

        return res;
    }

  private:
    struct Equation {
        ll result;
        vector<ll> numbers;
    };
    enum Operation { ADD, MUL, CONCAT };
    typedef vector<int> vInt;
    typedef vector<string> vString;

    vector<Equation> equations;

    ll get_true_test_val(const Equation &eq) {
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

    ll evaluate_exp(const Equation &eq, const vector<Operation> &operations) {
        ll res = eq.numbers[0];
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

    ll concat_op(ll a, ll b) {
        ll multiplier = 1;
        while (multiplier <= b) {
            multiplier *= 10;
        }

        return a * multiplier + b;
    }

    ll get_true_test_val_with_concat(const Equation &eq) {
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
