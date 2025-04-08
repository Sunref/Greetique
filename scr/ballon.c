#include "../include/balloon.h"
#include <math.h>

// Inicializa os balões com posições e cores aleatórias
void InitBalloons(Balloon balloons[], int maxBalloons, int screenWidth, int screenHeight) {
    for (int i = 0; i < maxBalloons; i++) {
        balloons[i].position.x = GetRandomValue(50, screenWidth - 50);
        balloons[i].position.y = GetRandomValue(screenHeight, screenHeight + 300);
        balloons[i].radius = GetRandomValue(20, 40);
        balloons[i].speed = GetRandomValue(1, 3);

        // Cores aleatórias vibrantes para os balões
        int colorIndex = GetRandomValue(0, 3);
        switch (colorIndex) {
            case 0: balloons[i].color = GREEN; break;
            case 1: balloons[i].color = PURPLE; break;
            case 2: balloons[i].color = BLUE; break;
            case 3: balloons[i].color = PINK; break;
        }
    }
}

// Atualiza a posição dos balões
void UpdateBalloons(Balloon balloons[], int maxBalloons, int screenHeight) {
    for (int i = 0; i < maxBalloons; i++) {
        balloons[i].position.y -= balloons[i].speed;

        // Mover levemente para os lados (efeito flutuante)
        balloons[i].position.x += sin(GetTime() + i) * 0.5f;

        // Se o balão sair da tela, reposicionar abaixo
        if (balloons[i].position.y < -balloons[i].radius * 2) {
            balloons[i].position.y = screenHeight + balloons[i].radius;
            balloons[i].position.x = GetRandomValue(50, screenHeight - 50);
        }
    }
}

// Desenha os balões na tela
void DrawBalloons(Balloon balloons[], int maxBalloons) {
    for (int i = 0; i < maxBalloons; i++) {
        // Desenhar o balão (oval)
        DrawEllipse(
            balloons[i].position.x,
            balloons[i].position.y,
            balloons[i].radius,
            balloons[i].radius * 1.3f,
            balloons[i].color
        );

        // Desenhar o brilho no balão
        DrawEllipse(
            balloons[i].position.x - balloons[i].radius * 0.3f,
            balloons[i].position.y - balloons[i].radius * 0.3f,
            balloons[i].radius * 0.2f,
            balloons[i].radius * 0.2f,
            WHITE
        );

        // Desenhar o fio do balão
        DrawLine(
            balloons[i].position.x,
            balloons[i].position.y + balloons[i].radius * 1.3f,
            balloons[i].position.x + sin(GetTime() * 2 + i) * 10,
            balloons[i].position.y + balloons[i].radius * 1.3f + 30,
            WHITE
        );
    }
}