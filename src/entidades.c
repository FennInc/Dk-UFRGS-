#include "raylib.h"
#include "entidades.h"

// ---------------------------------------------------------------------------
// 1. INICIALIZAÇÃO E LÓGICA DO JOGADOR
// ---------------------------------------------------------------------------

void InicializarJogador(Jogador *j, int linhaInicial, int colunaInicial) {
    j->pos.linha = linhaInicial;
    j->pos.coluna = colunaInicial;
    j->estado = ATIVO;
    j->tempo = 0;
}

void AtualizarMovimentoJogador(Jogador *j, char mapa[30][30]) {
    if (j->estado == MORTO) return;

    int l = j->pos.linha;
    int c = j->pos.coluna;
    char blocoAtual = mapa[l][c];
    char blocoAbaixo = (l < 29) ? mapa[l+1][c] : ' ';

    // -- MOVIMENTO HORIZONTAL --
    // O movimento horizontal só é permitido quando houver uma plataforma (Z) 
    // imediatamente abaixo da posição atual do jogador
    if (blocoAbaixo == 'Z' || blocoAtual == 'D' || blocoAtual == 'S') {
        // Usa IsKeyPressed para mover um bloco por clique (estilo grid/puzzle)
        if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && c < 29) {
            j->pos.coluna++;
        }
        else if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && c > 0) {
            j->pos.coluna--;
        }
    }

    // -- MOVIMENTO VERTICAL (ESCADAS) --
    // Solução de teletransporte (Requisito mínimo do trabalho)
    if (blocoAtual == 'S' && (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))) {
        // Procura a primeira ocorrência de 'D' acima na mesma coluna
        //não querendo ser chereta, mas eu mudei o for para um while, assim n precisa usar break aqui
        int i = l - 1;
        int encontrou = 0;
        while (i >= 0 && encontrou == 0) {
            if (mapa[i][c] == 'D') {
                j->pos.linha = i;
                encontrou = 1;
            }
            i--;
        }
    }
    else if (blocoAtual == 'D' && (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))) {
        // Procura a primeira ocorrência de 'S' abaixo na mesma coluna
        //aqui tbm mudei
        int i = l + 1;
        int encontrou = 0;
        while (i < 30 && encontrou == 0) {
            if (mapa[i][c] == 'S') {
                j->pos.linha = i;
                encontrou = 1;
            }
            i++;
        }
    }
}

// ---------------------------------------------------------------------------
// 2. LÓGICA DOS INIMIGOS
// ---------------------------------------------------------------------------

// Variável global (apenas neste arquivo) para controlar a velocidade dos inimigos
int frameCounterInimigos = 0;

void AtualizarInimigos(Inimigo listaInimigos[], int qtdInimigos, char mapa[30][30]) {
    frameCounterInimigos++;
    
    // Atualiza a posição dos inimigos a cada 15 frames (aprox. 4 movimentos por segundo)
    if (frameCounterInimigos >= 15) {
        frameCounterInimigos = 0;

        for (int i = 0; i < qtdInimigos; i++) {
            int l = listaInimigos[i].pos.linha;
            int c = listaInimigos[i].pos.coluna;

            if (listaInimigos[i].direcao == DIREITA) {
                // Inimigo anda se houver chão ('Z') na próxima coluna e não for o limite da tela
                if (c < 29 && mapa[l+1][c+1] == 'Z') {
                    listaInimigos[i].pos.coluna++;
                } else {
                    listaInimigos[i].direcao = ESQUERDA; // Bateu no limite, inverte a direção
                }
            } 
            else if (listaInimigos[i].direcao == ESQUERDA) {
                if (c > 0 && mapa[l+1][c-1] == 'Z') {
                    listaInimigos[i].pos.coluna--;
                } else {
                    listaInimigos[i].direcao = DIREITA;
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------
// 3. SISTEMA DE COLISÕES E OBJETIVOS
// ---------------------------------------------------------------------------

int ChecarColisaoJogadorInimigos(Jogador *j, Inimigo listaInimigos[], int qtdInimigos) {
    for (int i = 0; i < qtdInimigos; i++) {
        if (j->pos.linha == listaInimigos[i].pos.linha && 
            j->pos.coluna == listaInimigos[i].pos.coluna) {
            
            j->estado = MORTO;
            return 1;
        }
    }
    return 0;
}

int JogadorAlcancouSaida(Jogador *j, char mapa[30][30]) {
    // Retorna verdadeiro se o jogador estiver pisando na célula 'F'
    return (mapa[j->pos.linha][j->pos.coluna] == 'F');
}

// ---------------------------------------------------------------------------
// 4. RENDERIZAÇÃO DAS ENTIDADES
// ---------------------------------------------------------------------------

void DesenharJogador(Jogador *j) {
    if (j->estado == MORTO) return;

    int tamanhoTile = 20;
    int offsetX = 100; // O mesmo offset usado no mapa.c para manter alinhado
    int offsetY = 40;

    int posX = offsetX + (j->pos.coluna * tamanhoTile);
    int posY = offsetY + (j->pos.linha * tamanhoTile);

    // Desenha o jogador como um quadrado verde (ou aplique spritesheet depois)
    DrawRectangle(posX, posY, tamanhoTile, tamanhoTile, GREEN);
}

void DesenharInimigos(Inimigo listaInimigos[], int qtdInimigos) {
    int tamanhoTile = 20;
    int offsetX = 100;
    int offsetY = 40;

    for (int i = 0; i < qtdInimigos; i++) {
        int posX = offsetX + (listaInimigos[i].pos.coluna * tamanhoTile);
        int posY = offsetY + (listaInimigos[i].pos.linha * tamanhoTile);

        // Desenha o inimigo como um quadrado vermelho
        DrawRectangle(posX, posY, tamanhoTile, tamanhoTile, RED);
    }
}