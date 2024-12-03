#include <iostream>
#include <vector>

typedef std::string str;
typedef std::vector<int> vInt;
struct mul_data_t {
    bool valid;
    int start;
    int end;
    int a, b;
};

class Solution {
  private:
    const int MAX_DIGITS = 3;
    const int MUL_OFFSET = 4;
    const int DO_OFFSET = 4;
    const int DONT_OFFSET = 7;

    std::string text;
    mul_data_t get_mul_data(int &pos, str &text) {
        int start_pos = pos + MUL_OFFSET;
        int curr_pos = start_pos;

        mul_data_t mul_data = {true, pos, -1, -1, -1};

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

        int search_pos = 0;
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

        int search_pos = 0;
        while ((search_pos = text.find(mul_sub, search_pos)) !=
               std::string::npos) {
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
};

int main(void) {
    Solution solution{};
    std::cout << "Part 1 answer: " << solution.mul_sum() << std::endl;
}
