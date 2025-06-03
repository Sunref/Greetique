#include "../include/animation.h"
#include "../include/messageInterface.h"
#include "../include/balloon.h"
#include "../include/star.h"
#include <math.h>
#include <string.h>

// Definitions for back button
#define BACK_BUTTON_WIDTH 32
#define BACK_BUTTON_HEIGHT 32
#define BACK_BUTTON_PADDING 20

// Draw message with animated color effects
void DrawAnimatedText(float currentTime, const AnimationConfig* config) {
    // Add animation effects
    float bounce = sin(currentTime * 2.0f) * 5.0f;
    float fade = (sin(currentTime * 3.0f) + 1.0f) / 2.0f;

    // Draw main message only if it's not empty
    if (strlen(config->mainMessage) > 0) {
        int mainTextWidth = MeasureText(config->mainMessage, MAIN_FONT_SIZE);
        int mainX = (SCREEN_WIDTH - mainTextWidth) / 2;
        DrawText(config->mainMessage, mainX, 200 + (int)bounce, MAIN_FONT_SIZE,
                 (Color){255, (unsigned char)(255 * fade), 100, 255});
    }

    // Draw sub message only if it's not empty
    if (strlen(config->subMessage) > 0) {
        int subTextWidth = MeasureText(config->subMessage, SUB_FONT_SIZE);
        int subX = (SCREEN_WIDTH - subTextWidth) / 2;
        DrawText(config->subMessage, subX, 280, SUB_FONT_SIZE,
                 (Color){255, 255, 255, 255});
    }

    // Draw third message only if it's not empty
    if (strlen(config->thirdMessage) > 0) {
        int thirdTextWidth = MeasureText(config->thirdMessage, THIRD_FONT_SIZE);
        int thirdX = (SCREEN_WIDTH - thirdTextWidth) / 2;
        DrawText(config->thirdMessage, thirdX, 320, THIRD_FONT_SIZE,
                 (Color){200, 200, 255, 255});
    }
}

void RunMessageAnimation(AnimationConfig* config, int fromWriteInterface) {
    // Initialize window for message animation
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Message Card!");
    SetTargetFPS(60);

    // Create rectangle for back button
    Rectangle backButton = {
        BACK_BUTTON_PADDING,
        BACK_BUTTON_PADDING,
        BACK_BUTTON_WIDTH,
        BACK_BUTTON_HEIGHT
    };

    // Initialize objects
    Balloon balloons[MAX_BALLOONS];
    Star stars[MAX_STARS];
    InitializeBalloons(balloons, MAX_BALLOONS, SCREEN_WIDTH, SCREEN_HEIGHT, config->useHeartBalloons);
    InitializeStars(stars, MAX_STARS, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Main animation loop
    while (!WindowShouldClose()) {
        // Update
        float currentTime = GetTime();
        UpdateBalloons(balloons, MAX_BALLOONS, SCREEN_HEIGHT, currentTime);
        UpdateStars(stars, MAX_STARS, currentTime);

        // Check click on back button (only if coming from write interface)
        if (fromWriteInterface) {
            Vector2 mousePoint = GetMousePosition();
            if (CheckCollisionPointRec(mousePoint, backButton)) {
                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                    CloseWindow();
                    if (runMessageInterface(config)) {
                        RunMessageAnimation(config, 1);  // Call animation directly after editing
                    }
                    return;
                }
            }
        }

        // Draw
        BeginDrawing();
            ClearBackground(BACKGROUND_COLOR);

            // Draw animation elements
            DrawStars(stars, MAX_STARS);
            DrawBalloons(balloons, MAX_BALLOONS, currentTime);
            DrawAnimatedText(currentTime, config);

            // Draw back button only if coming from write interface
            if (fromWriteInterface) {
                // Draw button background
                Vector2 mousePoint = GetMousePosition();
                bool isHovered = CheckCollisionPointRec(mousePoint, backButton);

                DrawRectangleRec(backButton, isHovered ? (Color){255, 192, 203, 255} : (Color){255, 182, 193, 200});

                // Draw back arrow
                Vector2 points[3] = {
                    {backButton.x + backButton.width * 0.7f, backButton.y + backButton.height * 0.2f},
                    {backButton.x + backButton.width * 0.3f, backButton.y + backButton.height * 0.5f},
                    {backButton.x + backButton.width * 0.7f, backButton.y + backButton.height * 0.8f}
                };

                for (int i = 0; i < 2; i++) {
                    DrawLineV(points[i], points[i + 1], WHITE);
                }
            }
        EndDrawing();
    }

    CloseWindow();
}
