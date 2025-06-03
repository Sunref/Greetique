#include "../include/balloon.h"
#include "../include/config.h"
#include <math.h>
#include <raylib.h>

// Initialize balloons with random positions, sizes, and colors
void InitializeBalloons(Balloon balloons[], int maxBalloons, int screenWidth, int screenHeight, bool useHeartBalloons) {
    for (int i = 0; i < maxBalloons; i++) {
        balloons[i].position.x = GetRandomValue(50, screenWidth - 50);
        balloons[i].position.y = GetRandomValue(screenHeight, screenHeight + 300);
        balloons[i].radius = GetRandomValue(20, 40);
        balloons[i].speed = GetRandomValue(1, 3);

        // Use heart shape only if useHeartBalloons is true
        balloons[i].shape = useHeartBalloons ?
            (GetRandomValue(0, 1) ? BALLOON_HEART : BALLOON_OVAL) : // 50% chance of heart if enabled
            BALLOON_OVAL; // Always oval if hearts are disabled

        // Vibrant random colors for balloons
        int colorIndex = GetRandomValue(0, 7);
        switch (colorIndex) {
            case 0: balloons[i].color = RED; break;
            case 1: balloons[i].color = PURPLE; break;
            case 2: balloons[i].color = PINK; break;
            case 3: balloons[i].color = GREEN; break;
            case 4: balloons[i].color = LIME; break;
            case 5: balloons[i].color = ORANGE; break;
            case 6: balloons[i].color = YELLOW; break;
            case 7: balloons[i].color = BLUE; break;
        }
    }
}

// Draw filled heart shape with outline
void DrawHeart(Vector2 position, float radius, Color color) {
    const int segments = 36;
    Vector2 points[segments];

    // Generate heart curve points
    for (int i = 0; i < segments; i++) {
        float t = i * 2 * PI / segments;
        float x = 16 * pow(sin(t), 3);
        float y = -(13 * cos(t) - 5 * cos(2*t) - 2 * cos(3*t) - cos(4*t));

        points[i].x = position.x + (x * radius / 16);
        points[i].y = position.y + (y * radius / 16);
    }

    // Draw heart filling
    for (int i = 1; i < segments - 1; i++) {
        DrawTriangle(points[0], points[i], points[i + 1], color);
    }

    // Draw outline with a slightly darker color
    Color outlineColor = ColorBrightness(color, 0.7f);
    for (int i = 0; i < segments; i++) {
        DrawLineEx(
            points[i],
            points[(i + 1) % segments],
            radius * 0.1f,  // Outline thickness
            outlineColor
        );
    }
}

// Draw balloons with highlights and strings
void DrawBalloons(Balloon balloons[], int maxBalloons, float time) {
    for (int i = 0; i < maxBalloons; i++) {
        if (balloons[i].shape == BALLOON_OVAL) {
            // Draw oval balloon
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
        } else {
            // Draw heart balloon (filled with outline)
            DrawHeart(balloons[i].position, balloons[i].radius * 1.2f, balloons[i].color);

        }

        // Draw balloon string with slight movement
        Color stringColor = LIGHTGRAY;
        DrawLineEx(
            (Vector2){balloons[i].position.x, balloons[i].position.y + balloons[i].radius * 1.3f},
            (Vector2){balloons[i].position.x + sin(time * 2 + i) * 10,
                     balloons[i].position.y + balloons[i].radius * 1.3f + 30},
            2.0f,  // Line thickness
            stringColor
        );
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
