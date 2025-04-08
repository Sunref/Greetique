//Feito por Fernanda com ajuda da IA Claude (não sei usar raylib direito)

#include "raylib.h"
#include <math.h>

#define MAX_BALLOONS 20
#define MAX_STARS 50

typedef struct {
    Vector2 position;
    float radius;
    Color color;
    float speed;
} Balloon;

typedef struct {
    Vector2 position;
    float radius;
    Color color;
    float rotation;
    float rotationSpeed;
    float scale;
    float scaleSpeed;
} Star;

int main() {
    // Inicialização da janela
    const int screenWidth = 1000;
    const int screenHeight = 850;
    InitWindow(screenWidth, screenHeight, "Feliz Aniversário!");

    // Configuração da taxa de FPS
    SetTargetFPS(60);

    // Inicialização dos balões
    Balloon balloons[MAX_BALLOONS];
    for (int i = 0; i < MAX_BALLOONS; i++) {
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

    // Inicialização das estrelas
    Star stars[MAX_STARS];
    for (int i = 0; i < MAX_STARS; i++) {
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

    // Loop principal
    while (!WindowShouldClose()) {

        // Atualizar posição dos balões
        for (int i = 0; i < MAX_BALLOONS; i++) {
            balloons[i].position.y -= balloons[i].speed;

            // Mover levemente para os lados (efeito flutuante)
            balloons[i].position.x += sin(GetTime() + i) * 0.5f;

            // Se o balão sair da tela, reposicionar abaixo
            if (balloons[i].position.y < -balloons[i].radius * 2) {
                balloons[i].position.y = screenHeight + balloons[i].radius;
                balloons[i].position.x = GetRandomValue(50, screenWidth - 50);
            }
        }

        // Atualizar estrelas
        for (int i = 0; i < MAX_STARS; i++) {
            stars[i].rotation += stars[i].rotationSpeed;
            stars[i].scale += stars[i].scaleSpeed * sin(GetTime() * 2 + i);

            // Manter a escala dentro de um intervalo razoável
            if (stars[i].scale < 0.8f || stars[i].scale > 1.2f) {
                stars[i].scaleSpeed *= -1;
            }
        }

        // Desenhar
        BeginDrawing();
            ClearBackground((Color){ 25, 25, 50, 255 }); // Fundo azul escuro

            // Desenhar estrelas
            for (int i = 0; i < MAX_STARS; i++) {
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

            // Desenhar balões
            for (int i = 0; i < MAX_BALLOONS; i++) {
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

            // Desenhar o texto de "Feliz Aniversário"
            const char* text = "FELIZ ANIVERSÁRIO GABRIEL!!!";
            const char* text2 = "Que seu dia tenha sido incrível, eu amo você irmão <3";

            int fontSize = 50;
            int fontSize2 = 30;
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

        EndDrawing();
    }

    // Encerrar
    CloseWindow();
    return 0;
}
