#ifndef MAPA_H
#define MAPA_H
#include "entidades.h"



void CarregarMapa(const char *nomeArquivo, char mapa[30][30], Jogador *jogador, Inimigo listaInimigos[], int *qtdInimigos);


void DesenharCenario(char mapa[30][30]);

#endif