#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio2.h>

typedef struct {
    int x;
    int y;
} Posicao;

typedef struct {
    Posicao pos;
    float timer;
} DVD;

typedef struct {
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

Jogo InicializaJogo(){
    Jogo j;
    j.dvd.pos.x=0;
    j.dvd.pos.y=0;
    j.dvd.timer=0;

    return j;
}

void AtualizaJogo(Jogo* j, float deltaT){
    j->dvd.timer+=deltaT;

    if(j->dvd.timer>=1){
        j->dvd.pos.x++;
        j->dvd.pos.y++;
        j->dvd.timer-=1;
    }
}
void DesenhaJogo(Jogo* j){
    clrscr();

    cputsxy(
        j->dvd.pos.x,
        j->dvd.pos.y,
        "DVD"
    );
}
