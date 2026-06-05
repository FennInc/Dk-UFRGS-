#ifndef ENTIDADES_H
#define ENTIDADES_H


typedef struct Posicao {
    int linha;
    int coluna;
} Posicao;

typedef enum EstadoJogador {
    ATIVO,
    MORTO
} EstadoJogador;

typedef enum DirecaoMovimento {
    ESQUERDA,
    DIREITA
} DirecaoMovimento;


typedef struct Jogador {
    Posicao pos;
    int tempo;
    EstadoJogador estado;
} Jogador;

typedef struct Inimigo {
    Posicao pos;
    DirecaoMovimento direcao;
} Inimigo;



void InicializarJogador(Jogador *j, int linhaInicial, int colunaInicial);

void AtualizarMovimentoJogador(Jogador *j, char mapa[30][30]);

void AtualizarInimigos(Inimigo listaInimigos[], int qtdInimigos, char mapa[30][30]);

int ChecarColisaoJogadorInimigos(Jogador *j, Inimigo listaInimigos[], int qtdInimigos);

int JogadorAlcancouSaida(Jogador *j, char mapa[30][30]);

void DesenharJogador(Jogador *j);

void DesenharInimigos(Inimigo listaInimigos[], int qtdInimigos);

#endif