#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <vector>
#include <random>

#include "grid/grid.h"
#include "block/block.h"
#include "block/blocks.cpp"

#define SCREEN_WIDTH (500)
#define SCREEN_HEIGHT (620)
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
    void reset();

    bool isBlockOutOfBounds();
    Block getRandomBlock();
    bool triggerEvent(double interval);
    void lockBlock();
    bool blockFits();
    bool isGameOver();
    void showGameOver();

    void moveBlockLeft();
    void moveBlockRight();
    void moveBlockDown();
    void rotateBlock();

    Grid _grid;
    std::vector<Block> _blocks;
    Block _currentBlock;
    Block _nextBlock;
    bool _gameOver;

    double _lastUpdateTime = 0;
};

#endif // GAME_H