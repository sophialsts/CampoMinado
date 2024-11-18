#include "raylib.h"

int main(void) {
    // Configuração da primeira janela
    const int screenWidth1 = 600; //largura
    const int screenHeight1 = 600; //altura
    InitWindow(screenWidth1, screenHeight1, "Tela de Início");

    // Loop de renderização para a primeira janela
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(PURPLE); //cor do fundo
        DrawText("Bem vindo ao Campo Minado!", 175, 280, 20, BLACK);
        EndDrawing();

        // Condição para fechar a primeira janela e abrir a segunda
        if (IsKeyPressed(KEY_ENTER)) {
            CloseWindow(); // Fecha a primeira janela
            break;         // Sai do loop da primeira janela
        }
    }

    // Configuração da segunda janela
    const int screenWidth2 = 600;
    const int screenHeight2 = 600;
    InitWindow(screenWidth2, screenHeight2, "Game");

    // Loop de renderização para a segunda janela
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(PURPLE);
        DrawText("aqui vai ter a mágica", 200, 290, 20, BLACK);
        DrawLine(18,42,screenWidth2 - 18, 42, BLACK);
        EndDrawing();

        // Condição para fechar a segunda janela
        if (IsKeyPressed(KEY_ESCAPE)) {
            CloseWindow(); // Fecha a segunda janela
            break;         // Sai do loop da segunda janela
        }
    }

    return 0;
}
