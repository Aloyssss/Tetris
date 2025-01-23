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
    _gameOver = false;
}

void Game::update()
{
    if (triggerEvent(0.6))
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

    if (_gameOver)
        showGameOver();

    EndDrawing();
}

void Game::handleEvent()
{
    int key = GetKeyPressed();

    if (_gameOver && key == KEY_SPACE)
    {
        init();
    }

    // move block
    if (!_gameOver)
    {
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
        }
    }
    
    if (key == KEY_ESCAPE)
        CloseWindow();
}

void Game::cleanup()
{
    CloseWindow();
}

void Game::reset()
{
    _grid = Grid();
    _blocks = {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
    _currentBlock = getRandomBlock();
    _nextBlock = getRandomBlock();
    _gameOver = false;
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
    if (!blockFits())
    {
        _gameOver = true;
    }

    _nextBlock = getRandomBlock();
    _grid.clearFullRows();
}

bool Game::blockFits()
{
    std::vector<Position> blockCells = _currentBlock.getCellPositions();
    for (Position item : blockCells)
    {
        if (!_grid.isCellEmpty(item.x, item.y))
            return false;
    }
    return true;
}

bool Game::isGameOver()
{
    for (int i = 0; i < 10; i++)
    {
        if (_grid.isColumnFull(i))
            return true;
    }
}

void Game::showGameOver()
{
    if (_gameOver)
    {
        DrawText("Game Over!", SCREEN_WIDTH/4, SCREEN_HEIGHT/2, 30, BLACK);
    }
}

void Game::moveBlockLeft()
{
    _currentBlock.move(-1, 0);
    if (isBlockOutOfBounds() || !blockFits())
        _currentBlock.move(1, 0);
}

void Game::moveBlockRight()
{
    _currentBlock.move(1, 0);
    if (isBlockOutOfBounds() || !blockFits())
        _currentBlock.move(-1, 0);
}

void Game::moveBlockDown()
{
    _currentBlock.move(0, 1);
    if (isBlockOutOfBounds() || !blockFits())
    {
        _currentBlock.move(0, -1);
        lockBlock();
    }
}

void Game::rotateBlock()
{
    _currentBlock.rotate();

    std::vector<Position> blockCells = _currentBlock.getCellPositions();

    for (Position item : blockCells)
    {
        if (!blockFits())
        {
            _currentBlock.rotate();
            _currentBlock.rotate();
            _currentBlock.rotate();
        }
    }
    
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
