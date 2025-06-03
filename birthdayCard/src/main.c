#include "raylib.h"
#include "../include/balloon.h"
#include "../include/star.h"
#include "../include/animation.h"
#include "../include/messageInterface.h"
#include "../include/messageLoader.h"
#include "../include/config.h"
#include "../include/menuInterface.h"

int main() {
    // Create configuration structure
    AnimationConfig config = {0};

    while (1) {
        // Run the menu interface
        int menuChoice = runMenuInterface();

        switch (menuChoice) {
            case 0: // Exit program
                return 0;

            case 1: // Write new message
                if (runMessageInterface(&config)) {
                    RunBirthdayAnimation(&config, 1);  // 1 indica que veio da interface de escrita
                }
                break;

            case 2: // Read existing message
                if (LoadMessagesFromFile(&config)) {
                    RunBirthdayAnimation(&config, 0);  // 0 indica que não veio da interface de escrita
                } else {
                    const int screenWidth = 400;
                    const int screenHeight = 200;

                    InitWindow(screenWidth, screenHeight, "Error");
                    SetTargetFPS(60);

                    while (!WindowShouldClose()) {
                        BeginDrawing();
                            ClearBackground(RAYWHITE);
                            DrawText("No saved message found!", 50, 80, 20, RED);
                            DrawText("Press ESC to return", 50, 120, 20, DARKGRAY);
                        EndDrawing();
                    }

                    CloseWindow();
                }
                break;
        }
    }

    return 0;
}
