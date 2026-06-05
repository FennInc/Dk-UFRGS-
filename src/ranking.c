#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "ranking.h"


//usando static pra nao sair do escopo daqui, preciso controlar umas outras coisas
static int inserindoNome = 0;
static float tempoSalvar = 0;
static char nomeInput[9] = "\0";
static int letrasCount = 0;

void SalvarNovoRecorde(float tempoFinal) {
    tempoSalvar = tempoFinal;
    inserindoNome = 1;       //jaja explioc o pq disso
    nomeInput[0] = '\0';
    letrasCount = 0;
}

void AtualizarTelaRanking(int *estadoAtual) {
    // entao, tava tendo u bug que quando apertava o enter essa joça ia direto pro menu e quebrava, por isso aqui tah
    if (inserindoNome) {
        if (*estadoAtual == 0) { 
            *estadoAtual = 3;
        }

        // limpa buffer
        int chave = GetCharPressed();
        
        //pega letra
        while (chave > 0) {
            if ((chave >= 32 && chave <= 125) && (letrasCount < 8)) {
                nomeInput[letrasCount] = (char)chave;
                letrasCount++;
                nomeInput[letrasCount] = '\0';
            }
            chave = GetCharPressed(); 
        }

        // apaga letra
        if (IsKeyPressed(KEY_BACKSPACE) && letrasCount > 0) {
            letrasCount--;
            nomeInput[letrasCount] = '\0';
        }

        // GUARDAR ARQUIVO
        if (IsKeyPressed(KEY_ENTER) && letrasCount > 0) {
            RegistroPlacar topRecords[11];
            int totalRecords = 0;
            
            // abrindo arquivo
            FILE *f = fopen("placar.bin", "rb");
            if (f != NULL) {
                while (totalRecords < 10 && fread(&topRecords[totalRecords], sizeof(RegistroPlacar), 1, f) == 1) {
                    totalRecords++;
                }
                fclose(f);
            }

            // taca o recorde no fim do vetor, ja que o ultimo lugar vai ser mandado embora msm
            strcpy(topRecords[totalRecords].nome, nomeInput);
            topRecords[totalRecords].tempo = tempoSalvar;
            totalRecords++;

            // bubble sort :333333333333333333333333 foi uma desgraça pra fazer direito.
            int i = 0;
            while (i < totalRecords - 1) {
                int j = 0;
                while (j < totalRecords - i - 1) {
                    if (topRecords[j].tempo > topRecords[j + 1].tempo) {
                        RegistroPlacar aux = topRecords[j];
                        topRecords[j] = topRecords[j + 1];
                        topRecords[j + 1] = aux;
                    }
                    j++;
                }
                i++;
            }

            // decidi por 5, isso aq tbm preve pra nao dar problema e gravar lixo se n tiver 5 recordes
            f = fopen("placar.bin", "wb");
            if (f != NULL) {
                int k = 0;
                int limiteGravacao;
                if (totalRecords > 5) {
                    limiteGravacao = 5;
                } else {
                    limiteGravacao = totalRecords;
                }
                while (k < limiteGravacao) { //aritimetrica de ponteiros,,,,,,,,,,,,,,,,,
                    fwrite(topRecords + k, sizeof(RegistroPlacar), 1, f);
                    k++;
                }
                fclose(f);
            }

            inserindoNome = 0; 
        }
    }
}

void DesenharTelaRanking(void) {
    if (inserindoNome) {
        // TELA PARA DIGITAR NOME
        DrawText("NOVO RECORDE ALCANCADO!", 180, 150, 32, GOLD);
        DrawText(TextFormat("Tempo Total: %.2f segundos", tempoSalvar), 240, 210, 22, RAYWHITE);
        DrawText("Digite suas iniciais (Ate 8 letras):", 240, 280, 20, LIGHTGRAY);
        
        // CAIXA DE TEXTO
        DrawRectangle(250, 330, 300, 45, DARKGRAY);
        DrawRectangleLines(250, 330, 300, 45, GOLD);
        DrawText(nomeInput, 265, 340, 26, YELLOW);
        
        DrawText("Pressione ENTER para salvar o seu tempo", 215, 410, 18, GRAY);
    } 
    else {
        // PLACAR DE TEMPOS
        DrawText("--- OS MELHORES TEMPOS ---", 190, 80, 32, GOLD);
        
        FILE *f = fopen("placar.bin", "rb");
        int linhaY = 180;
        int posicao = 1;
        RegistroPlacar r;

        if (f == NULL) {
            DrawText("Nenhum recorde registrado ainda!", 220, 240, 20, GRAY);
        } else {
            while (fread(&r, sizeof(RegistroPlacar), 1, f) == 1) {
                // DESENHA A LINHA BONITINHA DE CADA NOME
                DrawText(TextFormat("%d.  %-8s   ...................   %.2fs", posicao, r.nome, r.tempo), 220, linhaY, 24, RAYWHITE);
                linhaY += 50;
                posicao++;
            }
            fclose(f);
        }
        
        DrawText("Pressione ENTER para voltar ao Menu", 200, 540, 18, GRAY);
    }
}