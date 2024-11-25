#include <iostream>
#include <raylib.h>
#include <game.h>
#include <colors.h>
#include <string>
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
    InitWindow(500, 620, "Tetris");
    SetTargetFPS(60);
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Game game;

    while (WindowShouldClose() == false)
    {
        UpdateMusicStream(game.music);
        BeginDrawing();
        ClearBackground(darkBlue);
        if (EventTriggered(0.2) == true)
        {
            game.MoveDown();
        }
        DrawTextEx(font, "Score", {380, 15}, 20, 2, WHITE);
        DrawTextEx(font, "Next", {380, 175}, 20, 2, WHITE);
        if (game.gameOver)
        {
            DrawTextEx(font, "GAME OVER", {350, 450}, 20, 2, WHITE);
        }
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 20, 2);

        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 75}, 20, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
        game.Draw();
        game.handleInput();
        EndDrawing();
    }

    CloseWindow();
}