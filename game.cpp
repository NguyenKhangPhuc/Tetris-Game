#include <game.h>
#include <vector>
#include <random>

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
}

Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks()
{
    return {LBlock(), IBlock(), JBlock(), OBlock(), ZBlock(), SBlock(), TBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw();
}

void Game::handleInput()
{
    int keyPressed = GetKeyPressed();
    switch (keyPressed)
    {
    case KEY_LEFT:
        MoveLeft();
        break;

    case KEY_RIGHT:
        MoveRight();
        break;
    case KEY_DOWN:
        MoveDown();
        break;
    case KEY_UP:
        RotateBlock();
        break;
    }
}

void Game::MoveLeft()
{
    currentBlock.Move(0, -1);
    if (IsBlockOut() == true || ValidBlock() == false)
    {
        currentBlock.Move(0, 1);
    }
}

void Game::MoveRight()
{
    currentBlock.Move(0, 1);
    if (IsBlockOut() == true || ValidBlock() == false)
    {
        currentBlock.Move(0, -1);
    }
}

void Game::MoveDown()
{
    currentBlock.Move(1, 0);
    if (IsBlockOut() == true || ValidBlock() == false)
    {
        currentBlock.Move(-1, 0);
        LockBlock();
    }
}

bool Game::IsBlockOut()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for (Position item : tiles)
    {
        if (grid.IsCellOut(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    currentBlock.Rotate();
    if (IsBlockOut())
    {
        currentBlock.UndoRotate();
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    nextBlock = GetRandomBlock();
    grid.CheckFullRow();
}

bool Game::ValidBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for (Position item : tiles)
    {
        if (grid.IsEmptyCell(item.row, item.column) == false)
        {
            return false;
        }
    }
    return true;
}