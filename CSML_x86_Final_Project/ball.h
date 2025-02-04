#include <raylib.h>
#include <math.h> 
#pragma once
extern "C" void linear_motion(float* x, float* speed_x, float* y, float* speed_y);
extern "C" void sinus_motion(float* time, float* x, float* speed_x, float* y, float* speed_y);

class Ball {
public:
    float x, y;
    float speed_x, speed_y;
    float radius;
    Image image;
    Texture2D texture;
    int ballSpeedMode = 0;
    float time = 0.0f;
    float rotation = 1;

    void SetBall(int x, int y, float speed_x, float speed_y, float radius) {
        this->x = x;
        this->y = y;
        this->speed_x = speed_x;
        this->speed_y = speed_y;
        this->radius = radius / 2;

        texture = LoadTexture("resources/ball.png");
    }

    void Draw() {
        Vector2 origin = { radius, radius };
        Rectangle destRec = { x, y, radius * 2, radius * 2 };
        Rectangle sourceRec = { 0, 0, (float)texture.width, (float)texture.height };
        DrawTexturePro(texture, sourceRec, destRec, origin, rotation, WHITE);
    }

    void Update() {
        BallStart();

        switch (ballSpeedMode) {
            case 0:
                // Linear motion using assembly
                linear_motion(&x, &speed_x, &y, &speed_y);
                break;
            case 1:
                // Sinus motion with assembly
                time += GetFrameTime();
                sinus_motion(&time, &x, &speed_x, &y, &speed_y);
                break;
            case 2:
                x += speed_x;
                y += speed_y;
                speed_y += 0.05f;

                if (y - radius <= 0) {
                    y = radius;
                    speed_y *= -1;
                }
                if (x + radius >= GetScreenWidth() || x - radius <= 0) {
                    speed_x *= -1;
                    x = fmaxf(radius, fminf(x, GetScreenWidth() - radius));
                }
                break;
            default:
                break;
        }

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
            rotation *= -1;
        }
        if (x + radius >= GetScreenWidth() || x - radius <= 0) {
            speed_x *= -1;
            rotation *= -1;
        }

        rotation += sqrtf(speed_x * speed_x + speed_y * speed_y) * GetFrameTime() * 50.0f;
        if (rotation > 360.0f) {
            rotation -= 360.0f;
        }
    }

    void BallStart() {
        if (IsKeyPressed(KEY_Z) || IsKeyPressed(KEY_X) || IsKeyPressed(KEY_C)) {
            if (IsKeyPressed(KEY_Z)) {
                ballSpeedMode = 1;
            } 
            else if (IsKeyPressed(KEY_X)) {
                ballSpeedMode = 2;
            } 
            else if (IsKeyPressed(KEY_C)) {
                ballSpeedMode = 0;
            }

            if (speed_x == 0 || speed_y == 0) {
                speed_x = 2;
                speed_y = 2;
            }

            time = 0.0f;
        }
    }
};
