#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <vector>

namespace SolutionSpace {
enum Direction { UP, DOWN, LEFT, RIGHT };
enum Tile { EMPTY, BARRIER, PLAYER, VISITED };
enum Method { BRUTE, OPTIMISED };
struct Point {
    int row;
    int col;
};
struct Player {
    Point pos;
    Direction dir;
};

using namespace std;
class Solution {
  public:
    Solution() {
        string line;

        while (std::getline(std::cin, line)) {
            istringstream iss(line);
            vector<Tile> row;

            char c;
            while (iss >> c) {
                if (c == '.') {
                    row.push_back(EMPTY);
                } else if (c == '#') {
                    row.push_back(BARRIER);
                } else {
                    row.push_back(PLAYER);
                    player.pos = {static_cast<int>(map.size() + 1),
                                  static_cast<int>(row.size()) - 1};
                    player.dir = get_player_dir(c);
                }
            }

            map.push_back(row);
        }
    }

    int part_one() {
        int res = 0;
        vector<vector<Tile>> map = this->map;
        Player player = this->player;

        while (point_in_map(player.pos)) {
            int row = player.pos.row;
            int col = player.pos.col;

            if (map[row][col] == BARRIER) {
                turn_player(player);
            } else {
                if (!(map[row][col] == VISITED)) {
                    map[row][col] = VISITED;
                    res++;
                }
            }
            move_player_forwards(player);
        }

        return res;
    }

    int part_two(Method method) {
        if (method == BRUTE) {
            return part_two_brute();
        } else {
            return part_two_optimised();
        }
    }

  private:
    typedef vector<int> vInt;
    typedef vector<string> vString;

    vector<vector<Tile>> map;
    Player player;

    Direction get_player_dir(char c) {
        switch (c) {
        case '^':
            return UP;
        case 'v':
            return DOWN;
        case '<':
            return LEFT;
        case '>':
            return RIGHT;
        default:
            return UP;
        }
    }

    bool point_in_map(Point p) {
        int x = p.row;
        int y = p.col;
        return x >= 0 && x < static_cast<int>(map.size()) && y >= 0 &&
               y < static_cast<int>(map[0].size());
    }

    void turn_player(Player &player) {
        switch (player.dir) {
        case UP:
            player.pos.row++;
            player.dir = RIGHT;
            break;
        case DOWN:
            player.pos.row--;
            player.dir = LEFT;
            break;
        case LEFT:
            player.pos.col++;
            player.dir = UP;
            break;
        case RIGHT:
            player.pos.col--;
            player.dir = DOWN;
            break;
        default:
            break;
        }
    }

    void move_player_forwards(Player &player) {
        switch (player.dir) {
        case UP:
            player.pos.row--;
            break;
        case DOWN:
            player.pos.row++;
            break;
        case LEFT:
            player.pos.col--;
            break;
        case RIGHT:
            player.pos.col++;
            break;
        default:
            break;
        }
    }

    bool part_two_is_infinite_loop() {
        int res = 0;
        vector<vector<Tile>> map = this->map;
        Player player = this->player;

        while (point_in_map(player.pos)) {
            int row = player.pos.row;
            int col = player.pos.col;

            if (map[row][col] == BARRIER) {
                turn_player(player);
            } else {
                res++;
            }

            if (res == 10000) {
                return true;
            }

            move_player_forwards(player);
        }

        return false;
    }

    // oh my brute force
    int part_two_brute() {
        int res = 0;

        for (int i = 0; i < static_cast<int>(map.size()); i++) {
            for (int j = 0; j < static_cast<int>(map[i].size()); j++) {

                if (map[i][j] == BARRIER || map[i][j] == PLAYER) {
                    continue;
                } else {
                    Tile tmp = map[i][j];
                    map[i][j] = BARRIER;
                    if (part_two_is_infinite_loop()) {
                        res++;
                    }
                    map[i][j] = tmp;
                }
            }
        }

        return res;
    }

    int part_two_optimised() {
        int res = 0;
        vector<vector<Tile>> map = this->map;
        Player player = this->player;

        while (point_in_map(player.pos)) {
            int row = player.pos.row;
            int col = player.pos.col;

            if (map[row][col] == BARRIER) {
                turn_player(player);
            } else {
                if (!(map[row][col] == VISITED)) {
                    map[row][col] = VISITED;
                    res++;
                }
            }
            move_player_forwards(player);
        }

        return res;
    }
};

} // namespace SolutionSpace

int main(void) {
    SolutionSpace::Solution solution;
    std::cout << "Part 1 answer: " << solution.part_one() << std::endl;
    std::cout << "Part 2 brute force answer: "
              << solution.part_two(SolutionSpace::BRUTE) << std::endl;
    std::cout << "Part 2 optimised answer: "
              << solution.part_two(SolutionSpace::OPTIMISED) << std::endl;
    return EXIT_SUCCESS;
}
