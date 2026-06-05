#include <stdio.h>
#include "raylib.h"
#include "ranking.h"

void SalvarNovoRecorde(float tempoFinal) {
    // TODO: Receber o tempoFinal que veio do main.c
    // TODO: Criar lógica visual para o jogador digitaras 8 letras
    // TODO: Criar um RegistroPlacar com o nome e o tempo
    // TODO: Abrir o arquivo "placar.bin" em modo "ab" (append binário) e usar fwrite()
}

void AtualizarTelaRanking(int *estadoAtual) {
    // TODO: Adicionar lógica para sair do ranking e voltar ao menu. Se a pessoa apertar ENTER ou ESC, *estadoAtual volta para a TELA_MENU
}

void DesenharTelaRanking(void) {
    // TODO: Abrir o "placar.bin", ler os registros e desenhar na tela os melhores.
    
    // Rascunho
    DrawText("--- MELHORES TEMPOS ---", 200, 100, 30, GOLD);
    DrawText("(Tabela em construcao)", 200, 250, 20, RAYWHITE);
}