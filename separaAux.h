#include <stdio.h>
#include <stdlib.h>

#define NumConfInicial 1000000000

typedef struct
{
    int *Grupos;

} Estado;

typedef struct
{
    int Contador;
    int MenorNumConf;
    Estado estadoOtimo;

} Analise;

Estado inicia_Estado(int numHerois);

Analise *inicia_Analise(int numHerois);

void BranchAndBound(arg a, Dados dados, Estado estado, Analise *analise, int n);