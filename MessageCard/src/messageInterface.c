#include <string.h>
#include "../include/config.h"
#include "../include/raylib/raylib.h"
#include "../include/messageInterface.h"

#define MAX_INPUT_LENGTH 256

typedef struct {
    Rectangle bounds;
    char text[MAX_INPUT_LENGTH];
    int letterCount;
    bool isSelected;
} TextBox;

// Function to load existing configuration into text boxes for editing
// This preserves user's messages when they click "Edit" from animation view
void loadExistingConfig(TextBox* titleBox, TextBox* secondaryBox, TextBox* detailsBox, bool* useHeartBalloons, const AnimationConfig* config) {

    // Safety check
    if (!config) return;

    // Load main message with bounds checking
    if (config->mainMessage[0] != '\0') {
        strncpy(titleBox->text, config->mainMessage, MAX_INPUT_LENGTH - 1);
        titleBox->text[MAX_INPUT_LENGTH - 1] = '\0';
        titleBox->letterCount = strlen(titleBox->text);
    }

    // Load secondary message with bounds checking
    if (config->subMessage[0] != '\0') {
        strncpy(secondaryBox->text, config->subMessage, MAX_INPUT_LENGTH - 1);
        secondaryBox->text[MAX_INPUT_LENGTH - 1] = '\0';
        secondaryBox->letterCount = strlen(secondaryBox->text);
    }

    // Load details message with bounds checking
    if (config->detailsMessage[0] != '\0') {
        strncpy(detailsBox->text, config->detailsMessage, MAX_INPUT_LENGTH - 1);
        detailsBox->text[MAX_INPUT_LENGTH - 1] = '\0';
        detailsBox->letterCount = strlen(detailsBox->text);
    }

    // Load heart balloons setting
    *useHeartBalloons = config->useHeartBalloons;

}

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

    TextBox detailsBox = {
        .bounds = (Rectangle){ 50, 380, 925, 40 },
        .text = "",
        .letterCount = 0,
        .isSelected = false
    };

    // Checkbox for heart-shaped balloons
    Rectangle heartCheckbox = { 50, 450, 20, 20 };
    bool useHeartBalloons = false;

    // Load existing configuration if available
    loadExistingConfig(&titleBox, &secondaryBox, &detailsBox, &useHeartBalloons, config);

    // Create Animation button (centered)
    Rectangle buildButton = { 400, 575, 200, 40 };

    int result = 0;
    Vector2 mousePoint = { 0.0f, 0.0f };

    while (!WindowShouldClose()) {
        // Update mouse position
        mousePoint = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Check text box selection
            titleBox.isSelected = CheckCollisionPointRec(mousePoint, titleBox.bounds);
            secondaryBox.isSelected = CheckCollisionPointRec(mousePoint, secondaryBox.bounds);
            detailsBox.isSelected = CheckCollisionPointRec(mousePoint, detailsBox.bounds);

            // Check checkbox click
            if (CheckCollisionPointRec(mousePoint, heartCheckbox)) {
                useHeartBalloons = !useHeartBalloons;
            }

            // Check if create animation button was clicked
            if (CheckCollisionPointRec(mousePoint, buildButton)) {
                // Update configuration structure directly
                strcpy(config->mainMessage, titleBox.text);
                strcpy(config->subMessage, secondaryBox.text);
                strcpy(config->detailsMessage, detailsBox.text);
                config->useHeartBalloons = useHeartBalloons;

                result = 1;
                break;
            }
        }

        // Handle text input
        TextBox* selectedBox = NULL;
        if (titleBox.isSelected) selectedBox = &titleBox;
        if (secondaryBox.isSelected) selectedBox = &secondaryBox;
        if (detailsBox.isSelected) selectedBox = &detailsBox;

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
            Color background = { 210, 180, 140, 255 };
            ClearBackground(background);

            // Draw title
            DrawText("Message Card Creator", (SCREEN_WIDTH - MeasureText("Message Card Creator", 40)) / 2, 10, 40, WHITE);
            DrawText("made by: Sunref", SCREEN_WIDTH - 210, 10, 20, BROWN);

            // Draw helpful note in a box
            Rectangle noteBox = (Rectangle){ 50, 50, 925, 80 };
            DrawRectangleRec(noteBox, ColorAlpha(GRAY, 0.2f));
            DrawRectangleLinesEx(noteBox, 1, ColorAlpha(WHITE, 0.3f));

                DrawText("Note:", 60, 60, 20, BROWN);
            DrawText("Create short messages as long messages will be cut off on screen.",
                    120, 60, 20, WHITE);
            DrawText("Use heart-shaped balloons option for your loved ones!",
                    120, 85, 20, WHITE);

            // Draw text boxes and labels
            DrawText("Enter the title message", 50, 150, 20, BROWN);
            DrawRectangleRec(titleBox.bounds, WHITE);
            if (titleBox.isSelected) DrawRectangleLinesEx(titleBox.bounds, 4, BROWN);
            DrawText(titleBox.text, titleBox.bounds.x + 5, titleBox.bounds.y + 10, 20, BLACK);

            DrawText("Enter the secondary message", 50, 250, 20, BROWN);
            DrawRectangleRec(secondaryBox.bounds, WHITE);
            if (secondaryBox.isSelected) DrawRectangleLinesEx(secondaryBox.bounds, 4, BROWN);
            DrawText(secondaryBox.text, secondaryBox.bounds.x + 5, secondaryBox.bounds.y + 10, 20, BLACK);

            DrawText("Enter the details message", 50, 350, 20, BROWN);
            DrawRectangleRec(detailsBox.bounds, WHITE);
            if (detailsBox.isSelected) DrawRectangleLinesEx(detailsBox.bounds, 4, BROWN);
            DrawText(detailsBox.text, detailsBox.bounds.x + 5, detailsBox.bounds.y + 10, 20, BLACK);

            // Draw heart balloon checkbox
            DrawRectangleRec(heartCheckbox, WHITE);
            if (useHeartBalloons) {
                DrawRectangle(heartCheckbox.x + 4, heartCheckbox.y + 4,
                            heartCheckbox.width - 8, heartCheckbox.height - 8,
                            BROWN);
            }
            DrawText("Use heart-shaped balloons", heartCheckbox.x + 30, heartCheckbox.y + 1, 20, BROWN);

            // Draw create animation button
            DrawRectangleRec(buildButton, BROWN);
            DrawText("Create Animation", buildButton.x + 15, buildButton.y + 10, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return result;

}
