#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio2.h>
#include <windows.h>

#define LARGURA_TELA 80
#define ALTURA_TELA 30

typedef struct {
    char c;
    int cor;
} Pixel;

typedef struct {
    int x;
    int y;
} Posicao;

typedef struct {
    Posicao pos;
    float timer;

    int velX;
    int velY;

    int color;
} DVD;

typedef struct {
    Pixel tela[LARGURA_TELA][ALTURA_TELA];
    Pixel tela_anterior[LARGURA_TELA][ALTURA_TELA];

    DVD dvd;
} Jogo;

Jogo InicializaJogo();
void AtualizaJogo(Jogo* j, float deltaT);
void DesenhaJogo(Jogo* j);
float CalculaDeltaT();
void HideCursor();

int main() {
    srand(time(NULL));
    Jogo j = InicializaJogo();
    HideCursor();

    while (1) {
        AtualizaJogo(&j, CalculaDeltaT());
        DesenhaJogo(&j);
    }
}

float tempoAnterior = 0;
float CalculaDeltaT() {
    float tempoAtual = clock() / (float)CLOCKS_PER_SEC;

    float delta = tempoAtual - tempoAnterior;
    tempoAnterior = tempoAtual;

    return delta;
}

Jogo InicializaJogo() {
    int x, y;
    Jogo j;

    j.dvd.pos.x=5;
    j.dvd.pos.y=5;
    j.dvd.velX=1;
    j.dvd.velY=1;
    j.dvd.timer=0;

    j.dvd.color=WHITE;

    for(x=0; x < LARGURA_TELA; x++) {
        for(y=0; y < ALTURA_TELA; y++) {
            j.tela[x][y]=(Pixel) {' ', WHITE};
            j.tela_anterior[x][y]=(Pixel) {' ', WHITE};
        }
    }

    return j;
}

void AtualizaJogo(Jogo* j, float deltaT) {
    j->dvd.timer+=deltaT;
    int cores[] = {WHITE, BLUE, RED, CYAN, GREEN, MAGENTA, YELLOW, BROWN};

    int corSorteada=cores[rand() % 8];

    if(j->dvd.timer>=0.1) {
        j->dvd.pos.x += j->dvd.velX;
        j->dvd.pos.y += j->dvd.velY;
        j->dvd.timer-=0.1;


        if (j->dvd.pos.x >= LARGURA_TELA-3) {
            j->dvd.velX *= -1;
            j->dvd.pos.x = LARGURA_TELA-5;
            j->dvd.color = corSorteada;
        }

        if (j->dvd.pos.y >= ALTURA_TELA-1) {
            j->dvd.velY *= -1;
            j->dvd.pos.y = ALTURA_TELA-3;
            j->dvd.color = corSorteada;
        }

        if (j->dvd.pos.x <= 1) {
            j->dvd.velX *= -1;
            j->dvd.pos.x = 1;
            j->dvd.color = corSorteada;
        }

        if (j->dvd.pos.y <= 1) {
            j->dvd.velY *= -1;
            j->dvd.pos.y = 1;
            j->dvd.color = corSorteada;
        }
    }
}
void DesenhaJogo(Jogo* j) {
    int x, y;

    for(x=0; x < LARGURA_TELA; x++) {
        for(y=0; y < ALTURA_TELA; y++) {
            j->tela[x][y]=(Pixel) {' ', WHITE};
        }
    }

    for(x=0; x < LARGURA_TELA; x++){
        j->tela[x][0]=(Pixel) {'#', LIGHTGRAY};
        j->tela[x][ALTURA_TELA-1]=(Pixel) {'#', LIGHTGRAY};
    }
    for(y=0; y < ALTURA_TELA; y++) {
        j->tela[0][y]=(Pixel) {'#', LIGHTGRAY};
        j->tela[LARGURA_TELA-1][y]=(Pixel) {'#', LIGHTGRAY};
    }

    j->tela[j->dvd.pos.x][j->dvd.pos.y]=(Pixel) {'D', j->dvd.color};
    j->tela[j->dvd.pos.x + 1][j->dvd.pos.y]=(Pixel) {'V', j->dvd.color};
    j->tela[j->dvd.pos.x + 2][j->dvd.pos.y]=(Pixel) {'D', j->dvd.color};

     for(x=0; x < LARGURA_TELA; x++) {
        for(y=0; y < ALTURA_TELA; y++) {
            if(j->tela[x][y].c != j->tela_anterior[x][y].c || j->tela[x][y].cor != j->tela_anterior[x][y].cor) {
                textcolor(j->tela[x][y].cor);
                putchxy(x+1, y+1, j->tela[x][y].c);
            }
            j->tela_anterior[x][y]=j->tela[x][y];
        }
    }
}

void HideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
