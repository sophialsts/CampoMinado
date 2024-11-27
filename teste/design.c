#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// Dimensões da janela
static const int screenWidth = 800;
static const int screenHeight = 450;

// Função para desenhar a tela inicial (incluindo a bomba)
void DrawWelcomeScreen(Vector2 bombPosition) {
    BeginDrawing();
        ClearBackground(PURPLE);

        // Mensagem de boas-vindas
        DrawText("B E M     V I N D O      A O     C A M P O     M I N A D O!", 100, 100, 20, BLACK);

        // Desenho da bomba
        DrawCircleV(bombPosition, 50, BLACK);                            // Corpo da bomba
        DrawLine(bombPosition.x + 15, bombPosition.y - 55, bombPosition.x + 25, bombPosition.y - 67, WHITE); // Pavio
        DrawLine(bombPosition.x + 16, bombPosition.y - 55, bombPosition.x + 26, bombPosition.y - 67, WHITE); // Pavio
        DrawCircle(bombPosition.x + 30, bombPosition.y - 70, 3, RED); 
        DrawCircle(bombPosition.x + 30, bombPosition.y - 74, 2, RED);
        DrawCircle(bombPosition.x + 30, bombPosition.y - 76, 1, RED);
        DrawCircle(bombPosition.x + 32, bombPosition.y - 73, 2, YELLOW); 
        DrawCircle(bombPosition.x + 32, bombPosition.y - 74, 2, YELLOW);
        DrawCircle(bombPosition.x + 32, bombPosition.y - 76, 1, YELLOW);         // Faísca

        // Instrução para começar
        DrawText("Pressione ENTER para começar", 250, 300, 20, BLACK);

    EndDrawing();
}

// Função para desenhar o jogo (uma tela futura caso necessário)
void DrawGameScreen() {

    float startTime = GetTime();

    while (!WindowShouldClose()) {
        // Calcula o tempo decorrido
        float elapsedTime = GetTime() - startTime;

        // Converte o tempo para texto
        char timeText[50];
        sprintf(timeText, "Your time: %.2f seconds", elapsedTime);

        // Início do desenho
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Exibe o tempo no topo da tela
            DrawText(timeText, 10, 10, 20, DARKGRAY);

            // Simulação de outras partes do jogo
            DrawText("Aqui vai o tabuleiro do Campo Minado!", 200, 200, 20, BLACK);
        EndDrawing();
    }
}

int main() {
    // Inicializa a janela
    InitWindow(screenWidth, screenHeight, "Campo Minado");

    // Define a posição da bomba
    Vector2 bombPosition = { screenWidth / 2.0f, 215 }; // Posição ajustada para ficar entre os textos

    // Estado inicial do programa (0 = tela inicial, 1 = jogo ativo)
    int gameState = 0;

    // Loop principal
    while (!WindowShouldClose()) {
        if (gameState == 0) {
            // Tela inicial (desenha bomba e textos)
            DrawWelcomeScreen(bombPosition);

            // Se o usuário pressionar ENTER, muda para o jogo
            if (IsKeyPressed(KEY_ENTER)) {
                gameState = 1;
            }
        } else if (gameState == 1) {
            // Tela do jogo (ou outra funcionalidade)
            DrawGameScreen();
        }
    }

    // Encerra e libera recursos
    CloseWindow();
    return 0;
}
