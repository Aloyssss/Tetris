#include "game.h"

Game::Game()
{
    init();
}

Game::~Game()
{
    cleanup();
}

void Game::run()
{
    while (!WindowShouldClose())
    {
        // Rendering
        BeginDrawing();
        ClearBackground(DARKBLUE);
        _grid.draw();
        EndDrawing();
    }
}

void Game::init()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    _blocks = {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::update()
{
}

void Game::draw()
{
}

void Game::handleEvent()
{
}

void Game::cleanup()
{
    CloseWindow();
}

Block Game::getRandomBlock()
{
    Block block = _blocks[rand() % _blocks.size()];
    _blocks.erase(_blocks.begin());
    return block;
}
