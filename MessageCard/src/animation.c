#include <math.h>
#include <stdio.h>
#include <string.h>
#include "../include/gif.h"
#include "../include/star.h"
#include "../include/balloon.h"
#include "../include/animation.h"

#define SAVE_BUTTON_WIDTH 100
#define SAVE_BUTTON_HEIGHT 40
#define SAVE_BUTTON_PADDING 20
#define EXIT_BUTTON_WIDTH 80
#define EXIT_BUTTON_HEIGHT 32
#define EXIT_BUTTON_PADDING 20
#define MAX_FRAMES 300

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

    // Draw details message only if it's not empty
    if (strlen(config->detailsMessage) > 0) {
        int detailsTextWidth = MeasureText(config->detailsMessage, DETAILS_FONT_SIZE);
        int detailsX = (SCREEN_WIDTH - detailsTextWidth) / 2;
        DrawText(config->detailsMessage, detailsX, 320, DETAILS_FONT_SIZE,
                 (Color){200, 200, 255, 255});
    }

}

void SaveAnimationAsGif(const AnimationConfig* config, const char* filename) {

    const int width = SCREEN_WIDTH;
    const int height = SCREEN_HEIGHT;

    // Initialize GIF writer
    GifWriter writer = {0};
    if (!GifBegin(&writer, filename, width, height, 3, 8, false)) {
        printf("Failed to create GIF file!\n");
        return;
    }

    // Initialize objects
    Balloon balloons[MAX_BALLOONS];
    Star stars[MAX_STARS];
    InitializeBalloons(balloons, MAX_BALLOONS, width, height, config->useHeartBalloons);
    InitializeStars(stars, MAX_STARS, width, height);

    // Position balloons below screen initially (slightly higher)
    for (int i = 0; i < MAX_BALLOONS; i++) {
        balloons[i].position.y = height + balloons[i].radius + GetRandomValue(0, 150);
    }

    // Record frames - 18.3 second cinematic sequence (14.8s + 3.5s for smiley)
    bool success = true;
    int total_frames = 549;  // 18.3 seconds at 30fps

    for (int frame = 0; frame < total_frames; frame++) {
        float currentTime = frame / 30.0f;

        // Define sequence timing
        float star_start = 0.5f;            // Stars appear
        float text_start = 1.5f;            // Text appears
        float balloon_start = 2.0f;         // Balloons start rising
        float balloon_fade_start = 2.0f;    // Balloons start fading
        float balloon_end = 14.0f;          // Balloons disappear
        float text_end = 14.4f;             // Text disappears
        float star_end = 14.8f;             // Stars disappear
        float smiley_start = 14.8f;         // :) appears

        // Update objects conditionally
        UpdateStars(stars, MAX_STARS, currentTime);

        // Balloons start rising only at 2 seconds
        if (currentTime >= balloon_start) {
            UpdateBalloons(balloons, MAX_BALLOONS, height, currentTime);
        }

        // Draw clean frame and capture for GIF
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);

        // Draw stars
        if (currentTime >= star_start && currentTime < star_end) {
            float star_alpha = 1.0f;
            if (currentTime < star_start + 0.5f) {
                // Fade in stars
                star_alpha = (currentTime - star_start) / 0.5f;
            } else if (currentTime >= star_end - 0.5f) {
                // Fade out stars
                star_alpha = (star_end - currentTime) / 0.5f;
            }
            if (star_alpha > 0.0f) {
                DrawStars(stars, MAX_STARS);
            }
        }

        // Draw balloons
        if (currentTime < balloon_end) {
            float balloon_alpha = 1.0f;
            if (currentTime >= balloon_fade_start) {
                // Fade out balloons
                balloon_alpha = (balloon_end - currentTime) / 2.5f;
            }
            if (balloon_alpha > 0.0f) {
                DrawBalloons(balloons, MAX_BALLOONS, currentTime);
            }
        }

        // Draw text
        if (currentTime >= text_start && currentTime < text_end) {
            float text_alpha = 1.0f;
            if (currentTime < text_start + 0.5f) {
                // Fade in text
                text_alpha = (currentTime - text_start) / 0.5f;
            } else if (currentTime >= text_end - 0.5f) {
                // Fade out text
                text_alpha = (text_end - currentTime) / 0.5f;
            }
            if (text_alpha > 0.0f) {
                DrawAnimatedText(currentTime, config);
            }
        }

        // Draw :) when stars disappear
        if (currentTime >= smiley_start) {
            DrawText(":)", SCREEN_WIDTH - 60, SCREEN_HEIGHT - 60, 40, WHITE);
        }

        EndDrawing();

        // Capture clean frame for GIF
        Image screenshot = LoadImageFromScreen();

        // Draw the same frame with saving message for user feedback
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        DrawStars(stars, MAX_STARS);
        DrawBalloons(balloons, MAX_BALLOONS, currentTime);
        DrawAnimatedText(currentTime, config);

        // Add stable saving message
        int progress = (int)((float)frame / total_frames * 100);
        DrawText("Saving...", 20, 20, 30, WHITE);
        DrawText(TextFormat("%d%%", progress), 20, 55, 20, LIGHTGRAY);
        EndDrawing();

        WaitTime(1.0f/30.0f); // Ensure consistent timing

        if (screenshot.data && screenshot.width == width && screenshot.height == height) {
            // Ensure correct format
            if (screenshot.format != PIXELFORMAT_UNCOMPRESSED_R8G8B8A8) {
                ImageFormat(&screenshot, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
            }

            // Write frame with smooth timing
            if (!GifWriteFrame(&writer, screenshot.data, width, height, 3, 8, false)) {
                success = false;
            }
        } else {
            success = false;
        }

        if (screenshot.data) UnloadImage(screenshot);

        if (!success) break;
    }

    // The sequence naturally ends with blue background
    GifEnd(&writer);

    if (success) {
        printf("GIF saved successfully as %s!\n", filename);
    } else {
        printf("Failed to save GIF!\n");
    }

}

