#include "../include/balloon.h"
#include "../include/config.h"
#include <math.h>

// Initialize balloons with random positions, sizes, and colors
void InitializeBalloons(Balloon balloons[], int maxBalloons, int screenWidth, int screenHeight) {
    for (int i = 0; i < maxBalloons; i++) {
        balloons[i].position.x = GetRandomValue(50, screenWidth - 50);
        balloons[i].position.y = GetRandomValue(screenHeight, screenHeight + 300);
        balloons[i].radius = GetRandomValue(20, 40);
        balloons[i].speed = GetRandomValue(1, 3);

        // Vibrant random colors for balloons
        int colorIndex = GetRandomValue(0, 3);
        switch (colorIndex) {
            case 0: balloons[i].color = RED; break;
            case 1: balloons[i].color = PURPLE; break;
            case 2: balloons[i].color = MAGENTA; break;
            case 3: balloons[i].color = PINK; break;
        }
    }
}

// Update balloon positions and movement
void UpdateBalloons(Balloon balloons[], int maxBalloons, int screenHeight, float time) {
    for (int i = 0; i < maxBalloons; i++) {
        // Move upward at balloon speed
        balloons[i].position.y -= balloons[i].speed;

        // Gentle side-to-side floating effect
        balloons[i].position.x += sin(time + i) * 0.5f;

        // Reset position if balloon moves off-screen
        if (balloons[i].position.y < -balloons[i].radius * 2) {
            balloons[i].position.y = screenHeight + balloons[i].radius;
            balloons[i].position.x = GetRandomValue(50, SCREEN_WIDTH - 50);
        }
    }
}

// Draw balloons with highlights and strings
void DrawBalloons(Balloon balloons[], int maxBalloons, float time) {
    for (int i = 0; i < maxBalloons; i++) {
        // Draw balloon (oval shape)
        DrawEllipse(
            balloons[i].position.x,
            balloons[i].position.y,
            balloons[i].radius,
            balloons[i].radius * 1.3f,
            balloons[i].color
        );

        // Draw highlight/reflection on balloon
        DrawEllipse(
            balloons[i].position.x - balloons[i].radius * 0.3f,
            balloons[i].position.y - balloons[i].radius * 0.3f,
            balloons[i].radius * 0.2f,
            balloons[i].radius * 0.2f,
            WHITE
        );

        // Draw balloon string with slight movement
        DrawLine(
            balloons[i].position.x,
            balloons[i].position.y + balloons[i].radius * 1.3f,
            balloons[i].position.x + sin(time * 2 + i) * 10,
            balloons[i].position.y + balloons[i].radius * 1.3f + 30,
            WHITE
        );
    }
}
