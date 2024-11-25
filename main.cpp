#include <iostream>
#include <raylib.h>
#include <game.h>
using namespace std;

double lastUpdatedTime = 0;

bool EventTriggered(double interval)
{
    double currrentTime = GetTime();
    if (currrentTime - lastUpdatedTime >= interval)
    {
        lastUpdatedTime = currrentTime;
        return true;
    }
    return false;
}

int main()
{
    Color darkBlue = {44, 44, 127, 255};
    InitWindow(300, 600, "Tetris");
    SetTargetFPS(60);
    Game game;

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(darkBlue);
        game.Draw();
        if (EventTriggered(0.2) == true)
        {
            game.MoveDown();
        }
        game.handleInput();
        EndDrawing();
    }

    CloseWindow();
}