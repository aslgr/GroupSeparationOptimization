#include "TestaEntrada.h"

arg testaEntrada (int argc, char **argv)
{
    arg a;
    a.boundProfessor = 0;
    a.cortesOtimalidadeDesativados = 0;
    a.cortesViabilidadeDesativados = 0;

    int opt;
    int error = 0;

    while ((opt = getopt(argc, argv, "afo")) != -1)
    {
        switch (opt) 
        {
            case 'a': a.boundProfessor = 1;
            break;

            case 'f': a.cortesViabilidadeDesativados = 1;
            break;

            case 'o': a.cortesOtimalidadeDesativados = 1;
            break;

            default: error++;
        }
    }

    // if (error > 0)
    //     printf("Apenas as opções '-a', '-f' e '-o' são levadas em consideração.\n");

    // if (a.boundProfessor)
    //     printf("Usando a função limitante do Professor.\n");
    
    // if (a.cortesOtimilidadeDesativados)
    //     printf("Cortes por otimalidade desativados.\n");

    // if (a.cortesViabilidadeDesativados)
    //     printf("Cortes por viabilidade desativados.\n");

    // printf("\n");

    return a;
}

Dados LeDados()
{
    Dados dados;

    scanf("%d %d %d", &dados.numHerois, &dados.numConflitos, &dados.numAfinidades);

    if ((dados.conf = (conflitos *) malloc (sizeof(conflitos) * dados.numConflitos)) == NULL)
    {
        printf("Erro ao alocar conflitos na memória.\n");
        return dados;
    }

    if ((dados.afin = (afinidades *) malloc (sizeof(afinidades) * dados.numAfinidades)) == NULL)
    {
        printf("Erro ao alocar afinidades na memória.\n");
        return dados;
    }

    for (int i = 0; i < dados.numConflitos; i++)
        scanf("%d %d", &dados.conf[i].heroi1, &dados.conf[i].heroi2);

    for (int i = 0; i < dados.numAfinidades; i++)
        scanf("%d %d", &dados.afin[i].heroi1, &dados.afin[i].heroi2);

    return dados;
}