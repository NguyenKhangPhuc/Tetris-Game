#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
private:
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
    bool IsFullRow(int row);
    void ClearFullRow(int row);
    void MoveRowDown(int row, int numOfRowDown);

public:
    int grid[20][10];
    Grid();
    void Initialize();
    void print_grid();
    void Draw();
    bool IsCellOut(int row, int col);
    bool IsCellCollision(int row);
    bool IsEmptyCell(int row, int column);
    int CheckFullRow();
};