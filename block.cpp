#include <block.h>
#include <vector>
Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    colOffset = 0;
}

void Block::Draw(int offsetX, int offsetY)
{
    std::vector<Position> tiles = GetCellPosition();
    for (Position item : tiles)
    {
        DrawRectangle(item.column * cellSize + 11 + offsetX, item.row * cellSize + 11 + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::Move(int r, int n)
{
    rowOffset += r;
    colOffset += n;
}

std::vector<Position> Block::GetCellPosition()
{
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;
    for (Position item : tiles)
    {
        Position newPos(item.row + rowOffset, item.column + colOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Block::Rotate()
{
    rotationState++;
    if (rotationState == cells.size())
    {
        rotationState = 0;
    }
}

void Block::UndoRotate()
{
    rotationState--;
}
