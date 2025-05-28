#include <stdio.h>
#include "raylib.h"
#include <string.h>
#include <time.h>
#include "../include/config.h"
#include "../include/messageInterface.h"

#define MAX_INPUT_LENGTH 256

typedef struct {
    Rectangle bounds;
    char text[MAX_INPUT_LENGTH];
    int letterCount;
    bool isSelected;
} TextBox;

int runMessageInterface(AnimationConfig* config) {
    // Initialize window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Message Input Interface");
    SetTargetFPS(60);

    // Initialize text boxes
    TextBox titleBox = {
        .bounds = (Rectangle){ 50, 180, 925, 40 },
        .text = "",
        .letterCount = 0,
        .isSelected = false
    };

    TextBox secondaryBox = {
        .bounds = (Rectangle){ 50, 280, 925, 40 },
        .text = "",
        .letterCount = 0,
        .isSelected = false
    };

    TextBox thirdBox = {
        .bounds = (Rectangle){ 50, 380, 925, 40 },
        .text = "",
        .letterCount = 0,
        .isSelected = false
    };

    // Checkbox para balões em forma de coração
    Rectangle heartCheckbox = { 50, 450, 20, 20 };
    bool useHeartBalloons = false;

    // Build button
    Rectangle buildButton = { 875, 575, 100, 40 };
    int result = 0;

    while (!WindowShouldClose()) {
        // Input handling
        TextBox* selectedBox = NULL;
        if (titleBox.isSelected) selectedBox = &titleBox;
        if (secondaryBox.isSelected) selectedBox = &secondaryBox;
        if (thirdBox.isSelected) selectedBox = &thirdBox;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePoint = GetMousePosition();

            titleBox.isSelected = CheckCollisionPointRec(mousePoint, titleBox.bounds);
            secondaryBox.isSelected = CheckCollisionPointRec(mousePoint, secondaryBox.bounds);
            thirdBox.isSelected = CheckCollisionPointRec(mousePoint, thirdBox.bounds);

            // Check checkbox click
            if (CheckCollisionPointRec(mousePoint, heartCheckbox)) {
                useHeartBalloons = !useHeartBalloons;
            }

            // Check if build button was clicked
            if (CheckCollisionPointRec(mousePoint, buildButton)) {
                FILE* configFile = fopen("animation_config.txt", "w");
                if (configFile != NULL) {
                    fprintf(configFile, "%s\n%s\n%s\n%d",
                        titleBox.text,
                        secondaryBox.text,
                        thirdBox.text,
                        useHeartBalloons ? 1 : 0);
                    fclose(configFile);

                    // Atualizar a estrutura de configuração
                    strcpy(config->mainMessage, titleBox.text);
                    strcpy(config->subMessage, secondaryBox.text);
                    strcpy(config->thirdMessage, thirdBox.text);
                    config->useHeartBalloons = useHeartBalloons;

                    result = 1;
                    break;
                }
            }
        }

        // Text input handling
        if (selectedBox != NULL) {
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (selectedBox->letterCount < MAX_INPUT_LENGTH - 1)) {
                    selectedBox->text[selectedBox->letterCount] = (char)key;
                    selectedBox->text[selectedBox->letterCount + 1] = '\0';
                    selectedBox->letterCount++;
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && selectedBox->letterCount > 0) {
                selectedBox->letterCount--;
                selectedBox->text[selectedBox->letterCount] = '\0';
            }
        }

        // Drawing
        BeginDrawing();
            Color background = { 25, 25, 50, 255 };
            ClearBackground(background);

            // Draw title and timestamp
            DrawText("made by: Sunref", SCREEN_WIDTH - 210, 10, 20, PINK);

            // Draw helpful note in a box
            Rectangle noteBox = (Rectangle){ 50, 50, 925, 80 };
            DrawRectangleRec(noteBox, ColorAlpha(GRAY, 0.2f));
            DrawRectangleLinesEx(noteBox, 1, ColorAlpha(WHITE, 0.3f));

            // Draw note text
            DrawText("Note:", 60, 60, 20, PINK);
            DrawText("Create short messages (but full of emotion) as long messages will be cut off",
                    120, 60, 20, WHITE);
            DrawText("on screen; Use heart-shaped balloons option for your loved ones!",
                    120, 85, 20, WHITE);

            // Draw text boxes and labels
            DrawText("Enter the title message", 50, 150, 20, WHITE);
            DrawRectangleRec(titleBox.bounds, LIGHTGRAY);
            if (titleBox.isSelected) DrawRectangleLinesEx(titleBox.bounds, 4, PURPLE);
            DrawText(titleBox.text, titleBox.bounds.x + 5, titleBox.bounds.y + 10, 20, BLACK);

            DrawText("Enter the secondary message", 50, 250, 20, WHITE);
            DrawRectangleRec(secondaryBox.bounds, LIGHTGRAY);
            if (secondaryBox.isSelected) DrawRectangleLinesEx(secondaryBox.bounds, 4, PURPLE);
            DrawText(secondaryBox.text, secondaryBox.bounds.x + 5, secondaryBox.bounds.y + 10, 20, BLACK);

            DrawText("Enter the third message", 50, 350, 20, WHITE);
            DrawRectangleRec(thirdBox.bounds, LIGHTGRAY);
            if (thirdBox.isSelected) DrawRectangleLinesEx(thirdBox.bounds, 4, PURPLE);
            DrawText(thirdBox.text, thirdBox.bounds.x + 5, thirdBox.bounds.y + 10, 20, BLACK);

            // Draw heart balloon checkbox
            DrawRectangleRec(heartCheckbox, LIGHTGRAY);
            if (useHeartBalloons) {
                DrawRectangle(heartCheckbox.x + 4, heartCheckbox.y + 4,
                            heartCheckbox.width - 8, heartCheckbox.height - 8,
                            PINK);
            }
            DrawText("Use heart-shaped balloons", heartCheckbox.x + 30, heartCheckbox.y + 1, 20, WHITE);

            // Draw build button
            DrawRectangleRec(buildButton, PINK);
            DrawText("Build", buildButton.x + 25, buildButton.y + 10, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return result;
}
