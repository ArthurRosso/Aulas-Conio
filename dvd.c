#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio2.h>

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


int main() {
    Jogo j = InicializaJogo();

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

    if(j->dvd.timer>=0.1) {
        j->dvd.pos.x += j->dvd.velX;
        j->dvd.pos.y += j->dvd.velY;
        j->dvd.timer-=0.1;


        if (j->dvd.pos.x >= LARGURA_TELA-3) {
            j->dvd.velX *= -1;
            j->dvd.pos.x = LARGURA_TELA-5;

        }

        if (j->dvd.pos.y >= ALTURA_TELA-1) {
            j->dvd.velY *= -1;
            j->dvd.pos.y = ALTURA_TELA-3;
        }

        if (j->dvd.pos.x <= 1) {
            j->dvd.velX *= -1;
            j->dvd.pos.x = 1;
        }

        if (j->dvd.pos.y <= 1) {
            j->dvd.velY *= -1;
            j->dvd.pos.y = 1;
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

    j->tela[j->dvd.pos.x][j->dvd.pos.y]=(Pixel) {'D', LIGHTBLUE};
    j->tela[j->dvd.pos.x + 1][j->dvd.pos.y]=(Pixel) {'V', LIGHTBLUE};
    j->tela[j->dvd.pos.x + 2][j->dvd.pos.y]=(Pixel) {'D', LIGHTBLUE};

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
