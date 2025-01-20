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

    Block getRandomBlock();

    Grid _grid;
    std::vector<Block> _blocks;
};

#endif // GAME_H