#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "../include/config.h"
#include "../include/messageInterface.h"
#include "../include/animation.h"

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define BUTTON_SPACING 40

int runMenuInterface(void) {
    // Initialize window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Message Card Menu");
    SetTargetFPS(60);

    // Calculate button positions (centered)
    Rectangle readButton = {
        (SCREEN_WIDTH - BUTTON_WIDTH) / 2,
        (SCREEN_HEIGHT - BUTTON_HEIGHT * 2 - BUTTON_SPACING) / 2,
        BUTTON_WIDTH,
        BUTTON_HEIGHT
    };

    Rectangle writeButton = {
        (SCREEN_WIDTH - BUTTON_WIDTH) / 2,
        readButton.y + BUTTON_HEIGHT + BUTTON_SPACING,
        BUTTON_WIDTH,
        BUTTON_HEIGHT
    };

    Vector2 mousePoint = { 0.0f, 0.0f };
    bool readHovered = false;
    bool writeHovered = false;
    Color buttonColor = PINK;
    Color hoverColor = (Color){ 255, 170, 200, 255 }; // Light pink

    while (!WindowShouldClose()) {
        mousePoint = GetMousePosition();

        // Check button hover states
        readHovered = CheckCollisionPointRec(mousePoint, readButton);
        writeHovered = CheckCollisionPointRec(mousePoint, writeButton);

        // Check for button clicks
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (readHovered) {
                CloseWindow();
                // Carregar e executar a animação diretamente
                AnimationConfig config = {0};
                FILE* configFile = fopen("animation_config.txt", "r");
                if (configFile != NULL) {
                    char buffer[256];
                    if (fgets(buffer, sizeof(buffer), configFile)) {
                        buffer[strcspn(buffer, "\n")] = 0;
                        strcpy(config.mainMessage, buffer);
                    }
                    if (fgets(buffer, sizeof(buffer), configFile)) {
                        buffer[strcspn(buffer, "\n")] = 0;
                        strcpy(config.subMessage, buffer);
                    }
                    if (fgets(buffer, sizeof(buffer), configFile)) {
                        buffer[strcspn(buffer, "\n")] = 0;
                        strcpy(config.thirdMessage, buffer);
                    }
                    fscanf(configFile, "%d", &config.useHeartBalloons);
                    fclose(configFile);
                    return 2; // Código para executar animação
                }
                return 0; // Erro ao ler arquivo
            }
            if (writeHovered) {
                CloseWindow();
                return 1; // Código para abrir interface de mensagem
            }
        }

        BeginDrawing();
            Color background = { 25, 25, 50, 255 };
            ClearBackground(background);

            // Draw title
            DrawText("Birthday Card Creator",
                    (SCREEN_WIDTH - MeasureText("Birthday Card Creator", 40)) / 2,
                    100, 40, WHITE);

            // Draw subtitle
            DrawText("made by: Sunref",
                    SCREEN_WIDTH - 210, 10, 20, PINK);

            // Draw Read Button
            DrawRectangleRec(readButton, readHovered ? hoverColor : buttonColor);
            DrawText("Read a Message",
                    readButton.x + (readButton.width - MeasureText("Read a Message", 20)) / 2,
                    readButton.y + (readButton.height - 20) / 2, 20, WHITE);

            // Draw Write Button
            DrawRectangleRec(writeButton, writeHovered ? hoverColor : buttonColor);
            DrawText("Write a Message",
                    writeButton.x + (writeButton.width - MeasureText("Write a Message", 20)) / 2,
                    writeButton.y + (writeButton.height - 20) / 2, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
