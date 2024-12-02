#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define tamCampo 5
#define tamCelula 40

int M[tamCampo][tamCampo];

// Dimensões da janela
static const int screenWidth = 1000;
static const int screenHeight = 1000;

void preencheCampo(){

    int i;
    int j;

     for (int i = 0; i < tamCampo; i++) {
        for (int j = 0; j < tamCampo; j++) {
            //if (verificaCoordenadas(i, j) && M[i][j] != Bomba) verificaVizinhos(i, j);
            M[i][j] = 2;
        }
     }

}

// Função para desenhar a tela inicial (incluindo a bomba)
void DrawWelcomeScreen(Vector2 bombPosition) {
    BeginDrawing();
        ClearBackground(PURPLE);

        // Mensagem de boas-vindas
        DrawText("B E M     V I N D O      A O     C A M P O     M I N A D O!", screenWidth/4, screenHeight/10, 20, BLACK);

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
        DrawText("Pressione ENTER para começar", screenWidth/2.85, screenHeight - 2.75 * (screenHeight/4), 20, BLACK);

    EndDrawing();
}

// Função para desenhar o jogo (uma tela futura caso necessário)
void DrawGameScreen() {

    float startTime = GetTime();
    int deslocamento_x = (screenWidth - (tamCampo * tamCelula)) / 2;
    int deslocamento_y = (screenHeight - (tamCampo * tamCelula)) / 2;

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

        // Percorre a matriz para desenhar os quadrados
        for (int i = 0; i < tamCampo; i++) {
            for (int j = 0; j < tamCampo; j++) {
                // Calcula posição na tela
                int x = deslocamento_x + j * tamCelula;
                int y = deslocamento_y + i * tamCelula;

                // Determina a cor com base no valor da matriz
                Color cor = (M[i][j] == 1) ? BLACK : WHITE;

                // Desenha o quadrado
                DrawRectangle(x, y, tamCelula, tamCelula, cor);

                // Desenha bordas para separação (opcional)
                DrawRectangleLines(x, y, tamCelula, tamCelula, GRAY);
            }
        }

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
