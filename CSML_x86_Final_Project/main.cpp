#include "raylib.h"
#include <iostream>
#include "ball.h"
#include "paddle.h"


Ball ball;
Paddle player;
CPUPaddle cpu;

int main() {
    const int screen_width = 1280;
    const int screen_height = 720;
    const int target_fps = 144;

    InitWindow(screen_width , screen_height , "My Pong Game");
    SetTargetFPS(target_fps);

    ball.SetBall(screen_width / 2 - 300 , screen_height / 2 , 0 , 0 , 20);
    player.SetPaddle(10 , screen_height / 2 - 60 , 25 , 120 , 5);
    cpu.SetPaddle(screen_width - 35 , screen_height / 2 , 25 , 120 , 1);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        
        //Updating
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        //Check for collisions
        if(CheckCollisionCircleRec(Vector2{ball.x , ball.y} , ball.radius , Rectangle{player.x , player.y , player.width , player.height})){
            ball.speed_x *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x , ball.y} , ball.radius , Rectangle{cpu.x , cpu.y , cpu.width , cpu.height})){
            ball.speed_x *= -1;
        }
 
        //Draw the ball
        ClearBackground(BLACK);
        ball.Draw();
        player.Draw();
        cpu.Draw();

        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}