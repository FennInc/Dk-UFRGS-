#include <stdio.h>
#include "raylib.h"
#include "mapa.h"

// Lê e processa o mapa
void CarregarMapa(const char *nomeArquivo, char mapa[30][30], Jogador *jogador, Inimigo listaInimigos[], int *qtdInimigos) {
    
    for (int l = 0; l < 30; l++) {
        for (int c = 0; c < 30; c++) {
            mapa[l][c] = ' ';
        }
    }

  
    FILE *arquivo = fopen(nomeArquivo, "r");
    
    // tratamento de erro caso não ache o arquivo
    if (arquivo == NULL) {
        printf("ERRO: Nao foi possivel abrir o arquivo %s!\n", nomeArquivo);
        return; 
    }

    *qtdInimigos = 0; // Zera para não sobrar do mapa anterior

    
    for (int linha = 0; linha < 30; linha++) {
        for (int coluna = 0; coluna < 30; coluna++) {
            
            // Pega caractere por caractere
            int ch = fgetc(arquivo);
            
            // Ignora quebras de linha
            while (ch == '\n' || ch == '\r') {
                ch = fgetc(arquivo);
            }
            
            // Se o arquivo acabar antes do esperado, interrompe a leitura
            if (ch == EOF) break;

            // Define onde as entidades nascem e limpa o cenário atrás delas
            if (ch == 'P') {
                InicializarJogador(jogador, linha, coluna);
            } 
            else if (ch == 'E') {
                // tratamento para não passar do limite de inimigos
                if (*qtdInimigos < 10) {
                    listaInimigos[*qtdInimigos].pos.linha = linha;
                    listaInimigos[*qtdInimigos].pos.coluna = coluna;
                    listaInimigos[*qtdInimigos].direcao = ESQUERDA;
                    (*qtdInimigos)++;
                }
                mapa[linha][coluna] = ' '; // o espaço do inimigo fica vazio dps de posto
            } 
            // Se for os outros caracteres salva na matriz
            else {
                mapa[linha][coluna] = (char)ch;
            }
        }
    }

    fclose(arquivo);
}

// renderização do cenário.
void DesenharCenario(char mapa[30][30]) {
    // 640 pixels de altura, 30x20 = 600 para o mapa, 40 para a HUD.
    int tamanhoTile = 20; 
    
    // centraliza o mapa na tela.
    int offsetX = 100;
    int offsetY = 40;

    for (int linha = 0; linha < 30; linha++) {
        for (int coluna = 0; coluna < 30; coluna++) {
            
            char bloco = mapa[linha][coluna];
            
            // Calcula as coordenadas X e Y reais na tela em pixels
            int posX = offsetX + (coluna * tamanhoTile);
            int posY = offsetY + (linha * tamanhoTile);

            // Usa as funções de desenho baseadas no caractere
            if (bloco == 'Z') {
                // plataforma azul
                DrawRectangle(posX, posY, tamanhoTile, tamanhoTile, DARKBLUE);
            } 
            else if (bloco == 'S' || bloco == 'H') {
                // Escadas
                DrawRectangle(posX + 5, posY, 10, tamanhoTile, BROWN);
            } 
            else if (bloco == 'F') {
                // Final da fase
                DrawRectangle(posX, posY, tamanhoTile, tamanhoTile, GOLD);
            }
        }
    }
}