void RunMessageAnimation(AnimationConfig* config, int fromWriteInterface) {

    (void)fromWriteInterface; // Suppress unused parameter warning
    // Initialize window for message animation
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Message Card!");
    SetTargetFPS(60);

    // Create rectangle for edit button
    Rectangle editButton = {
        EXIT_BUTTON_PADDING,
        EXIT_BUTTON_PADDING,
        EXIT_BUTTON_WIDTH,
        EXIT_BUTTON_HEIGHT
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

        Vector2 mousePoint = GetMousePosition();

        // Check click on edit button to go back to message interface
        if (CheckCollisionPointRec(mousePoint, editButton)) {
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
                return;
            }
        }

        // Draw
        BeginDrawing();
            ClearBackground(BACKGROUND_COLOR);

            // Draw animation elements
            DrawStars(stars, MAX_STARS);
            DrawBalloons(balloons, MAX_BALLOONS, currentTime);
            DrawAnimatedText(currentTime, config);

            // Draw save GIF button
            Rectangle saveButton = {
                SCREEN_WIDTH - SAVE_BUTTON_WIDTH - SAVE_BUTTON_PADDING,
                SAVE_BUTTON_PADDING,
                SAVE_BUTTON_WIDTH,
                SAVE_BUTTON_HEIGHT
            };

            bool isSaveHovered = CheckCollisionPointRec(mousePoint, saveButton);

            DrawRectangleRec(saveButton, isSaveHovered ? (Color){ 210, 180, 140, 255 } : (Color){220, 210, 180, 255});
            DrawText("Save GIF", saveButton.x + 4, saveButton.y + 10, 20, WHITE);

            if (isSaveHovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                SaveAnimationAsGif(config, "animation.gif");
            }

            // Draw edit button
            bool isEditHovered = CheckCollisionPointRec(mousePoint, editButton);
            DrawRectangleRec(editButton, isEditHovered ? (Color){ 210, 180, 140, 255 } : (Color){220, 210, 180, 255});
            DrawText("Edit", editButton.x + 20, editButton.y + 8, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();

}
