#include "raylib.h"
#include "../include/balloon.h"
#include "../include/star.h"
#include "../include/animation.h"
#include "../include/messageInterface.h"
#include "../include/messageLoader.h"
#include "../include/config.h"

int main() {
    // Create configuration structure
    AnimationConfig config = {0};

    // Run message interface to get user input
    int messagesSaved = runMessageInterface(&config);

    // If user didn't save messages (closed window without clicking Build), exit
    if (!messagesSaved) {
        return 0;
    }

    // Load messages from recently saved file
    LoadMessagesFromFile(&config);

    // Initialize window for birthday animation
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Happy Birthday!");
    SetTargetFPS(60);

    // Initialize objects
    Balloon balloons[MAX_BALLOONS];
    Star stars[MAX_STARS];
    InitializeBalloons(balloons, MAX_BALLOONS, SCREEN_WIDTH, SCREEN_HEIGHT, config.useHeartBalloons);
    InitializeStars(stars, MAX_STARS, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Main loop
    while (!WindowShouldClose()) {
        // Update
        float currentTime = GetTime();
        UpdateBalloons(balloons, MAX_BALLOONS, SCREEN_HEIGHT, currentTime);
        UpdateStars(stars, MAX_STARS, currentTime);

        // Draw
        BeginDrawing();
            ClearBackground(BACKGROUND_COLOR);

            // Draw animation elements
            DrawStars(stars, MAX_STARS);
            DrawBalloons(balloons, MAX_BALLOONS, currentTime);
            DrawAnimatedText(currentTime);

        EndDrawing();
    }

    // Cleanup
    CloseWindow();
    return 0;
}
