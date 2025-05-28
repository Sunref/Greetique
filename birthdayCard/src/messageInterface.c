#include <stdio.h>
#include "raylib.h"
#include <string.h>
#include "../include/config.h"
#include "../include/messageInterface.h"

#define MAX_INPUT_LENGTH 256

typedef struct {
    Rectangle bounds;
    char text[MAX_INPUT_LENGTH];
    int letterCount;
    bool isSelected;
} TextBox;

int runMessageInterface(void) {
    // Initialize window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Message Input Interface");
    SetTargetFPS(60);

    // Initialize text boxes
    TextBox titleBox = {
        .bounds = (Rectangle){ 50, 100, 925, 40 },
        .text = "",
        .letterCount = 0,
        .isSelected = false
    };

    TextBox secondaryBox = {
        .bounds = (Rectangle){ 50, 200, 925, 40 },
        .text = "",
        .letterCount = 0,
        .isSelected = false
    };

    TextBox thirdBox = {
        .bounds = (Rectangle){ 50, 300, 925, 40 },
        .text = "",
        .letterCount = 0,
        .isSelected = false
    };

    // Build button
    Rectangle buildButton = { 875, 575, 100, 40 };
    int result = 0; // Return value: 0 = cancelled, 1 = messages saved

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

            // Check if build button was clicked
            if (CheckCollisionPointRec(mousePoint, buildButton)) {
                // Save messages to a configuration file
                FILE* configFile = fopen("messages.txt", "w");
                if (configFile != NULL) {
                    fprintf(configFile, "%s\n%s\n%s",
                        titleBox.text,
                        secondaryBox.text,
                        thirdBox.text);
                    fclose(configFile);
                    result = 1; // Success
                    break; // Exit the loop
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

            // Draw title
            DrawText("made by: sunref", SCREEN_WIDTH - 210, 10, 20, PINK);

            // Draw text boxes and labels
            DrawText("Enter the title message", 50, 70, 20, WHITE);
            DrawRectangleRec(titleBox.bounds, LIGHTGRAY);
            if (titleBox.isSelected) DrawRectangleLinesEx(titleBox.bounds, 4, PURPLE);
            DrawText(titleBox.text, titleBox.bounds.x + 5, titleBox.bounds.y + 10, 20, BLACK);

            DrawText("Enter the secondary message", 50, 170, 20, WHITE);
            DrawRectangleRec(secondaryBox.bounds, LIGHTGRAY);
            if (secondaryBox.isSelected) DrawRectangleLinesEx(secondaryBox.bounds, 4, PURPLE);
            DrawText(secondaryBox.text, secondaryBox.bounds.x + 5, secondaryBox.bounds.y + 10, 20, BLACK);

            DrawText("Enter the third message", 50, 270, 20, WHITE);
            DrawRectangleRec(thirdBox.bounds, LIGHTGRAY);
            if (thirdBox.isSelected) DrawRectangleLinesEx(thirdBox.bounds, 4, PURPLE);
            DrawText(thirdBox.text, thirdBox.bounds.x + 5, thirdBox.bounds.y + 10, 20, BLACK);

            // Draw build button
            DrawRectangleRec(buildButton, PINK);
            DrawText("Build", buildButton.x + 25, buildButton.y + 10, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return result;
}
