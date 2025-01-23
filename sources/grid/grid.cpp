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

bool Grid::isCellEmpty(int x, int y)
{
    if (grid[y][x] == 0)
        return true;
    return false;
}

bool Grid::isColumnFull(int x)
{
    for (int i = 0; i < numRows; i++)
    {
        if (grid[i][x] == 0)
            return false;
    }
    return true;
}

bool Grid::isRowFull(int y)
{
    for (int i = 0; i < numCols; i++)
    {
        if (grid[y][i] == 0)
            return false;
    }
    return true;
}

void Grid::clearRow(int y)
{
    for (int x = 0; x < numCols; x++)
    {
        grid[y][x] = 0;
    }
}

void Grid::moveRowDown(int y, int numRows)
{
    for (int x = 0; x < numCols; x++)
    {
        grid[y + numRows][x] = grid[y][x];
        grid[y][x] = 0;
    }
}

int Grid::clearFullRows()
{
    int clearedRows = 0;
    for (int i = numRows - 1; i >= 0; i--)
    {
        if (isRowFull(i))
        {
            clearRow(i);
            clearedRows++;
        }
        else if (clearedRows > 0)
        {
            moveRowDown(i, clearedRows);
        } 
    }
    return clearedRows;
}
