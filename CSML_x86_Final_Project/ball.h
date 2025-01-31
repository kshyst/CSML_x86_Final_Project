#include <raylib.h>
#include <math.h> 

#pragma once
class Ball {
public:
    float x, y;
    float speed_x, speed_y;
    float radius;
    Image image;
    Texture2D texture;
    int ballSpeedMode = 0;
    float time = 0.0f; // Time variable for sinusoidal and curve motion

    void SetBall(int x, int y, float speed_x, float speed_y, float radius) {
        this->x = x;
        this->y = y;
        this->speed_x = speed_x;
        this->speed_y = speed_y;
        this->radius = radius;

        texture = LoadTexture("resources/ball.png"); // Convert image to texture
    }

    void Draw() {
        DrawTexture(texture, x, y, WHITE);
    }

    void Update() {
        BallStart();

        switch (ballSpeedMode) {
            case 0:
                // Linear motion
                x += speed_x;
                y += speed_y;
                break;
            case 1:
                // Sinusoidal motion
                time += GetFrameTime(); // Increment time based on frame time
                x += speed_x;
                y += sinf(time * 2.0f) * speed_y; // Oscillate y position using sine wave
                break;
            case 2:
                // Quadratic curve motion
                time += GetFrameTime(); // Increment time based on frame time
                time = fminf(time, 10.0f); // Clamp time to a maximum value (e.g., 10 seconds)
                x += speed_x;
                y += speed_y * time * time * 0.1f; // Quadratic curve for y position
                break;
            default:
                break;
        }

        // Boundary collision detection
        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth() || x - radius <= 0) {
            speed_x *= -1;
        }
    }

    void BallStart() {
        if (IsKeyPressed(KEY_Z) || IsKeyPressed(KEY_X) || IsKeyPressed(KEY_C))
        {
            if (IsKeyPressed(KEY_Z)) {
                ballSpeedMode = 1;
            } else if (IsKeyPressed(KEY_X)) {
                ballSpeedMode = 2;
            } else if (IsKeyPressed(KEY_C)) {
                ballSpeedMode = 0;
            }

            if (speed_x == 0 || speed_y == 0)
            {
                speed_x = 2;
                speed_y = 2;
            }
            
            time = 0.0f; // Reset time when changing mode
        }
    }
};