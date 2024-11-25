#pragma once
#include <grid.h>
#include <blocks.cpp>
#include <vector>

class Game
{
private:
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    void RotateBlock();
    void LockBlock();
    bool ValidBlock();

public:
    Game();
    Grid grid;
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    void Draw();
    void handleInput();
    void MoveLeft();
    void MoveRight();
    void MoveDown();
    bool IsBlockOut();
};