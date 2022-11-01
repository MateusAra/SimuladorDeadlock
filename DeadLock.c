#include <bits/stdc++.h>
//#include <stdio.h>
using namespace std;
int arrmax[100][100];
int alloc[100][100];
int need[100][100];
int avail[100];
int n, r;

void input()
{
    int i, j;
    cout << "Insira o nº de Processos\t";
    cin >> n;
    cout << "Insira o número de instâncias de recursos\t";
    cin >> r;
    cout << "Digite a Matriz Máxima\n";
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < r; j++)
        {
            cin >> arrmax[i][j];
        }
    }
    cout << "Insira a Matriz de Alocação\n";
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < r; j++)
        {
            cin >> alloc[i][j];
        }
    }
    cout << "Insira os recursos disponíveis\n";
    for (j = 0; j < r; j++)
    {
        cin >> avail[j];
    }
}
void show()
{
    int i, j;
    cout << "Processo\t Alocação\t Maxima\t Recursos disponiveis\t";
    for (i = 0; i < n; i++)
    {
        cout << "\nP" << i + 1 << "\t ";
        for (j = 0; j < r; j++)
        {
            cout << alloc[i][j] << " ";
        }
        cout << "\t\t";
        for (j = 0; j < r; j++)
        {
            cout << arrmax[i][j] << " ";
        }
        cout << "\t ";
        if (i == 0)
        {
            for (j = 0; j < r; j++)
                cout << avail[j] << " ";
        }
    }
}
void cal()
{
    int finish[100], temp, need[100][100], flag = 1, k, c1 = 0;
    int dead[100];
    int safe[100];
    int i, j;
    for (i = 0; i < n; i++)
    {
        finish[i] = 0;
    }
    //find need matrix
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < r; j++)
        {
            need[i][j] = arrmax[i][j] - alloc[i][j];
        }
    }
    while (flag)
    {
        flag = 0;
        for (i = 0; i < n; i++)
        {
            int c = 0;
            for (j = 0; j < r; j++)
            {
                if ((finish[i] == 0) && (need[i][j] <= avail[j]))
                {
                    c++;
                    if (c == r)
                    {
                        for (k = 0; k < r; k++)
                        {
                            avail[k] += alloc[i][j];
                            finish[i] = 1;
                            flag = 1;
                        }
                        if (finish[i] == 1)
                        {
                            i = n;
                        }
                    }
                }
            }
        }
    }
    j = 0;
    flag = 0;
    for (i = 0; i < n; i++)
    {
        if (finish[i] == 0)
        {
            dead[j] = i;
            j++;
            flag = 1;
        }
    }
    if (flag == 1)
    {
        cout << "\n\nOsseguintes processos estão em Deadlock\n";
        for (i = 0; i < n; i++)
        {
            for (int j = 0; j < r; j++)
            {
                cout << "P" << dead[i] << "aguardando" << need[i][j]"instancias\t";
            }
        }
    }
    else
    {
        cout << "\nNo Deadlock Occur";
    }
}
int main()
{
    int i, j;
    cout << "********** Detecção de Deadlock************\n";
    input();
    show();
    cal();
    return 0;
}