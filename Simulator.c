#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
    FILE *arquivo;
    char nome[20];

    int numProcesso, numRecursos;

    int *vetorDeExistentes;
    int *vetorDeDisponiveis;

    int j; 
    int i; 

    int **matrizAlocacao;
    int **matrizRequisicao;

    printf("Digite o nome do arquivo: ");
    scanf("%s", nome);

    arquivo = fopen(nome, "r");

    if (!arquivo)
    {
        printf("Erro ao abrir o arquivo!!!");
        exit(0);
    }

    fscanf(arquivo, "%d", &numProcesso); 
    fscanf(arquivo, "%d", &numRecursos); 

    printf("Quantidade de processos: %d\n", numProcesso);
    printf("Quantidade de recursos: %d\n\n", numRecursos);

    vetorDeExistentes = calloc(numRecursos, sizeof(int));
    vetorDeDisponiveis = calloc(numRecursos, sizeof(int));

    for (i = 0; i < numRecursos; i++)
    {
        fscanf(arquivo, "%d", &vetorDeExistentes[i]);
    }
    printf("Recursos Existentes\n");
    for (i = 0; i < numRecursos; i++)
    {
        printf("%d ", vetorDeExistentes[i]);
    }
    printf("\n");

    for (i = 0; i < numRecursos; i++)
    {
        fscanf(arquivo, "%d", &vetorDeDisponiveis[i]);
    }
    printf("Recursos Disponiveis\n");
    for (i = 0; i < numRecursos; i++)
    {
        printf("%d ", vetorDeDisponiveis[i]);
    }
    printf("\n");

    matrizAlocacao = calloc(numRecursos, sizeof(int *));
    matrizRequisicao = calloc(numRecursos, sizeof(int *));

    for (i = 0; i < numProcesso; i++)
    {
        matrizAlocacao[i] = calloc(numRecursos, sizeof(int));
    }

    for (i = 0; i < numProcesso; i++)
    {
        matrizRequisicao[i] = calloc(numRecursos, sizeof(int));
    }

    for (i = 0; i < numProcesso; i++)
    {
        for (j = 0; j < numRecursos; j++)
        {
            fscanf(arquivo, "%d", &matrizAlocacao[i][j]);
        }
    }
    for (i = 0; i < numProcesso; i++)
    {
        for (j = 0; j < numRecursos; j++)
        {
            fscanf(arquivo, "%d", &matrizRequisicao[i][j]);
        }
    }

    printf("\n\nMatriz de alocacao\n");
    for (i = 0; i < numProcesso; i++)
    { 
        for (j = 0; j < numRecursos; j++)
        {
            printf("%d ", matrizAlocacao[i][j]);
        }
        printf("\n");
    }

    printf("\nMatriz de requisitados\n");
    for (i = 0; i < numProcesso; i++)
    {
        for (j = 0; j < numRecursos; j++)
        {
            printf("%d ", matrizRequisicao[i][j]);
        }
        printf("\n");
    }

    int *ja_executados = calloc(numProcesso, sizeof(int));

    for (i = 0; i < numProcesso; i++)
    {
        ja_executados[i] = FALSE;
    }

    printf("\n");

    for (i = 0; i < numProcesso; i++)
    {
        printf("------Tentativa %d------\n\n", i + 1);

        int qtd_processos_executados = 0;

        for (j = 0; j < numProcesso; j++)
        { 

            if (ja_executados[j] == TRUE)
                continue;

            int k, qtd_de_recursos_pegos = 0;

            for (k = 0; k < numRecursos; k++)
            {
                if (matrizRequisicao[j][k] == 0 || matrizRequisicao[j][k] <= vetorDeDisponiveis[k])
                {
                    qtd_de_recursos_pegos++;
                }
                else
                {
                    break;
                }
            }

            if (qtd_de_recursos_pegos == numRecursos)
            {
                for (k = 0; k < numRecursos; k++)
                {
                    vetorDeDisponiveis[k] = vetorDeDisponiveis[k] + matrizAlocacao[j][k];
                }

                printf("Processo %d EXECUTADO.\n", j + 1);
                ja_executados[j] = TRUE;
                qtd_processos_executados++;
            }
        }

        if (qtd_processos_executados != 0)
        {
            int executados = 0;

            for (int k = 0; k < numProcesso; k++)
            {
                if (ja_executados[k] == TRUE)
                    executados++;
            }

            if (executados == numProcesso)
            {
                printf("\n\nTodos os processos foram executados\n");
                break;
            }
        }
        else
        {
            int faltam_executar = 0;
            int k;
            int numRecursosFaltam;
            for (k = 0; k < numProcesso; k++)
            {
                if (ja_executados[k] == FALSE)
                    faltam_executar++;
            }

            if (faltam_executar == 1)
            {
                for (k = 0; k < numProcesso; k++)
                {
                    if (ja_executados[k] == FALSE)
                    {
                        for (int line = 0; line < numRecursos; line++)
                        {
                            numRecursosFaltam = matrizRequisicao[k][line] - vetorDeDisponiveis[line];
                            if (numRecursosFaltam > 0)
                                printf("Processo %d em esperando %d intancias de R%d\n", k + 1, numRecursosFaltam, line + 1);
                        }
                        break;
                    }
                }
                break;
            }
            else
            {
                for (k = 0; k < numProcesso; k++)
                {
                    if (ja_executados[k] == FALSE)
                    {
                        for (int line = 0; line < numRecursos; line++)
                        {
                            numRecursosFaltam = matrizRequisicao[k][line] - vetorDeDisponiveis[line];
                            if (numRecursosFaltam > 0)
                                printf("Processo %d em esperando %d intancias de R%d\n", k + 1, numRecursosFaltam, line + 1);
                        }
                    }
                }
                break;
            }
        }
        printf("\nVetor de Disponiveis:");
        for (int b = 0; b < numRecursos; b++)
        {
            printf("%d ", vetorDeDisponiveis[b]);
        }
        printf("\n\n");
    }
    system("pause");
    return 0;
}