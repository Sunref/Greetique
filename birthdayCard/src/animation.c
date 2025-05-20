#include "animation.h"
#include "../include/config.h"
#include <math.h>

// Draw birthday message with animated color effects
void DrawAnimatedText(float time) {
    // Calculate text widths for centering
    int textWidth = MeasureText(MAIN_MESSAGE, MAIN_FONT_SIZE);
    int textWidth2 = MeasureText(SUB_MESSAGE, SUB_FONT_SIZE);
    int textWidth3 = MeasureText(THIRD_MESSAGE, THIRD_FONT_SIZE);

    // Generate pulsating colors based on time
    Color textColor = (Color){
        (unsigned char)(255 * fabs(sin(time * 0.5f))),
        (unsigned char)(255 * fabs(sin(time * 0.3f + 2))),
        (unsigned char)(255 * fabs(sin(time * 0.2f + 4))),
        255
    };

    Color textColor2 = (Color){
        (unsigned char)(255 * fabs(sin(time * 0.5f + 1))),
        (unsigned char)(255 * fabs(sin(time * 0.3f + 3))),
        (unsigned char)(255 * fabs(sin(time * 0.2f + 5))),
        255
    };

    Color textColor3 = (Color){
        (unsigned char)(255 * fabs(sin(time * 0.5f + 1))),
        (unsigned char)(255 * fabs(sin(time * 0.3f + 3))),
        (unsigned char)(255 * fabs(sin(time * 0.2f + 5))),
        255
    };

    // Draw main message with shadow
    DrawText(
        MAIN_MESSAGE,
        SCREEN_WIDTH/2 - textWidth/2 + 3,
        SCREEN_HEIGHT/2 - 30 + 3,
        MAIN_FONT_SIZE,
        BLACK
    );

    DrawText(
        MAIN_MESSAGE,
        SCREEN_WIDTH/2 - textWidth/2,
        SCREEN_HEIGHT/2 - 30,
        MAIN_FONT_SIZE,
        textColor
    );

    // Draw second message with shadow
    DrawText(
        SUB_MESSAGE,
        SCREEN_WIDTH/2 - textWidth2/2 + 2,
        SCREEN_HEIGHT/2 + 40 + 2,
        SUB_FONT_SIZE,
        BLACK
    );

    DrawText(
        SUB_MESSAGE,
        SCREEN_WIDTH/2 - textWidth2/2,
        SCREEN_HEIGHT/2 + 40,
        SUB_FONT_SIZE,
        textColor2
    );

    // Draw third message with shadow
    DrawText(
        THIRD_MESSAGE,
        SCREEN_WIDTH/2 - textWidth3/2 + 2,
        SCREEN_HEIGHT/2 + 80 + 2,
        THIRD_FONT_SIZE,
        BLACK
    );

    DrawText(
        THIRD_MESSAGE,
        SCREEN_WIDTH/2 - textWidth3/2,
        SCREEN_HEIGHT/2 + 80,
        THIRD_FONT_SIZE,
        textColor3
    );
}
