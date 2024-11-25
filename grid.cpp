#include <grid.h>
#include <iostream>
#include <colors.h>

Grid::Grid()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();
}

void Grid::Initialize()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            grid[row][col] = 0;
        }
    }
}

void Grid::print_grid()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::Draw()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            int cellValue = grid[row][col];
            DrawRectangle(col * cellSize + 1, row * cellSize + 1, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}

bool Grid::IsCellOut(int row, int col)
{
    if (row >= 0 && row < numRows && col >= 0 && col < numCols)
    {
        return false;
    }
    return true;
}

bool Grid::IsCellCollision(int row)
{
    if (row == numRows - 1)
    {
        return true;
    }
    return false;
}

bool Grid::IsEmptyCell(int row, int column)
{
    if (grid[row][column] != 0)
    {
        return false;
    }
    return true;
}

void Grid::CheckFullRow()
{
    int completedRow = 0;
    for (int row = numRows - 1; row > 0; row--)
    {
        if (IsFullRow(row))
        {
            ClearFullRow(row);
            completedRow++;
        }
        else if (completedRow > 0)
        {
            MoveRowDown(row, completedRow);
        }
    }
}

bool Grid::IsFullRow(int row)
{
    for (int col = 0; col < numCols; col++)
    {
        if (grid[row][col] == 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::ClearFullRow(int row)
{
    for (int col = 0; col < numCols; col++)
    {
        grid[row][col] = 0;
    }
}

void Grid::MoveRowDown(int row, int numOfRowDown)
{
    for (int col = 0; col < numCols; col++)
    {
        grid[row + numOfRowDown][col] = grid[row][col];
        grid[row][col] = 0;
    }
}
