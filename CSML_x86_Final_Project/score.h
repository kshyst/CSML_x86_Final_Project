#include "raylib.h"
#include "ball.h"

class Score
{
public:
    int userScore = 0;
    int opponentScore = 0;

    void Update(Ball& ball) { // Pass Ball by reference
        if (ball.x + ball.radius >= GetScreenWidth()) {
            userScore += 1;
            ResetBall(ball);
        }
        else if (ball.x - ball.radius <= 0) {
            opponentScore += 1;
            ResetBall(ball);
        }
    }

    void Draw() {
        // User score on the left side in blue
        DrawText(TextFormat("User: %d", userScore), 50, 20, 30, BLUE);
        
        // Opponent score on the right side in red
        DrawText(TextFormat("Opponent: %d", opponentScore), GetScreenWidth() - 250, 20, 30, RED);
    }


    void ResetBall(Ball& ball) { // Pass Ball by reference
        ball.x = GetScreenWidth() / 2 - 300;
        ball.y = GetScreenHeight() / 2;
        ball.speed_x = 0;
        ball.speed_y = 0;
    }
};