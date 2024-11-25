#pragma once
#include <map>
#include <vector>
#include <position.h>
#include <colors.h>

class Block
{
private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
    int rowOffset;
    int colOffset;

public:
    Block();
    void Draw();
    int id;
    std::map<int, std::vector<Position>> cells;
    void Move(int r, int n);
    std::vector<Position> GetCellPosition();
    void Rotate();
    void UndoRotate();
};