#include <stdio.h>
#include "raylib.h"
#include <string.h>
#include "../include/config.h"
#include "../include/messageInterface.h"
#include <sys/stat.h>
#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(dir) _mkdir(dir)
#else
    #include <unistd.h>
    #define MKDIR(dir) mkdir(dir, 0777)
#endif

#define MAX_INPUT_LENGTH 256

typedef struct {
    Rectangle bounds;
    char text[MAX_INPUT_LENGTH];
    int letterCount;
    bool isSelected;
} TextBox;

void loadExistingConfig(TextBox* titleBox, TextBox* secondaryBox, TextBox* thirdBox, bool* useHeartBalloons) {
    FILE* configFile = fopen("animation_config.txt", "r");
    if (configFile != NULL) {
        char buffer[MAX_INPUT_LENGTH];

        // Read the main message
        if (fgets(buffer, sizeof(buffer), configFile)) {
            buffer[strcspn(buffer, "\n")] = 0;  // Remove the \n
            strcpy(titleBox->text, buffer);
            titleBox->letterCount = strlen(buffer);
        }

        // Read the secondary message
        if (fgets(buffer, sizeof(buffer), configFile)) {
            buffer[strcspn(buffer, "\n")] = 0;
            strcpy(secondaryBox->text, buffer);
            secondaryBox->letterCount = strlen(buffer);
        }

        // Read the third message
        if (fgets(buffer, sizeof(buffer), configFile)) {
            buffer[strcspn(buffer, "\n")] = 0;
            strcpy(thirdBox->text, buffer);
            thirdBox->letterCount = strlen(buffer);
        }

        // Read the balloons configuration
        int heartBalloons;
        if (fscanf(configFile, "%d", &heartBalloons) == 1) {
            *useHeartBalloons = heartBalloons != 0;
        }

        fclose(configFile);
    }
}

void saveCardToArchive(const char* cardName, const AnimationConfig* config) {
    char folderPath[512];
    char filePath[512];

    // Create saved_cards folder path if it doesn't exist
    #ifdef _WIN32
    MKDIR("saved_cards");
    snprintf(folderPath, sizeof(folderPath), "saved_cards\\%s", cardName);
    MKDIR(folderPath);
    snprintf(filePath, sizeof(filePath), "%s\\animation_config.txt", folderPath);
    #else
    MKDIR("saved_cards");
    snprintf(folderPath, sizeof(folderPath), "saved_cards/%s", cardName);
    MKDIR(folderPath);
    snprintf(filePath, sizeof(filePath), "%s/animation_config.txt", folderPath);
    #endif

    // Save configuration file in the card folder
    FILE* configFile = fopen(filePath, "w");
    if (configFile != NULL) {
        fprintf(configFile, "%s\n%s\n%s\n%d",
            config->mainMessage,
            config->subMessage,
            config->thirdMessage,
            config->useHeartBalloons ? 1 : 0);
        fclose(configFile);
    }
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

    TextBox thirdBox = {
        .bounds = (Rectangle){ 50, 380, 925, 40 },
        .text = "",
        .letterCount = 0,
        .isSelected = false
    };

    // Checkbox para balões em forma de coração
    Rectangle heartCheckbox = { 50, 450, 20, 20 };
    bool useHeartBalloons = false;

    // Load existing configuration
    loadExistingConfig(&titleBox, &secondaryBox, &thirdBox, &useHeartBalloons);

    // Build button
    Rectangle buildButton = { 875, 575, 100, 40 };

    // Save button
    Rectangle saveButton = { 750, 575, 100, 40 };

    // Variables for saving card
    char cardName[256] = "";
    bool showNameInput = false;

    int result = 0;
    Vector2 mousePoint = { 0.0f, 0.0f };

    while (!WindowShouldClose()) {
        // Update mouse position
        mousePoint = GetMousePosition();

        // Input handling
        TextBox* selectedBox = NULL;
        if (titleBox.isSelected) selectedBox = &titleBox;
        if (secondaryBox.isSelected) selectedBox = &secondaryBox;
        if (thirdBox.isSelected) selectedBox = &thirdBox;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (!showNameInput) {  // Only allows clicking elements if not showing name input
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

                        // Update configuration structure
                        strcpy(config->mainMessage, titleBox.text);
                        strcpy(config->subMessage, secondaryBox.text);
                        strcpy(config->thirdMessage, thirdBox.text);
                        config->useHeartBalloons = useHeartBalloons;

                        result = 1;
                        break;
                    }
                }

                // Check if save button was clicked
                if (CheckCollisionPointRec(mousePoint, saveButton)) {
                    showNameInput = true;
                }
            }
        }

        // Text input handling
        if (showNameInput) {
            // Capture the card name
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (strlen(cardName) < 255)) {
                    cardName[strlen(cardName)] = (char)key;
                    cardName[strlen(cardName) + 1] = '\0';
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && strlen(cardName) > 0) {
                cardName[strlen(cardName) - 1] = '\0';
            }

            if (IsKeyPressed(KEY_ENTER) && strlen(cardName) > 0) {
                AnimationConfig tempConfig = {0};
                strcpy(tempConfig.mainMessage, titleBox.text);
                strcpy(tempConfig.subMessage, secondaryBox.text);
                strcpy(tempConfig.thirdMessage, thirdBox.text);
                tempConfig.useHeartBalloons = useHeartBalloons;

                saveCardToArchive(cardName, &tempConfig);
                showNameInput = false;
                cardName[0] = '\0';
            }
        } else if (selectedBox != NULL) {
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

            // Draw save button
            DrawRectangleRec(saveButton, PINK);
            DrawText("Save", saveButton.x + 30, saveButton.y + 10, 20, WHITE);

            // Draw build button
            DrawRectangleRec(buildButton, PINK);
            DrawText("Build", buildButton.x + 25, buildButton.y + 10, 20, WHITE);

            // Draw name input interface
            if (showNameInput) {
                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, ColorAlpha(BLACK, 0.8f));
                DrawText("Enter card name:", SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 40, 20, WHITE);
                DrawText(cardName, SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2, 20, WHITE);
                DrawText("Press ENTER to save", SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 40, 20, GRAY);
            }

        EndDrawing();
    }

    CloseWindow();
    return result;
}
