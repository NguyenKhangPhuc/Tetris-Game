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
    void MoveLeft();
    void MoveRight();
    void Reset();
    void updateScore(int linesCleared, int movedownPoints);
    bool IsBlockOut();
    Grid grid;
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    Sound rotateSound;
    Sound clearSound;

public:
    Game();
    ~Game();
    void Draw();
    void handleInput();
    void MoveDown();
    bool gameOver;
    int score;
    Music music;
};