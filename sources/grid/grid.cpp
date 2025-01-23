#include "grid.h"

Grid::Grid()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;

    initialize();
    colors = getCellColors();
}

void Grid::initialize()
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            grid[i][j] = 0;
        }
    }
}

void Grid::print()
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::draw()
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            DrawRectangle(j * cellSize + 1, i * cellSize + 1, cellSize - 1, cellSize - 1, colors[grid[i][j]]);
        }
    }
}

bool Grid::isOutside(int x, int y)
{
    if (x >= 0 && x < numCols && y >= 0 && y < numRows)
        return false;
    else
        return true;
}
