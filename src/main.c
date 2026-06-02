#include "raylib.h"
#include "menu.h"

// estados do jogo
typedef enum TelaAtual { 
    TELA_MENU, 
    TELA_JOGO, 
    TELA_PAUSA, 
    TELA_RANKING 
} TelaAtual;

int main(void)
{
    // inicializa a janela
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Donkey Kong INF (DKINF)");
    SetTargetFPS(60); 


    TelaAtual estadoAtual = TELA_MENU;
    int sairDoJogo = 0;
    int opcaoSelecionadaMenu = 0; 
    int faseAtual = 1;


    //loop principal
    while (!WindowShouldClose() && !sairDoJogo)
    {
        // Att da lógica
        switch (estadoAtual)
        {
            case TELA_MENU:
                // O main apenas deteta as teclas e atualiza o índice da opção focada
                if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) opcaoSelecionadaMenu = (opcaoSelecionadaMenu + 1) % 3;
                if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) opcaoSelecionadaMenu = (opcaoSelecionadaMenu - 1 + 3) % 3;

                if (IsKeyPressed(KEY_ENTER)) {
                    if (opcaoSelecionadaMenu == 0) {
                        faseAtual = 1;
                        CarregarMapa();
                        estadoAtual = TELA_JOGO;
                    } 
                    else if (opcaoSelecionadaMenu == 1) {
                        estadoAtual = TELA_RANKING;
                    } 
                    else if (opcaoSelecionadaMenu == 2) {
                        sairDoJogo = 1;
                    }
                }
                break;

            case TELA_JOGO:
                // Atualização física das entidades
                AtualizarJogador(&jogador, mapa);
                AtualizarInimigos(listaInimigos, qtdInimigos, mapa);

                // Verificação de colisões e condições de jogo
                if (ChecarColisaoJogadorInimigos(&jogador, listaInimigos, qtdInimigos)) {
                    CarregarMapa("mapa1.txt", mapa, &jogador, listaInimigos, &qtdInimigos);
                }

                if (JogadorAlcancouSaida(&jogador, mapa)) {
                    faseAtual++;
                  
                }

                if (IsKeyPressed(KEY_TAB)) {
                    estadoAtual = TELA_PAUSA;
                }
                break;

            case TELA_PAUSA:
                // Detecta o comando para sair do estado de pausa
                if (IsKeyPressed(KEY_TAB)) {
                    estadoAtual = TELA_JOGO;
                }
                break;

            case TELA_RANKING:
                if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE)) {
                    estadoAtual = TELA_MENU;
                }
                break;
        }

        //renderização
        BeginDrawing();
        ClearBackground(BLACK);

        switch (estadoAtual)
        {
            case TELA_MENU:
                DesenharMenuPrincipal(opcaoSelecionadaMenu);
                break;

            case TELA_JOGO:
                DesenharCenario(mapa);
                DesenharJogador(&jogador);
                DesenharInimigos(listaInimigos, qtdInimigos);
                
                DrawText(TextFormat("FASE: %d", faseAtual), 20, 20, 20, RAYWHITE);
                break;

            case TELA_PAUSA:
                DesenharCenario(mapa); 
                DesenharMenuPausa();   
                break;

            case TELA_RANKING:
                break;
        }

        EndDrawing();
    }


    CloseWindow(); 
    return 0;
}