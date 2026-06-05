#include <stdio.h>
#include "raylib.h"
#include "menu.h"
#include "entidades.h"
#include "mapa.h"
#include "ranking.h"

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
    const int screenHeight = 640;
    InitWindow(screenWidth, screenHeight, "Donkey Kong INF (DKINF)");
    SetTargetFPS(60); 


    TelaAtual estadoAtual = TELA_MENU;
    int sairDoJogo = 0;
    int opcaoSelecionadaMenu = 0; 
    int faseAtual = 1;
    float tempoFase = 0.0f;

    char mapa[30][30]; 
    Jogador jogador;
    Inimigo listaInimigos[10]; 
    int qtdInimigos = 0;

    //loop principal
    while (!WindowShouldClose() && !sairDoJogo)
    {
        
        switch (estadoAtual)
        {
            case TELA_MENU:
                // detecta a tecla e atualiza a opção focada.
                if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) opcaoSelecionadaMenu = (opcaoSelecionadaMenu + 1) % 3;
                if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) opcaoSelecionadaMenu = (opcaoSelecionadaMenu - 1 + 3) % 3;

                if (IsKeyPressed(KEY_ENTER)) {
                    if (opcaoSelecionadaMenu == 0) {
                        faseAtual = 1;
                        tempoFase = 0.0f;
                        CarregarMapa("mapas/mapa1.txt", mapa, &jogador, listaInimigos, &qtdInimigos);
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
                tempoFase += GetFrameTime();
                // Atualização física das entidades
                AtualizarMovimentoJogador(&jogador, mapa);
                AtualizarInimigos(listaInimigos, qtdInimigos, mapa);

                // Verificação de colisões e condições de jogo
                if (ChecarColisaoJogadorInimigos(&jogador, listaInimigos, qtdInimigos)) {
                    char nomeFicheiro[30];
                    snprintf(nomeFicheiro, sizeof(nomeFicheiro), "mapas/mapa%d.txt", faseAtual);

                    CarregarMapa(nomeFicheiro, mapa, &jogador, listaInimigos, &qtdInimigos);
                }

               if (JogadorAlcancouSaida(&jogador, mapa)) {
                    faseAtual++;
    
                    // cria uma string com o nome do proximo mapa.
                    char nomeFicheiro[30];
                    snprintf(nomeFicheiro, sizeof(nomeFicheiro), "mapas/mapa%d.txt", faseAtual);

                // tenta abrir o próximo mapa para verficicar se ele existe.
                FILE *ficheiroTeste = fopen(nomeFicheiro, "r");
                if (ficheiroTeste != NULL) {
                fclose(ficheiroTeste);
        
                // Se o mapa existe, carrega o novo mapa
                CarregarMapa(nomeFicheiro, mapa, &jogador, listaInimigos, &qtdInimigos);
                } else {
                SalvarNovoRecorde(tempoFase);
        
                faseAtual = 1; // Reseta para próxima run
                estadoAtual = TELA_RANKING;
                }
            }

                if (IsKeyPressed(KEY_TAB)) {
                    estadoAtual = TELA_PAUSA;
                }
                break;

            case TELA_PAUSA:
                // TODO: menu de pausa ainda precisa ser implementado.
                // Detecta o comando para sair do estado de pausa
                if (IsKeyPressed(KEY_TAB)) {
                    estadoAtual = TELA_JOGO;
                }
                break;

            case TELA_RANKING:
                if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE)) {
                    estadoAtual = TELA_MENU;
                }
                AtualizarTelaRanking((int*)&estadoAtual);
                break;
        }

        //renderização
        BeginDrawing();
        ClearBackground(BLACK);

        switch (estadoAtual)
        {
            case TELA_MENU:
                DesenharMenuPrincipal(opcaoSelecionadaMenu, screenWidth, screenHeight);
                break;

            case TELA_JOGO:
                DesenharCenario(mapa);
                DesenharJogador(&jogador);
                DesenharInimigos(listaInimigos, qtdInimigos);
                
                // desenha a HUD com a fase e o tempo.
                DrawRectangle(0, 0, screenWidth, 40, Fade(BLACK, 0.8f));
                DrawText(TextFormat("FASE: %d", faseAtual), 20, 10, 20, RAYWHITE);
                DrawText(TextFormat("TEMPO: %.2f s", tempoFase), 200, 10, 20, YELLOW);
                break;

            case TELA_PAUSA:
                DesenharCenario(mapa); 
                DesenharMenuPausa();   
                break;

            case TELA_RANKING:
                DesenharTelaRanking();
                break;
        }

        EndDrawing();
    }


    CloseWindow(); 
    return 0;
}