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
        // Event handling
        handleEvent();

        // Update
        update();

        // Rendering
        draw();
    }
}

void Game::init()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    _grid = Grid();

    _blocks = {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};

    _currentBlock = getRandomBlock();
    _nextBlock = getRandomBlock();
}

void Game::update()
{
    if (triggerEvent(0.8))
    {
        moveBlockDown();
    }
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(DARKBLUE);

    _grid.draw();
    _currentBlock.draw();

    EndDrawing();
}

void Game::handleEvent()
{
    int key = GetKeyPressed();
    switch (key)
    {
    case KEY_LEFT:
        moveBlockLeft();
        break;
    
    case KEY_RIGHT:
        moveBlockRight();
        break;

    case KEY_DOWN:
        moveBlockDown();
        break;

    case KEY_UP:
        rotateBlock();
        break;

    case KEY_ESCAPE:
        CloseWindow();
        break;    
    
    default:
        break;
    }
}

void Game::cleanup()
{
    CloseWindow();
}

bool Game::isBlockOutOfBounds()
{
    std::vector<Position> blockCells = _currentBlock.getCellPositions();
    for (Position item : blockCells)
    {
        if (_grid.isOutside(item.x, item.y))
            return true;
    }
    return false;
}

Block Game::getRandomBlock()
{
    if (_blocks.empty())
    {
        _blocks = {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
    }
    int randIndex = rand() % _blocks.size();
    Block block = _blocks[randIndex];
    _blocks.erase(_blocks.begin() + randIndex);
    return block;
}

bool Game::triggerEvent(double interval)
{
    double currentTime = GetTime();
    if (currentTime - _lastUpdateTime >= interval)
    {
        _lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

void Game::lockBlock()
{
    std::vector<Position> blockCells = _currentBlock.getCellPositions();
    for (Position item : blockCells)
    {
        _grid.grid[item.y][item.x] = _currentBlock.id;
    }
    _currentBlock = _nextBlock;
    _nextBlock = getRandomBlock();
}

void Game::moveBlockLeft()
{
    _currentBlock.move(-1, 0);
    if (isBlockOutOfBounds())
        _currentBlock.move(1, 0);
}

void Game::moveBlockRight()
{
    _currentBlock.move(1, 0);
    if (isBlockOutOfBounds())
        _currentBlock.move(-1, 0);
}

void Game::moveBlockDown()
{
    _currentBlock.move(0, 1);
    if (isBlockOutOfBounds())
    {
        _currentBlock.move(0, -1);
        lockBlock();
    }
}

void Game::rotateBlock()
{
    _currentBlock.rotate();

    std::vector<Position> blockCells = _currentBlock.getCellPositions();
    
    int offsetX = 0;
    int offsetY = 0;

    // Vérifiez les limites pour toutes les cellules du bloc
    for (Position item : blockCells)
    {
        if (item.x < 0)
            offsetX = std::max(offsetX, 0 - item.x);
        else if (item.x >= _grid.numCols)
            offsetX = std::min(offsetX, _grid.numCols - 1 - item.x);

        if (item.y >= _grid.numRows)
            offsetY = std::min(offsetY, _grid.numRows - 1 - item.y);
    }

    // Appliquez le déplacement pour corriger la position du bloc
    _currentBlock.move(offsetX, offsetY);
}
