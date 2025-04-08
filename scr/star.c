#include "../include/star.h"
#include <math.h>

// Inicializa as estrelas com posições e propriedades aleatórias
void InitStars(Star stars[], int maxStars, int screenWidth, int screenHeight) {
    for (int i = 0; i < maxStars; i++) {
        stars[i].position.x = GetRandomValue(0, screenWidth);
        stars[i].position.y = GetRandomValue(0, screenHeight);
        stars[i].radius = GetRandomValue(5, 15);
        stars[i].rotation = GetRandomValue(0, 360);
        stars[i].rotationSpeed = GetRandomValue(1, 5) * 0.01f;
        stars[i].scale = GetRandomValue(80, 120) * 0.01f;
        stars[i].scaleSpeed = GetRandomValue(1, 5) * 0.01f;

        // Cores aleatórias para as estrelas
        stars[i].color = (Color){
            GetRandomValue(200, 255),
            GetRandomValue(200, 255),
            GetRandomValue(100, 255),
            255
        };
    }
}

// Atualiza as propriedades das estrelas (rotação, escala)
void UpdateStars(Star stars[], int maxStars) {
    for (int i = 0; i < maxStars; i++) {
        stars[i].rotation += stars[i].rotationSpeed;
        stars[i].scale += stars[i].scaleSpeed * sin(GetTime() * 2 + i);

        // Manter a escala dentro de um intervalo razoável
        if (stars[i].scale < 0.8f || stars[i].scale > 1.2f) {
            stars[i].scaleSpeed *= -1;
        }
    }
}

// Desenha as estrelas na tela
void DrawStars(Star stars[], int maxStars) {
    for (int i = 0; i < maxStars; i++) {
        // Desenhar uma estrela de 5 pontas
        float angle = 0;
        float outerRadius = stars[i].radius * stars[i].scale;
        float innerRadius = outerRadius * 0.4f;

        for (int j = 0; j < 10; j++) {
            float radius = j % 2 == 0 ? outerRadius : innerRadius;
            float x1 = stars[i].position.x + cos(angle + stars[i].rotation) * radius;
            float y1 = stars[i].position.y + sin(angle + stars[i].rotation) * radius;

            angle += PI / 5.0f;
            float x2 = stars[i].position.x + cos(angle + stars[i].rotation) * radius;
            float y2 = stars[i].position.y + sin(angle + stars[i].rotation) * radius;

            DrawLineEx((Vector2){x1, y1}, (Vector2){x2, y2}, 2.0f, stars[i].color);
        }
    }
}