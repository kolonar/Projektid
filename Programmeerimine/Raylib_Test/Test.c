#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_X 1000
#define WINDOW_Y 700
#define FPS 60

#define RECT_WIDTH 50
#define RECT_HEIGHT 50

#define GRAVITY 9.81f
#define THRUST_POWER 10.0f
#define BOUNCE 0.5f
#define FRICTION 0.5f
#define VEL_MAX 20.0f //not used
#define GOAL { (WINDOW_X/2) + (RECT_WIDTH/2), (WINDOW_Y/2) + (RECT_HEIGHT/2) }

#define Kp 0.1f
#define Ki 0.01f
#define Kd 0.1f

void ApplyThrust(float *vel_x, float *vel_y, float *desire) {
    *vel_x += (THRUST_POWER * desire[0]) / FPS;
    *vel_y += (THRUST_POWER * desire[1]) / FPS; 
}
void DrawFlame(float x, float y, char *dir) {
    if (*dir == 'u'){
        Vector2 p1 = { x + 15, y+50 };
        Vector2 p2 = { x + 25, y + 80 };
        Vector2 p3 = { x + 35, y+50 };
        DrawTriangle(p1, p2, p3, ORANGE);
    } else if (*dir == 'l'){
        Vector2 p1 = { x + 50, y + 15};
        Vector2 p2 = { x + 50, y + 35};
        Vector2 p3 = { x + 80, y + 25};
        DrawTriangle(p1, p2, p3, ORANGE);
    }else if (*dir == 'r'){
        Vector2 p1 = { x - 30, y + 25};
        Vector2 p2 = { x, y + 35};
        Vector2 p3 = { x, y + 15};
        DrawTriangle(p1, p2, p3, ORANGE);
    }else if (*dir == 'd'){
        Vector2 p1 = { x + 15, y-0 };
        Vector2 p2 = { x + 35, y-0 };
        Vector2 p3 = { x + 25, y-30 };
        DrawTriangle(p1, p2, p3, ORANGE);
    }
}
void PID(float x, float y, float *vel_x, float *vel_y) {
    float dt = GetFrameTime(); 
    
    if (dt <= 0.0f) return; 

    float ex = ((float[])GOAL)[0] - x - (RECT_WIDTH/2);
    float ey = ((float[])GOAL)[1] - y - (RECT_HEIGHT/2);

    float Px = Kp * ex;
    float Py = Kp * ey;

    static float integral_x = 0;
    static float integral_y = 0;
    
    integral_x += ex * dt; 
    integral_y += ey * dt;

    float Ix = Ki * integral_x;
    float Iy = Ki * integral_y;

    static float prev_ex = 0;
    static float prev_ey = 0;

    float Dx = Kd * (ex - prev_ex) / dt;
    float Dy = Kd * (ey - prev_ey) / dt;

    prev_ex = ex;
    prev_ey = ey;

    float desire[2] = {Px + Ix + Dx, Py + Iy + Dy};
    ApplyThrust(vel_x, vel_y, desire);
}
int main(){
    InitWindow(WINDOW_X, WINDOW_Y, "Test");
    SetTargetFPS(FPS);

    float rect_x = 450;
    float rect_y = 600;
    float vel_x = 0;
    float vel_y = 0;
    float desire[2]={0,0};
    char direction = 'n';

    while (!WindowShouldClose()){
        vel_y += GRAVITY / FPS;
        bool isThrusting = false;
        if (IsKeyDown(KEY_UP)) {
            desire[0]=0;
            desire[1]=-55;
            ApplyThrust(&vel_x,&vel_y,desire);
            isThrusting = true;
            direction = 'u';
        }
        if (IsKeyDown(KEY_DOWN)) {
            desire[0]=0;
            desire[1]=55;
            ApplyThrust(&vel_x,&vel_y,desire);
            isThrusting = true;
            direction = 'd';
        }
        if (IsKeyDown(KEY_LEFT)) {
            desire[0]=-55;
            desire[1]=0;
            ApplyThrust(&vel_x,&vel_y,desire);
            isThrusting = true;
            direction = 'l';
        }
        if (IsKeyDown(KEY_RIGHT)) {
            desire[0]=55;
            desire[1]=0;
            ApplyThrust(&vel_x,&vel_y,desire);
            isThrusting = true;
            direction = 'r';
        }
        PID(rect_x,rect_y, &vel_x, &vel_y);
        rect_y += vel_y;
        rect_x += vel_x;
        if (rect_y > WINDOW_Y - RECT_HEIGHT){
            rect_y = WINDOW_Y - RECT_HEIGHT;
            vel_y = -vel_y * BOUNCE;
            vel_x = vel_x * FRICTION;
            if (vel_y > -0.3 && vel_y < 0.3) vel_y = 0; 
        }
        else if (rect_y <=0){
            rect_y = 0;
            vel_y = -vel_y * BOUNCE;
            if (vel_y > -0.3 && vel_y < 0.3) vel_y = 0; 
        }
        
        if (rect_x <= 0){
            rect_x = 0;
            vel_x = -vel_x * BOUNCE;
            if (vel_x > -0.3 && vel_x < 0.3) vel_x = 0; 
        }
        else if (rect_x >= WINDOW_X-RECT_WIDTH){
            rect_x = WINDOW_X-RECT_WIDTH;
            vel_x = -vel_x * BOUNCE;
            if (vel_x > -0.3 && vel_x < 0.3) vel_x = 0; 
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircle(((float[])GOAL)[0], ((float[])GOAL)[1], 50.0f, RED);
        DrawRectangle(rect_x, rect_y, RECT_WIDTH, RECT_HEIGHT, DARKBLUE);
        if (isThrusting) {
            DrawFlame(rect_x, rect_y, &direction);
            DrawText("Thrusting!", 400,10,20,DARKPURPLE);
        }
        float total_vel = abs(vel_y)+abs(vel_x);
        DrawText(TextFormat("Velocity: %.2f", total_vel), 10, 40, 20, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}