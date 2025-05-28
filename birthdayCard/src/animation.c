#include "../include/animation.h"
#include "../include/config.h"
#include "../include/messageLoader.h"
#include <math.h>
#include <string.h>

// Draw birthday message with animated color effects
void DrawAnimatedText(float currentTime) {
    // Get the loaded messages instead of using hardcoded ones
    const char* mainMessage = GetMainMessage();
    const char* subMessage = GetSubMessage();
    const char* thirdMessage = GetThirdMessage();

    // Add some animation effects if you want
    float bounce = sin(currentTime * 2.0f) * 5.0f;
    float fade = (sin(currentTime * 3.0f) + 1.0f) / 2.0f;

    // Draw main message only if it's not empty
    if (strlen(mainMessage) > 0) {
        int mainTextWidth = MeasureText(mainMessage, MAIN_FONT_SIZE);
        int mainX = (SCREEN_WIDTH - mainTextWidth) / 2;
        DrawText(mainMessage, mainX, 200 + (int)bounce, MAIN_FONT_SIZE,
                 (Color){255, (unsigned char)(255 * fade), 100, 255});
    }

    // Draw sub message only if it's not empty
    if (strlen(subMessage) > 0) {
        int subTextWidth = MeasureText(subMessage, SUB_FONT_SIZE);
        int subX = (SCREEN_WIDTH - subTextWidth) / 2;
        DrawText(subMessage, subX, 280, SUB_FONT_SIZE,
                 (Color){255, 255, 255, 255});
    }

    // Draw third message only if it's not empty
    if (strlen(thirdMessage) > 0) {
        int thirdTextWidth = MeasureText(thirdMessage, THIRD_FONT_SIZE);
        int thirdX = (SCREEN_WIDTH - thirdTextWidth) / 2;
        DrawText(thirdMessage, thirdX, 320, THIRD_FONT_SIZE,
                 (Color){200, 200, 255, 255});
    }
}
