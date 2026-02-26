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

void ApplyThrust(float *vel) {
    *vel -= THRUST_POWER / FPS; 
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
    float vel = 0;
    float bounce = 0.5f; 

    while (!WindowShouldClose()){
        vel += GRAVITY / FPS;
        bool isThrusting = false;
        if (IsKeyDown(KEY_SPACE)) {
            ApplyThrust(&vel);
            isThrusting = true;
        }
        rect_y += vel;
        if (rect_y > WINDOW_Y - RECT_HEIGHT){
            rect_y = WINDOW_Y - RECT_HEIGHT;
            vel = -vel * bounce;
            if (vel > -0.3 && vel < 0.3) vel = 0; 
        }
        if (rect_y < 0) {
            rect_y = 0;
            vel = 0;
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(rect_x, (int)rect_y, RECT_WIDTH, RECT_HEIGHT, DARKBLUE);
        if (isThrusting) {
            DrawFlame(rect_x, rect_y);
        }
        DrawText("Hold SPACE to Fly!", 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("Velocity: %.2f", -vel), 10, 40, 20, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}