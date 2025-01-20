#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <raylib.h>
#include <vector>
#include "colors.h"

class Grid
{
public:
    Grid();

    void initialize();
    void print();
    void draw();

    int grid[20][10];

private:
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;

};

#endif // GRID_H