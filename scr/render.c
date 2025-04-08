#include "raylib.h"
#include <math.h>
#include "../include/config.h"

// Desenha as mensagens de aniversário na tela
void DrawBirthdayMessage(int screenWidth, int screenHeight) {
    // Configura o texto de "Feliz Aniversário"
    const char* text = MAIN_TEXT;
    const char* text2 = SECONDARY_TEXT;

    int fontSize = MAIN_FONT_SIZE;
    int fontSize2 = SECONDARY_FONT_SIZE;
    int textWidth = MeasureText(text, fontSize);
    int textWidth2 = MeasureText(text2, fontSize2);

    // Sombra do primeiro texto
    DrawText(
        text,
        screenWidth/2 - textWidth/2 + 3,
        screenHeight/2 - 30 + 3,
        fontSize,
        BLACK
    );

    // Primeiro texto com cor pulsante baseada no tempo
    float time = GetTime();
    Color textColor = (Color){
        (unsigned char)(255 * fabs(sin(time * 0.5f))),
        (unsigned char)(255 * fabs(sin(time * 0.3f + 2))),
        (unsigned char)(255 * fabs(sin(time * 0.2f + 4))),
        255
    };

    DrawText(
        text,
        screenWidth/2 - textWidth/2,
        screenHeight/2 - 30,
        fontSize,
        textColor
    );

    // Sombra do segundo texto
    DrawText(
        text2,
        screenWidth/2 - textWidth2/2 + 2,
        screenHeight/2 + 40 + 2,
        fontSize2,
        BLACK
    );

    // Segundo texto com cor pulsante (ligeiramente defasada)
    Color textColor2 = (Color){
        (unsigned char)(255 * fabs(sin(time * 0.5f + 1))),
        (unsigned char)(255 * fabs(sin(time * 0.3f + 3))),
        (unsigned char)(255 * fabs(sin(time * 0.2f + 5))),
        255
    };

    DrawText(
        text2,
        screenWidth/2 - textWidth2/2,
        screenHeight/2 + 40,
        fontSize2,
        textColor2
    );
}