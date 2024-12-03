#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

typedef std::string str;
typedef std::vector<int> vInt;
struct mul_data_t {
    bool valid;
    size_t start;
    size_t end;
    int a, b;
};

struct interval {
    int a, b;
};

class Solution {
  private:
    const int MAX_DIGITS = 3;
    const int MUL_OFFSET = 4;
    const int DO_OFFSET = 4;
    const int DONT_OFFSET = 7;

    std::string text;
    mul_data_t get_mul_data(size_t &pos, str &text) {
        int start_pos = pos + MUL_OFFSET;
        int curr_pos = start_pos;

        mul_data_t mul_data = {true, pos, pos, -1, -1};

        while (std::isdigit(text.at(curr_pos))) {
            if (curr_pos - start_pos > MAX_DIGITS) {
                mul_data.valid = false;
                break;
            }
            curr_pos++;
        }

        if (!mul_data.valid || text.at(curr_pos) != ',') {
            mul_data.valid = false;
            return mul_data;
        }

        mul_data.a = std::stoi(text.substr(start_pos, curr_pos - 1));
        curr_pos++;

        start_pos = curr_pos;

        while (std::isdigit(text.at(curr_pos))) {
            if (curr_pos - start_pos > MAX_DIGITS) {
                mul_data.valid = false;
                break;
            }
            curr_pos++;
        }

        if (!mul_data.valid || text.at(curr_pos) != ')') {
            mul_data.valid = false;
            return mul_data;
        }

        mul_data.b = std::stoi(text.substr(start_pos, curr_pos - 1));
        mul_data.end = curr_pos;

        return mul_data;
    }

  public:
    Solution() {
        char c;
        while (std::cin >> c) {
            text.push_back(c);
        }
    }

    int mul_sum() {
        const str sub = "mul(";
        int res = 0;

        size_t search_pos = 0;
        while ((search_pos = text.find(sub, search_pos)) != std::string::npos) {
            mul_data_t mul_data;
            mul_data = get_mul_data(search_pos, text);
            if (mul_data.valid) {
                res += mul_data.a * mul_data.b;
                search_pos = mul_data.end + 1;
            } else {
                search_pos++;
            }
        }

        return res;
    }

    int mul_sum_cond() {
        const str mul_sub = "mul(";
        const str do_sub = "do()";
        const str dont_sub = "don't()";
        int res = 0;

        size_t search_pos = 0;
        size_t dont_pos = 0;
        size_t do_pos = 0;
        size_t count = 0;

        while ((search_pos = text.find(mul_sub, search_pos)) !=
               std::string::npos) {

            // Update the position of the next don't
            // if search pos is after the last do
            while (search_pos >= do_pos) {
                dont_pos = text.find(dont_sub, dont_pos);
                if (dont_pos == std::string::npos) {
                    dont_pos = INT_MAX;
                } else {
                    dont_pos += DONT_OFFSET;
                }

                // If dont() is after do() then we need the next do()
                while (dont_pos >= do_pos && do_pos != INT_MAX) {
                    do_pos = text.find(do_sub, do_pos);
                    if (do_pos == std::string::npos) {
                        do_pos = INT_MAX;
                    } else {
                        do_pos += DO_OFFSET;
                    }
                }

                count++;
            }

            mul_data_t mul_data;
            mul_data = get_mul_data(search_pos, text);
            if (mul_data.valid &&
                !(search_pos >= dont_pos && search_pos < do_pos)) {
                res += mul_data.a * mul_data.b;
                search_pos = mul_data.end + 1;
            } else {
                search_pos++;
            }
        }

        return res;
    }
};

int main(void) {
    Solution solution{};
    std::cout << "Part 1 answer: " << solution.mul_sum() << std::endl;
    std::cout << "Part 2 answer: " << solution.mul_sum_cond() << std::endl;
}
