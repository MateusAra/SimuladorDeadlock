#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
    FILE *arquivo;
    char nome[20] ;


    int num_processo, num_recursos;

    int* vetor_de_existentes;//array de recurssos existentes
    int* vetor_de_disponiveis;//array de recurssos disponiveis

    int j;//contador de recursos
    int i;//contador de processos

    int **matriz_alocados;
    int **matriz_requisitados;


    printf("Digite o nome do arquivo: ");
    scanf("%s", nome);

    arquivo = fopen(nome, "r");//abrindo o arquivo

    if(!arquivo){//verificando se deu certo abrir o arquivo
        printf("Erro ao abrir o arquivo!!!");
        exit(0);
    }

    fscanf(arquivo,"%d",&num_processo);//pegando do arquivo o numero de processos
    fscanf(arquivo,"%d",&num_recursos);//pegando do arquivo o numero de recurssos

    printf("Quantidade de processos: %d\n", num_processo);
    printf("Quantidade de recursos: %d\n\n", num_recursos);

    //alocano memoria para o array de recursos existentes e disponiveis
    vetor_de_existentes = calloc(num_recursos,sizeof(int));
    vetor_de_disponiveis = calloc(num_recursos,sizeof(int));


    /**Vetores existentes e disponiveis*/
    //------------Lendo os Existentes----------------------
    for(i = 0;i<num_recursos;i++){
        fscanf(arquivo,"%d", &vetor_de_existentes[i]);
    }
    printf("Recurssos Existentes\n");
    for(i = 0;i<num_recursos;i++){
        printf("%d ", vetor_de_existentes[i]);
    }
    printf("\n");
    //-------------Lendo os Disponiveis--------------------
    for(i = 0;i<num_recursos;i++){
        fscanf(arquivo,"%d", &vetor_de_disponiveis[i]);
    }
    printf("Recurssos Disponiveis\n");
    for(i = 0;i<num_recursos;i++){
        printf("%d ", vetor_de_disponiveis[i]);
    }
    printf("\n");

    /**Alocando a memoria para as matrizes de alocados e requisitados*/


    matriz_alocados = calloc(num_recursos,sizeof(int*));
    matriz_requisitados = calloc(num_recursos,sizeof(int*));

    for(i=0;i<num_processo;i++){
        matriz_alocados[i] = calloc(num_recursos,sizeof(int));
    }
    for(i=0;i<num_processo;i++){
        matriz_requisitados[i] = calloc(num_recursos,sizeof(int));
    }


    for(i=0;i<num_processo;i++){//pegando os valores
        for(j=0;j<num_recursos;j++){
            fscanf(arquivo,"%d", &matriz_alocados[i][j]);
        }
    }
    for(i=0;i<num_processo;i++){//pegando os valores
        for(j=0;j<num_recursos;j++){
            fscanf(arquivo,"%d",&matriz_requisitados[i][j]);
        }
    }

    printf("\n\nMatriz de alocados\n");
    for(i=0;i<num_processo;i++){//mostrando
        for(j=0;j<num_recursos;j++){
            printf("%d ",matriz_alocados[i][j]);
        }
        printf("\n");
    }
    printf("\nMatriz de requisitados\n");
    for(i=0;i<num_processo;i++){//mostrando
        for(j=0;j<num_recursos;j++){
            printf("%d ",matriz_requisitados[i][j]);
        }
        printf("\n");
    }


    int* ja_executados = calloc(num_processo,sizeof(int));
    for(i=0;i<num_processo;i++){
        ja_executados[i] = FALSE;
    }

    printf("\n");
    for(i=0;i<num_processo;i++){//quantidade maxima de tentativas
        printf("------Tentativa %d------\n\n",i+1);
        int qtd_processos_executados = 0;


        for(j=0;j<num_processo;j++){//tentando executar todos os processo numa mesma tentativa

            if(ja_executados[j] == TRUE) continue;//se o processo atual ja foi executado nao precisa tentar executar ele

            int k, qtd_de_recursos_pegos = 0;

            for(k = 0; k < num_recursos; k++)
            {
                if(matriz_requisitados[j][k] == 0 || matriz_requisitados[j][k] <= vetor_de_disponiveis[k])
                {
                    //concigo pegar
                    qtd_de_recursos_pegos++;
                }
                else
                {
                    //nao concigo
                    break;//se nao conceguio pegar pelo menos um recursso entao nem tente mais verificar se ele consigir� pegar outros recurssos
                }
            }

            if(qtd_de_recursos_pegos == num_recursos)
            {//se conceguio pegar todos os recursos que precesava defina esse processo como executado
                for( k = 0; k < num_recursos; k++){
                    vetor_de_disponiveis[k] = vetor_de_disponiveis[k] + matriz_alocados[j][k];//atualizando o vetor de disponiveis
                }
                printf("Processo %d EXECUTADO.\n",j+1);
                ja_executados[j] = TRUE;
                qtd_processos_executados++;
            }
        }

        if(qtd_processos_executados != 0){//verificando se executou todo mundo
            int executados=0;
            int k;
            for(k=0;k<num_processo;k++){
                if(ja_executados[k]==TRUE) executados++;
            }

            if(executados == num_processo){
                printf("\n\nTodos os processos foram executados\n"); break;
            }
        }
        else{//verificando se entrou em deadlock ou bloqueio
            int faltam_executar = 0;
            for(int k = 0; k < num_processo; k++)
            {
                if(ja_executados[k] == FALSE) 
                    faltam_executar++;
            }

            if(faltam_executar==1){
                for(k=0;k<num_processo;k++){
                    if(ja_executados[k]==FALSE){
                        printf("Processo %d BLOQUEADO.\n",k+1);
                        int l;
                        printf("Alocados[");
                        for(l=0;l<num_recursos;l++){
                           printf("%d ",matriz_alocados[k][l]);
                        }
                        printf("] ");

                        printf("Requisitados[");
                        for(l=0;l<num_recursos;l++){
                           printf("%d ",matriz_requisitados[k][l]);
                        }
                        printf("] \n\n");
                        break;
                    }
                }
                break;
            }
            else{
                for(k=0;k<num_processo;k++){
                    if(ja_executados[k]==FALSE){
                        printf("Processo %d em DEADLOCK.\n",k+1);
                        int l;
                        printf("Alocados[");
                        for(l=0;l<num_recursos;l++){
                           printf("%d ",matriz_alocados[k][l]);
                        }
                        printf("] ");

                        printf("Requisitados[");
                        for(l=0;l<num_recursos;l++){
                           printf("%d ",matriz_requisitados[k][l]);
                        }
                        printf("] \n\n");

                    }
                }
                break;
            }
        }

        int b;
        printf("\n.:Vetor de Disponiveis:.\n");//mostrando depois de cada tentativa como ficou o vetor de disponiveis
        for(b=0;b<num_recursos;b++){
            printf("%d ", vetor_de_disponiveis[b]);
        }
        printf("\n\n");
    }

    system("pause");
    return 0;
}