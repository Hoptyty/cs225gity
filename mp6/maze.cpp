/* Your code here! */
#include <stack>
#include <numeric>
#include <random>

#include "maze.h"

SquareMaze::SquareMaze() {
}

void SquareMaze::makeMaze(int width, int height) {
    _width = width;
    _height = height;
    DisjointSets cells;
    cells.addelements(_width * _height);
    no_right_wall.assign(_width * _height, false);
    no_down_wall.assign(_width * _height, false);
    vector<int> remove_order(2 * _width * _height);
    std::iota(remove_order.begin(), remove_order.end(), 0);
    std::shuffle(remove_order.begin(), remove_order.end(), std::mt19937{std::random_device{}()}); 
    int count = 0;
    size_t i = 0;
    while (count < _width * _height - 1) {
        int idx = remove_order[i] % (_width * _height);
        int dir = remove_order[i] / (_width * _height);
        int x = idx % _width;
        int y = idx / _width;
        if (dir == 0) {
            if (x != _width - 1 && cells.find(idx) != cells.find(idx + 1)) {
                setWall(x, y, 0, 0); 
                cells.setunion(idx, idx + 1);
                count++;
            }
        }
        else {
            if (y != _height - 1 && cells.find(idx) != cells.find(idx + _width)) {
                setWall(x, y, 1, 0);
                cells.setunion(idx, idx + _width);
                count++;
            }
        }
        i++;
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    switch (dir) {
        case 0:
            if (x >= _width - 1)
                return false;
            return no_right_wall[y * _width + x];
        case 1:
            if (y >= _height - 1)
                return false;
            return no_down_wall[y * _width + x];
        case 2:
            if (x <= 0)
                return false;
            return no_right_wall[y * _width + x - 1];
        case 3:
            if (y <= 0)
                return false;
            return no_down_wall[(y - 1) * _width + x];
    }
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if (x < 0 || y < 0 || x > _width - 1 || y > _height - 1)
        return;
    switch (dir) {
        case 0:
            no_right_wall[y * _width + x] = (x == _width - 1) ? false : !exists;
            break;
        case 1:
            no_down_wall[y * _width + x] = (y == _height - 1) ? false : !exists;
            break;
    }
}

vector<int> SquareMaze::solveMaze() {
    vector<int> steps;
    map<size_t, vector<int>> paths;
    vector<bool> visited(_width * _height, false);
    dfs(0, visited, steps, paths);
    return paths.rbegin() -> second;
}

PNG* SquareMaze::drawMaze() const {
    PNG* maze = new PNG(_width * 10 + 1, _height * 10 + 1);
    HSLAPixel black(0, 0, 0, 1);
    for (int y = 0; y < _height * 10 + 1; y++) {
        HSLAPixel& pixel = maze -> getPixel(0, y);
        pixel = black;
    }
    for (int x = 10; x < _width * 10 + 1; x++) {
        HSLAPixel& pixel = maze -> getPixel(x, 0);
        pixel = black;
    }
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            int idx = y * _width + x;
            if (!no_right_wall[idx]) {
                for (int k = 0; k <= 10; k++) {
                    HSLAPixel& pixel = maze -> getPixel((x + 1) * 10, y * 10 + k);
                    pixel = black;
                }
            }
            if (!no_down_wall[idx]) {
                for (int k = 0; k <= 10; k++) {
                    HSLAPixel& pixel = maze -> getPixel(x * 10 + k, (y + 1) * 10);
                    pixel = black;
                }
            }
        }
    }
    return maze;
}

PNG* SquareMaze::drawMazeWithSolution() {
    PNG* maze_solution = drawMaze();
    vector<int> solution = solveMaze();
    HSLAPixel red(0, 1, 0.5, 1);
    HSLAPixel white(1, 1, 1, 1);
    int x = 5;
    int y = 5;
    HSLAPixel& pixel = maze_solution -> getPixel(x, y);
    pixel = red;
    for (size_t i = 0; i < solution.size(); i++) {
        switch (solution[i]) {
            case 0:
                for (int k = 0; k < 10; k++) {
                    x++;
                    HSLAPixel& pixel = maze_solution -> getPixel(x, y);
                    pixel = red;
                }
                break;
            case 1:
                for (int k = 0; k < 10; k++) {
                    y++;
                    HSLAPixel& pixel = maze_solution -> getPixel(x, y);
                    pixel = red;
                }
                break;
            case 2:
                for (int k = 0; k < 10; k++) {
                    x--;
                    HSLAPixel& pixel = maze_solution -> getPixel(x, y);
                    pixel = red;
                }
                break;
            case 3:
                for (int k = 0; k < 10; k++) {
                    y--;
                    HSLAPixel& pixel = maze_solution -> getPixel(x, y);
                    pixel = red;
                }
                break;
        }
    }
    x -= 5;
    y += 5;
    for (int k = 1; k < 10; k++) {
        HSLAPixel& pixel = maze_solution -> getPixel(x + k, y);
        pixel = white;
    }
    return maze_solution;
}

PNG* SquareMaze::drawCreativeMaze() const {
    PNG* creative_maze = drawMaze();
    PNG logo; 
    logo.readFromFile("adidas.png");
    logo.resize(_width * 10 + 1, _height * 10 + 1);
    HSLAPixel white(1, 1, 1, 1);
    for (int y = 0; y < _height * 10 + 1; y++) {
        for (int x = 0; x < _width * 10 + 1; x++) {
            HSLAPixel& p1 = creative_maze -> getPixel(x, y);
            HSLAPixel& p2 = logo.getPixel(x, y);
            if (p2.a == 0)
                p1 = white;
        }
    }
    return creative_maze;
}

void SquareMaze::dfs(int idx, vector<bool>& visited, vector<int>& steps, map<size_t, vector<int>>& paths) {
    visited[idx] = true;
    int x = idx % _width;
    int y = idx / _width;
    if (y == _height - 1) {
        size_t dist = steps.size();
        paths[dist] = steps;
    }
    if (canTravel(x, y, 0) && !visited[idx + 1]) {
        steps.push_back(0);
        dfs(idx + 1, visited, steps, paths);
        steps.pop_back();
    }
    if (canTravel(x, y, 1) && !visited[idx + _width]) {
        steps.push_back(1);
        dfs(idx + _width, visited, steps, paths);
        steps.pop_back();
    }
    if (canTravel(x, y, 2) && !visited[idx - 1]) {
        steps.push_back(2);
        dfs(idx - 1, visited, steps, paths);
        steps.pop_back();
    }
    if (canTravel(x, y, 3) && !visited[idx - _width]) {
        steps.push_back(3);
        dfs(idx - _width, visited, steps, paths);
        steps.pop_back();
    } 
}
