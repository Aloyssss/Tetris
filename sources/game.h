#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <vector>
#include <random>

#include "grid/grid.h"
#include "block/block.h"
#include "block/blocks.cpp"

#define SCREEN_WIDTH (300)
#define SCREEN_HEIGHT (600)
#define WINDOW_TITLE "Tetris"

class Game
{
public:
    Game();
    ~Game();

    void run();
private:
    void init();
    void update();
    void draw();
    void handleEvent();
    void cleanup();

    bool isBlockOutOfBounds();
    Block getRandomBlock();
    bool triggerEvent(double interval);
    void lockBlock();

    void moveBlockLeft();
    void moveBlockRight();
    void moveBlockDown();
    void rotateBlock();

    Grid _grid;
    std::vector<Block> _blocks;
    Block _currentBlock;
    Block _nextBlock;

    double _lastUpdateTime = 0;
};

#endif // GAME_H