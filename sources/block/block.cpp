#include "block.h"

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = getCellColors();
    x = 0;
    y = 0;
}

void Block::draw()
{
    std::vector<Position> blockCells = getCellPositions();
    for (int i = 0; i < blockCells.size(); i++)
    {
        int x = blockCells[i].x;
        int y = blockCells[i].y;
        DrawRectangle(x * cellSize + 1, y * cellSize + 1, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::move(int x_offset, int y_offset)
{
    x += x_offset;
    y += y_offset;


}

std::vector<Position> Block::getCellPositions()
{
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> positions;
    for (Position item : tiles)
    {
        positions.push_back({item.x + x, item.y + y});
    }
    return positions;
}
