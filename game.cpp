#include <game.h>
#include <vector>
#include <random>

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("Sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
}

Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
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
    currentBlock.Draw(0, 0);
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(245, 280);
        break;
    case 4:
        nextBlock.Draw(245, 270);
        break;
    default:
        nextBlock.Draw(260, 260);
        break;
    }
}

void Game::handleInput()
{
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0)
    {
        gameOver = false;
        Reset();
    }
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
        updateScore(0, 1);
        break;
    case KEY_UP:
        RotateBlock();
        break;
    }
}

void Game::MoveLeft()
{
    if (gameOver == false)
    {
        currentBlock.Move(0, -1);
        if (IsBlockOut() == true || ValidBlock() == false)
        {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveRight()
{
    if (gameOver == false)
    {
        currentBlock.Move(0, 1);
        if (IsBlockOut() == true || ValidBlock() == false)
        {
            currentBlock.Move(0, -1);
        }
    }
}

void Game::MoveDown()
{
    if (gameOver == false)
    {
        currentBlock.Move(1, 0);
        if (IsBlockOut() == true || ValidBlock() == false)
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
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

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::RotateBlock()
{
    if (gameOver == false)
    {
        currentBlock.Rotate();
        if (IsBlockOut())
        {
            currentBlock.UndoRotate();
        }
        else
        {
            PlaySound(rotateSound);
        }
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
    if (ValidBlock() == false)
    {
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowCleared = grid.CheckFullRow();
    if (rowCleared > 0)
    {
        PlaySound(clearSound);
    }
    updateScore(rowCleared, 0);
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

void Game::updateScore(int linesCleared, int movedownPoints)
{
    switch (linesCleared)
    {
    case 1:
        score += 100;
    case 2:
        score += 300;
    case 3:
        score += 500;
    default:
        break;
    }
    score += movedownPoints;
}
