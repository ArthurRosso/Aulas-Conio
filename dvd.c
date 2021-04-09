#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>

typedef struct {

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
}

void AtualizaJogo(Jogo* j, float deltaT){
}
void DesenhaJogo(Jogo* j){
}
