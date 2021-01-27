/* Your code here! */
#include <vector>
#include <map>

#include "cs225/PNG.h"
#include "dsets.h"

using namespace cs225;
using namespace std;

class SquareMaze {
    public:
        SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        vector<int> solveMaze();
        PNG* drawMaze() const;
        PNG* drawMazeWithSolution();
        PNG* drawCreativeMaze() const;
    private:
        int _width;
        int _height;
        vector<bool> no_right_wall;
        vector<bool> no_down_wall;
        void dfs(int idx, vector<bool>& visited, vector<int>& steps, map<size_t, vector<int>>& paths);
};
