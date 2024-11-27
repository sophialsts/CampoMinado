#include "raylib.h"
#include <stdio.h> // Para usar sprintf

int main() {
    // Dimensões da janela
    const int screenWidth = 800;
    const int screenHeight = 450;

    // Inicializa a janela
    InitWindow(screenWidth, screenHeight, "Campo Minado - Cronômetro");

    // Variável para armazenar o tempo inicial do jogo
    float startTime = GetTime(); 

    // Loop principal
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
            DrawText("Aqui vai o tabuleiro do Campo Minado!", 150, 200, 20, BLACK);
        EndDrawing();
    }

    // Encerra a janela e libera recursos
    CloseWindow();

    return 0;
}
