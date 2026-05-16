#include "raylib.h"
#include "menu.h" // Interface com o arquivo menu.c onde o menu será desenhado

int main(void)
{
    //Inicializa a janela
    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Donkey Kong INF (DKINF)");
    SetTargetFPS(60); //Define o fps

    // Variável da opção do menu
    int opcaoSelecionadaMenu = 0;

    //Loop principal
    while (!WindowShouldClose())
    {
        //Lógica de navegação do menu.
        
        // Move para baixo na lista de opções
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
            opcaoSelecionadaMenu = (opcaoSelecionadaMenu + 1) % 3;
        }
        
        // Move para cima na lista de opções
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
            opcaoSelecionadaMenu = (opcaoSelecionadaMenu - 1 + 3) % 3;
        }

        // Renderização
        BeginDrawing();
        ClearBackground(BLACK); // Limpa o frame anterior com a cor preta

       //Rnderiza o menu principal
        DesenharMenuPrincipal(opcaoSelecionadaMenu, screenWidth, screenHeight);

        EndDrawing();
    }

   // fecha a janela
    CloseWindow(); // Fecha o contexto da Raylib graciosamente
    return 0;
}