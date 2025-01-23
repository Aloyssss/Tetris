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

    void print();
    void draw();
    bool isOutside(int x, int y);

    int grid[20][10];
    int numRows;
    int numCols;

private:
    void initialize();

    int cellSize;
    std::vector<Color> colors;

};

#endif // GRID_H