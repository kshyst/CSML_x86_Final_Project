#include <raylib.h>

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

    void Draw(){
        DrawRectangle(x , y , width , height , RED);
    }
};