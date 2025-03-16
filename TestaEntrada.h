#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
    int boundProfessor;
    int cortesViabilidadeDesativados;
    int cortesOtimalidadeDesativados;   

} arg;

typedef struct 
{
    int heroi1;
    int heroi2;

} conflitos;

typedef struct 
{
    int heroi1;
    int heroi2;
    
} afinidades;

typedef struct
{
    int numHerois, numConflitos, numAfinidades;
    conflitos *conf;
    afinidades *afin;

} Dados;

arg testaEntrada (int argc, char **argv);

Dados LeDados();
