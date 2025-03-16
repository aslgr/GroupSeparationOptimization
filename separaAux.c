#include "TestaEntrada.h"
#include "separaAux.h"

Estado inicia_Estado(int numHerois)
{
    Estado estado;

    if ((estado.Grupos = (int *) malloc (sizeof(int) * (numHerois + 1))) == NULL)
    {
        printf("Erro ao alocar estado na memória.\n");
        return estado;
    }

    for (int i = 0; i <= numHerois; i++)
        estado.Grupos[i] = i * numHerois + 10;

    return estado;
}

Analise *inicia_Analise(int numHerois)
{
    Analise *analise;

    if ((analise = (Analise *) malloc (sizeof(Analise))) == NULL)
    {
        printf("Erro ao alocar analise na memória.\n");
        return NULL;
    }

    analise->Contador = 0;
    analise->MenorNumConf = NumConfInicial;
    analise->estadoOtimo = inicia_Estado (numHerois);

    return analise;
}

int Bound(Dados dados, Estado estado, int n)
{
    int i, j, k,
        heroi1, heroi2,
        heroi1aux, heroi2aux,
        heroi1aux2, heroi2aux2,
        heroi1Tri = -1, heroi2Tri = -1,
        numConflitosGrupo = 0, numTriangulos = 0;

    for (i = 0; i < dados.numConflitos; i++) 
    {
        heroi1 = dados.conf[i].heroi1;
        heroi2 = dados.conf[i].heroi2;

        if (estado.Grupos[heroi1] == estado.Grupos[heroi2])
        {
            numConflitosGrupo++;
        }
        else if (heroi1 > n && heroi2 > n)
        {
            for (j = i + 1; j < dados.numConflitos; j++)
            {
                heroi1aux = dados.conf[j].heroi1;
                heroi2aux = dados.conf[j].heroi2;

                if (heroi1aux > n && heroi2aux > n)
                {
                    if (estado.Grupos[heroi1] == estado.Grupos[heroi1aux])
                    {
                        heroi1Tri = heroi2; heroi2Tri = heroi2aux;
                    }
                    else if (estado.Grupos[heroi1] == estado.Grupos[heroi2aux])
                    {
                        heroi1Tri = heroi2; heroi2Tri = heroi1aux;
                    }
                    else if (estado.Grupos[heroi2] == estado.Grupos[heroi1aux])
                    {
                        heroi1Tri = heroi1; heroi2Tri = heroi2aux;
                    }
                    else if (estado.Grupos[heroi2] == estado.Grupos[heroi2aux])
                    {
                        heroi1Tri = heroi1; heroi2Tri = heroi1aux;
                    }

                    if (heroi1Tri != -1)
                    {
                        for (k = j + 1; k < dados.numConflitos; k++)
                        {
                            heroi1aux2 = dados.conf[k].heroi1;
                            heroi2aux2 = dados.conf[k].heroi2;

                            if ((heroi1aux2 == heroi1Tri && heroi2aux2 == heroi2Tri) ||
                                (heroi1aux2 == heroi2Tri && heroi2aux2 == heroi1Tri))
                            {
                                numTriangulos++;
                            }
                        }
                    }
                }
            }
        }
    }

    return numConflitosGrupo + numTriangulos;
}

int verificarAfinidades(Dados dados, Estado estado, int n)
{
    for (int i = 0; i < dados.numAfinidades; i++)
    {
        int heroi1 = dados.afin[i].heroi1;
        int heroi2 = dados.afin[i].heroi2;

        if ((heroi1 <= n && heroi2 <= n) && estado.Grupos[heroi1] != estado.Grupos[heroi2])
            return 0;
    }

    return 1;
}

int GrupoVazio(Dados dados, Estado estado)
{
    for (int i = 2; i <= dados.numHerois; i++)
    {
        if (estado.Grupos[i] != estado.Grupos[1])
            return 0;
    }

    return 1;
}

void BranchAndBound(arg a, Dados dados, Estado estado, Analise *analise, int n)
{
    int LowerBound, i;

    analise->Contador++;

    LowerBound = Bound(dados, estado, n);

    if (n == dados.numHerois)
    {
        if (GrupoVazio(dados, estado))
            return;

        if (LowerBound < analise->MenorNumConf)
        {
            analise->MenorNumConf = LowerBound;

            for (i = 1; i <= dados.numHerois; i++)
                analise->estadoOtimo.Grupos[i] = estado.Grupos[i];
        }

        return;
    }

    if (!a.cortesOtimalidadeDesativados)
    {
        if (LowerBound >= analise->MenorNumConf)
            return;
    }

    if (!a.cortesViabilidadeDesativados)
    {
        if (!verificarAfinidades(dados, estado, n))
            return;
    }

    Estado estado_anterior = inicia_Estado(dados.numHerois);
    estado_anterior = estado;

    estado.Grupos[n+1] = 1;
    BranchAndBound(a, dados, estado, analise, n+1);

    estado = estado_anterior;

    estado.Grupos[n+1] = 2;
    BranchAndBound(a, dados, estado, analise, n+1);

    return;
}