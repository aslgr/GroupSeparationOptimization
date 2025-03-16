#include "TestaEntrada.h"
#include "separaAux.h"

int main (int argc, char **argv)
{
    int n = 0;

    arg a = testaEntrada(argc, argv);

    Dados dados = LeDados();
    if (dados.afin == NULL || dados.conf == NULL)
        return 1;

    Estado estado_inicial = inicia_Estado(dados.numHerois);
    if (estado_inicial.Grupos == NULL)
        return 1;

    Analise *analise;
    if ((analise = inicia_Analise(dados.numHerois)) == NULL)
        return 1;

    BranchAndBound(a, dados, estado_inicial, analise, n);

    printf("%d\n", analise->MenorNumConf);

    for(int i = 1; i <= dados.numHerois; i++)
    {
        if (analise->estadoOtimo.Grupos[i] == analise->estadoOtimo.Grupos[1])
        {
            if (i < dados.numHerois)
                printf("%d ", i);
            else
                printf("%d", i);
        }
    }

    printf("\n");

    printf("\n%d\n", analise->Contador);

    return 0;
}