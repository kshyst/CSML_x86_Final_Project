#include "raylib.h"
#include <iostream>

class Ball{
public:
    float x , y;
    float speed_x , speed_y;
    float radius;
    Image image;
    Texture2D texture;

    void SetBall(int x , int y , float speed_x , float speed_y , float radius){
        this->x = x;
        this->y = y;
        this->speed_x = speed_x;
        this->speed_y = speed_y;
        this->radius = radius;

        texture = LoadTexture("resources/ball.png"); // Convert image to texture
    }

    void Draw(){
        DrawTexture(texture, x, y, WHITE);
    }

    void Update(){
        x += speed_x;
        y += speed_y;

        if(y +  radius >= GetScreenHeight() || y - radius <= 0){
            speed_y *= - 1;
        }
        if(x +  radius >= GetScreenWidth() || x - radius <= 0){
            speed_x *= - 1;
        }
        
    }
};


class Paddle {
public:
    float x , y , width , height , speed;

    void SetPaddle(float x , float y , float width , float height , float speed){
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->speed = speed;
    }

    void Draw(){
        DrawRectangle(x , y , width , height , BLUE);
    }

    void Update(){
        if(IsKeyDown(KEY_W)){
            y = y - speed;
        }
        if(IsKeyDown(KEY_S)){
            y = y + speed;
        }
    }
};


class CPUPaddle: public Paddle{
    public:

    void Update(float ball_y){
        if(y + height / 2 > ball_y){
            y -= speed;
        }
        if(y + height / 2 <= ball_y){
            y += speed;
        }
    }
};


Ball ball;
Paddle player;
CPUPaddle cpu;

int main() {
    const int screen_width = 1280;
    const int screen_height = 720;
    const int target_fps = 144;

    InitWindow(screen_width , screen_height , "My Pong Game");
    SetTargetFPS(target_fps);

    ball.SetBall(screen_width / 2 , screen_height / 2 , 2 , 2 , 20);
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