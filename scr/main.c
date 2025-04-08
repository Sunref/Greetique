// Aniversário do meu mano Gabriel
// Feito por Fernanda com ajuda da IA Claude (não sei usar raylib direito)

#include "raylib.h"
#include "../include/config.h"
#include "../include/balloon.h"
#include "../include/star.h"

// Declaração da função de renderização de mensagem (implementada em render.c)
void DrawBirthdayMessage(int screenWidth, int screenHeight);

int main() {
    // Inicialização da janela
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    // Configuração da taxa de FPS
    SetTargetFPS(FPS);

    // Inicialização dos balões
    Balloon balloons[MAX_BALLOONS];
    InitBalloons(balloons, MAX_BALLOONS, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Inicialização das estrelas
    Star stars[MAX_STARS];
    InitStars(stars, MAX_STARS, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Loop principal
    while (!WindowShouldClose()) {
        // Atualizar posição dos balões
        UpdateBalloons(balloons, MAX_BALLOONS, SCREEN_HEIGHT);

        // Atualizar estrelas
        UpdateStars(stars, MAX_STARS);

        // Desenhar
        BeginDrawing();
            ClearBackground(BACKGROUND_COLOR); // Fundo azul escuro

            // Desenhar estrelas
            DrawStars(stars, MAX_STARS);

            // Desenhar balões
            DrawBalloons(balloons, MAX_BALLOONS);

            // Desenhar o texto de "Feliz Aniversário"
            DrawBirthdayMessage(SCREEN_WIDTH, SCREEN_HEIGHT);

        EndDrawing();
    }

    // Encerrar
    CloseWindow();
    return 0;
}