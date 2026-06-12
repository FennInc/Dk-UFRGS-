#include "raylib.h"
#include "menu.h"

void DesenharMenuPrincipal(int opcaoFocada, int screenWidth, int screenHeight) {

    Image logo = LoadImage("resources/logo_DK.png"); 
    Texture2D texture = LoadTextureFromImage(logo);
    UnloadImage(logo);

    int logoX = screenWidth/2 - texture.width/2;
    int logoY = screenHeight/8;
    DrawTexture(texture, logoX, logoY, WHITE);

    const char *textoNovoJogo = (opcaoFocada == 0) ? "> NOVO JOGO" : "NOVO JOGO";
    const char *textoRanking = (opcaoFocada == 1) ? "> RANKING" : "RANKING";
    const char *textoSair = (opcaoFocada == 2) ? "> SAIR" : "SAIR";

    int linhaInicialY = screenHeight/2;
    int espacoEntreLinhas = 60;

    DrawText(textoNovoJogo, screenWidth/2 - MeasureText(textoNovoJogo, 30)/2, linhaInicialY, 30,
             (opcaoFocada == 0) ? YELLOW : RAYWHITE);
    DrawText(textoRanking, screenWidth/2 - MeasureText(textoRanking, 30)/2, linhaInicialY + espacoEntreLinhas, 30,
             (opcaoFocada == 1) ? YELLOW : RAYWHITE);
    DrawText(textoSair, screenWidth/2 - MeasureText(textoSair, 30)/2, linhaInicialY + espacoEntreLinhas*2, 30,
             (opcaoFocada == 2) ? YELLOW : RAYWHITE);
    
    DrawText("Use as Setas para navegar e ENTER para confirmar",
             screenWidth/2 - MeasureText("Use as Setas para navegar e ENTER para confirmar", 20)/2,
             screenHeight - 80, 20, DARKGRAY);
}

void DesenharMenuPausa(int opcaoFocada, int screenWidth, int screenHeight) {
    const char *textoContinuar = (opcaoFocada == 0) ? "> CONTINUAR" : "CONTINUAR";
    const char *textoMenu = (opcaoFocada == 1) ? "> MENU" : "MENU";
    const char *textoSair = (opcaoFocada == 2) ? "> SAIR" : "SAIR";

    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.6f));
    DrawText("PAUSA", screenWidth/2 - MeasureText("PAUSA", 40)/2, screenHeight/4, 40, YELLOW);

    int linhaInicialY = screenHeight/2 - 40;
    int espacoEntreLinhas = 60;

    DrawText(textoContinuar, screenWidth/2 - MeasureText(textoContinuar, 30)/2, linhaInicialY, 30,
             (opcaoFocada == 0) ? YELLOW : RAYWHITE);
    DrawText(textoMenu, screenWidth/2 - MeasureText(textoMenu, 30)/2, linhaInicialY + espacoEntreLinhas, 30,
             (opcaoFocada == 1) ? YELLOW : RAYWHITE);
    DrawText(textoSair, screenWidth/2 - MeasureText(textoSair, 30)/2, linhaInicialY + espacoEntreLinhas*2, 30,
             (opcaoFocada == 2) ? YELLOW : RAYWHITE);

    DrawText("Use Seta / W-S para trocar e ENTER para confirmar",
             screenWidth/2 - MeasureText("Use Seta / W-S para trocar e ENTER para confirmar", 20)/2,
             screenHeight - 80, 20, DARKGRAY);
}