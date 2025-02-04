#include "raylib.h"
#include <iostream>
#include "ball.h"
#include "paddle.h"
#include "score.h"


Ball ball;
Paddle player;
CPUPaddle cpu;
Score score;

int main() {
    const int screen_width = 1280;
    const int screen_height = 720;
    const int target_fps = 144;

    InitWindow(screen_width , screen_height , "My Pong Game");
    SetTargetFPS(target_fps);

    ball.SetBall(screen_width / 2 - 300 , screen_height / 2 , 0 , 0 , 20);
    player.SetPaddle(30 , screen_height / 2 - 60 , 25 , 120 , 5);
    cpu.SetPaddle(screen_width - 55 , screen_height / 2 , 25 , 120 , 3);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        
        //Updating
        ball.Update();
        player.Update();
        cpu.Update(ball.y);
        score.Update(ball);

        std::cout << ball.y << "\n";
        std::cout << ball.x << "\n";

        //Check for collisions
        if(CheckCollisionCircleRec(Vector2{ball.x , ball.y} , ball.radius , Rectangle{player.x , player.y , player.width , player.height})){
            ball.speed_x *= -1;
            ball.rotation *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x , ball.y} , ball.radius , Rectangle{cpu.x , cpu.y , cpu.width , cpu.height})){
            ball.speed_x *= -1;
            ball.rotation *= -1;
        }
 
        //Draw the ball
        ClearBackground(BLACK);
        ball.Draw();
        player.Draw();
        cpu.Draw();
        score.Draw();

        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}