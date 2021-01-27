#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    //cout << "Add your own tests here! Modify main.cpp" << endl;
    SquareMaze m;
    m.makeMaze(103, 103);
    PNG* creative = m.drawCreativeMaze();
    creative -> writeToFile("creative.png");
    delete creative;
    return 0;
}
