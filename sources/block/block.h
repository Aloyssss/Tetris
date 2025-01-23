#ifndef BLOCK_H
#define BLOCK_H

#include "colors.h"

#include <vector>
#include <map>

class Position
{
public:
    Position(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    int x, y;
};

class Block
{
public:
    Block();
    void draw();
    void move(int x, int y);
    void rotate();
    std::vector<Position> getCellPositions();

    int id;
    std::map<int, std::vector<Position>> cells;
private:


    int cellSize;
    int rotationState;
    std::vector<Color> colors;

    int x, y;
};

#endif // BLOCK_H