#ifndef RANKING_H
#define RANKING_H


typedef struct {
    char nome[9]; // 8 letras + \0
    float tempo;
} RegistroPlacar;

// Função chamada quando termina o jogo
void SalvarNovoRecorde(float tempoFinal);

// Função para atualizar a lógica da tela de ranking, estado atual passado por ponteiro para poder mandar de volta pra o menu.
void AtualizarTelaRanking(int *estadoAtual);

// Desenha a tela do ranking.
void DesenharTelaRanking(void);

#endif