#include "raylib.h"
#include <stdlib.h>
#include <math.h>


#define particle_count_max 300     
#define MAX_VELOCITY 6.0f         
#define MIN_VELOCITY 3.0f          
#define visual_range_squared 1600  
#define protected_range_squared 64 
#define visualRange 40.0f
#define protectedRange 8.0f

#define centeringfactor 0.0005f
#define matchingfactor 0.05f
#define avoidfactor 0.05f
#define turnfactor 0.2f
#define margin 100  

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Color color;
    bool active;
} Particle;

Particle particle_arr[particle_count_max];

void initParticles(Particle *p, int count) {
    for (int i = 0; i < count; i++) {
        p[i].position = (Vector2) {
            GetRandomValue(margin, GetScreenWidth()-margin), 
            GetRandomValue(margin, GetScreenHeight()-margin)
        };
        
        float angle = GetRandomValue(0, 360) * DEG2RAD;
        float speed = GetRandomValue(MIN_VELOCITY * 100, MAX_VELOCITY * 100) / 100.0f;
        p[i].velocity = (Vector2){
            cosf(angle) * speed,
            sinf(angle) * speed
        };
        p[i].color = BLACK;
        p[i].active = true;
    }
}

void updateParticles(Particle *p, int count, float delta) {
    for (int i = 0; i < count; i++) {
        float xpos_avg = 0, ypos_avg = 0;
        float xvel_avg = 0, yvel_avg = 0;
        float close_dx = 0, close_dy = 0;
        int neighboring_boids = 0;

        for (int j = 0; j < count; j++) {
            if (i == j) continue;

            float dx = p[i].position.x - p[j].position.x;
            float dy = p[i].position.y - p[j].position.y;

            if (fabsf(dx) < visualRange && fabsf(dy) < visualRange) {
                float squared_distance = dx*dx + dy*dy;

                if (squared_distance < protected_range_squared) {
                    close_dx += dx;
                    close_dy += dy;
                }
                else if (squared_distance < visual_range_squared) {
                    xpos_avg += p[j].position.x;
                    ypos_avg += p[j].position.y;
                    xvel_avg += p[j].velocity.x;
                    yvel_avg += p[j].velocity.y;
                    neighboring_boids++;
                }
            }
        }

        if (neighboring_boids > 0) {
            xpos_avg /= neighboring_boids;
            ypos_avg /= neighboring_boids;
            xvel_avg /= neighboring_boids;
            yvel_avg /= neighboring_boids;

            p[i].velocity.x += (xpos_avg - p[i].position.x) * centeringfactor + 
                              (xvel_avg - p[i].velocity.x) * matchingfactor;
            p[i].velocity.y += (ypos_avg - p[i].position.y) * centeringfactor + 
                              (yvel_avg - p[i].velocity.y) * matchingfactor;
        }

        p[i].velocity.x += close_dx * avoidfactor;
        p[i].velocity.y += close_dy * avoidfactor;

        if (p[i].position.x < margin) p[i].velocity.x += turnfactor;
        if (p[i].position.x > GetScreenWidth() - margin) p[i].velocity.x -= turnfactor;
        if (p[i].position.y < margin) p[i].velocity.y += turnfactor;
        if (p[i].position.y > GetScreenHeight() - margin) p[i].velocity.y -= turnfactor;

        float speed = sqrt(p[i].velocity.x * p[i].velocity.x + 
                         p[i].velocity.y * p[i].velocity.y);

        if (speed < MIN_VELOCITY) {
            p[i].velocity.x = (p[i].velocity.x/speed) * MIN_VELOCITY;
            p[i].velocity.y = (p[i].velocity.y/speed) * MIN_VELOCITY;
        }
        if (speed > MAX_VELOCITY) {
            p[i].velocity.x = (p[i].velocity.x/speed) * MAX_VELOCITY;
            p[i].velocity.y = (p[i].velocity.y/speed) * MAX_VELOCITY;
        }

        p[i].position.x += p[i].velocity.x;
        p[i].position.y += p[i].velocity.y;
    }
}

int main(void) 
{
    const int screenHeight = 720;
    const int screenWidth = 1080;
    
    InitWindow(screenWidth, screenHeight, "Boids simulation");
    initParticles(particle_arr, particle_count_max);

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        float delta = GetFrameTime();
        updateParticles(particle_arr, particle_count_max, delta);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            for (int i = 0; i < particle_count_max; i++) {
                DrawCircleV(particle_arr[i].position, 2.0f, particle_arr[i].color);
            }
            
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}