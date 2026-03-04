#include "raylib.h"
#include <math.h>

#define WINDOW_X 1000
#define WINDOW_Y 700
#define FPS 60

#define RECT_WIDTH 50
#define RECT_HEIGHT 50

#define GRAVITY 9.81f
#define THRUST_POWER 1.0f
#define BOUNCE 0.5f
#define FRICTION 0.5f

#define Kp 0.7f
#define Ki 0.5f
#define Kd 1.8f

typedef struct {
    Vector2 integral;
    Vector2 prev_error;
} PIDState;


void ApplyThrust(Vector2 *vel, Vector2 desire, float dt) {
    vel->x += (THRUST_POWER * desire.x) * dt;
    vel->y += (THRUST_POWER * desire.y) * dt; 
}

void DrawFlame(float x, float y, char dir) {
    Vector2 p1, p2, p3;
    if (dir == 'u'){
        p1 = (Vector2){ x + 15, y + 50 }; p2 = (Vector2){ x + 25, y + 80 }; p3 = (Vector2){ x + 35, y + 50 };
    } else if (dir == 'l'){
        p1 = (Vector2){ x + 50, y + 15}; p2 = (Vector2){ x + 50, y + 35}; p3 = (Vector2){ x + 80, y + 25};
    } else if (dir == 'r'){
        p1 = (Vector2){ x - 30, y + 25}; p2 = (Vector2){ x, y + 35}; p3 = (Vector2){ x, y + 15};
    } else if (dir == 'd'){
        p1 = (Vector2){ x + 15, y }; p2 = (Vector2){ x + 35, y }; p3 = (Vector2){ x + 25, y - 30 };
    } else {
        return;
    }
    DrawTriangle(p1, p2, p3, ORANGE);
}

void PID(Vector2 pos, Vector2 goal, Vector2 *vel, PIDState *state, float dt) {
    if (dt <= 0.0f) return; 

    Vector2 error = {
        goal.x - pos.x - (RECT_WIDTH / 2.0f),
        goal.y - pos.y - (RECT_HEIGHT / 2.0f)
    };

    Vector2 P = { Kp * error.x, Kp * error.y };

    state->integral.x += error.x * dt; 
    state->integral.y += error.y * dt;
    Vector2 I = { Ki * state->integral.x, Ki * state->integral.y };

    Vector2 D = {
        Kd * (error.x - state->prev_error.x) / dt,
        Kd * (error.y - state->prev_error.y) / dt
    };

    state->prev_error = error;

    Vector2 desire = { P.x + I.x + D.x, P.y + I.y + D.y };
    ApplyThrust(vel, desire, dt);
}

int main(void) {
    InitWindow(WINDOW_X, WINDOW_Y, "PID Controller");
    SetTargetFPS(FPS);

    Vector2 pos = { 450.0f, 600.0f };
    Vector2 vel = { 0.0f, 0.0f };
    Vector2 goal = { (WINDOW_X/2.0f) + (RECT_WIDTH/2.0f), (WINDOW_Y/2.0f) + (RECT_HEIGHT/2.0f) };
    
    PIDState pid_state = {0};
    char direction = 'n';

    while (!WindowShouldClose()){
        float dt = GetFrameTime();
        
        vel.y += GRAVITY * dt;
        
        bool isThrusting = false;
        Vector2 manual_desire = {0};

        if (IsKeyDown(KEY_UP)) { manual_desire.y = -70.0f; direction = 'u'; isThrusting = true; }
        if (IsKeyDown(KEY_DOWN)) { manual_desire.y = 70.0f; direction = 'd'; isThrusting = true; }
        if (IsKeyDown(KEY_LEFT)) { manual_desire.x = -70.0f; direction = 'l'; isThrusting = true; }
        if (IsKeyDown(KEY_RIGHT)) { manual_desire.x = 70.0f; direction = 'r'; isThrusting = true; }

        if (isThrusting) {
            ApplyThrust(&vel, manual_desire, dt);
        }
        //Comment to fly:
        PID(pos, goal, &vel, &pid_state, dt);

        pos.y += vel.y;
        pos.x += vel.x;

        if (pos.y > WINDOW_Y - RECT_HEIGHT){
            pos.y = WINDOW_Y - RECT_HEIGHT;
            vel.y = -vel.y * BOUNCE;
            vel.x *= FRICTION;
            if (fabsf(vel.y) < 0.3f) vel.y = 0.0f; 
        } else if (pos.y <= 0){
            pos.y = 0;
            vel.y = -vel.y * BOUNCE;
            if (fabsf(vel.y) < 0.3f) vel.y = 0.0f; 
        }
        
        if (pos.x <= 0){
            pos.x = 0;
            vel.x = -vel.x * BOUNCE;
            if (fabsf(vel.x) < 0.3f) vel.x = 0.0f; 
        } else if (pos.x >= WINDOW_X - RECT_WIDTH){
            pos.x = WINDOW_X - RECT_WIDTH;
            vel.x = -vel.x * BOUNCE;
            if (fabsf(vel.x) < 0.3f) vel.x = 0.0f; 
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawCircleV(goal, 50.0f, RED);
            DrawRectangle((int)pos.x, (int)pos.y, RECT_WIDTH, RECT_HEIGHT, DARKBLUE);
            
            if (isThrusting) {
                DrawFlame(pos.x, pos.y, direction);
                DrawText("Thrusting!", 400, 10, 20, DARKPURPLE);
            }
            
            float total_vel = fabsf(vel.y) + fabsf(vel.x); 
            DrawText(TextFormat("Velocity: %.2f", total_vel), 10, 40, 20, BLACK);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}