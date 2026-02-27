#include "raylib.h"
#include <stdio.h>

#define WINDOW_X 1000
#define WINDOW_Y 700
#define FPS 60

#define RECT_WIDTH 50
#define RECT_HEIGHT 50

#define GRAVITY 9.81f
#define THRUST_POWER 25.0f
#define VEL_MAX 20.0f
#define GOAL (WINDOW_X/2+RECT_WIDTH/2,WINDOW_Y/2+RECT_HEIGHT/2)

void ApplyThrust(float *vel_x, float *vel_y, float *desire) {
    *vel_x -= (THRUST_POWER * desire[0]) / FPS;
    *vel_y -= (THRUST_POWER * desire[1]) / FPS; 
}
void DrawFlame(float x, float y) {
    Vector2 p1 = { x + 15, y+50 };
    Vector2 p2 = { x + 25, y + 80 };
    Vector2 p3 = { x + 35, y+50 };
    
    DrawTriangle(p1, p2, p3, ORANGE);
}

int main(){
    InitWindow(WINDOW_X, WINDOW_Y, "Test");
    SetTargetFPS(FPS);

    float rect_x = 450;
    float rect_y = 600;
    float vel_x = 0;
    float vel_y = 0;
    float bounce = 0.5f;
    float desire[2]={1,1};

    while (!WindowShouldClose()){
        vel_y += GRAVITY / FPS;
        bool isThrusting = false;
        if (IsKeyDown(KEY_UP)) {
            desire[0]=0;
            desire[1]=1;
            ApplyThrust(&vel_x,&vel_y,desire);
            isThrusting = true;
        }
        if (IsKeyDown(KEY_LEFT)) {
            desire[0]=1;
            desire[1]=0;
            ApplyThrust(&vel_x,&vel_y,desire);
            isThrusting = true;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            desire[0]=-1;
            desire[1]=0;
            ApplyThrust(&vel_x,&vel_y,desire);
            isThrusting = true;
        }
        rect_y += vel_y;
        rect_x += vel_x;
        if (rect_y > WINDOW_Y - RECT_HEIGHT){
            rect_y = WINDOW_Y - RECT_HEIGHT;
            vel_y = -vel_y * bounce;
            if (vel_y > -0.3 && vel_y < 0.3) vel_y = 0; 
        }
        else if (rect_y <=0){
            rect_y = 0;
            vel_y = -vel_y * bounce;
            if (vel_y > -0.3 && vel_y < 0.3) vel_y = 0; 
        }
        
        if (rect_x <= 0){
            rect_x = 0;
            vel_x = -vel_x * bounce;
            if (vel_x > -0.3 && vel_x < 0.3) vel_x = 0; 
        }
        else if (rect_x >= WINDOW_X-RECT_WIDTH){
            rect_x = WINDOW_X-RECT_WIDTH;
            vel_x = -vel_x * bounce;
            if (vel_x > -0.3 && vel_x < 0.3) vel_x = 0; 
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(rect_x, rect_y, RECT_WIDTH, RECT_HEIGHT, DARKBLUE);
        if (isThrusting) {
            DrawFlame(rect_x, rect_y);
            DrawText("Thrusting!", 400,10,20,DARKPURPLE);
        }
        DrawText("Hold SPACE to Fly!", 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("Velocity: %.2f", -vel_y), 10, 40, 20, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}