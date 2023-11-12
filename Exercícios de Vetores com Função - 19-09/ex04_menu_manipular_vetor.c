#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define TF 30

void mostrar_menu ()
{
    printf("\n-------------------------------------------------------------------------------");
    printf("\n[MANIPULADOR DE VETOR INTEIRO - MENU]\n");

    printf("\n[0] Resetar o vetor;");
    printf("\n[1] Gerar valores aleatórios para o vetor;");
    printf("\n[2] Apresentar o vetor inteiro;");
    printf("\n\n[3] Incluir um elemento no final do vetor;");
    printf("\n[4] Incluir um elemento em uma determinada posição no meio do vetor;");
    printf("\n[5] Incluir um elemento no início do vetor;");

    printf("\n\n[6] Excluir o primeiro elemento do vetor;");
    printf("\n[7] Excluir o último elemento do vetor;");
    printf("\n[8] Excluir um elemento de uma determinada posição no meio vetor;");
    printf("\n[9] Excluir os elementos entre duas posições do vetor;");

    printf("\n\n[10] Localizar e apresentar a posição de um determinado elemento do vetor;");

    printf("\n\n[-1] Limpar a tela;");
    printf("\n[-2] Encerrar o programar;");

    printf("\n\n------------------------------------------------------------------------------");
}

void resetar (int *tl)
{
    *tl = 0;
}

void inserir_aleatorios (int *vetor, int *tl, int qnt, int valor_inicial, int valor_final)
{
    int i, limite, intervalo;
    long int tempo;

    tempo = time(NULL);
    srand(tempo);
    intervalo = valor_final - valor_inicial + 1;

    limite = *tl + qnt;

    for (i = *tl; i < limite; i++)
    {
        vetor[i] = valor_inicial + rand() % intervalo;
        (*tl)++;
    }
}

void inserir_elemento (int *vetor, int *tl, int elemento, int posicao)
{
    int i;

    for (i = *tl; i > posicao; i--)
        vetor[i] = vetor[i - 1];

    vetor[posicao] = elemento;
    (*tl)++;
}

void excluir_elemento (int *vetor, int *tl, int posicao)
{
    int i;

    (*tl)--;
    for (i = posicao; i < *tl; i++)
        vetor[i] = vetor[i + 1];
}

void excluir_entre_posicoes (int *vetor, int *tl, int pos_inicial, int pos_final)
{
    int i, qnt_excluidos;

    qnt_excluidos = pos_final - pos_inicial - 1;

    for (i = 0; i < qnt_excluidos; i++)
        excluir_elemento(vetor, tl, pos_inicial + 1);
}

void apresentar_elementos (int *vetor, int tl, int com_posicao)
{
    int i;

    for (i = 0; i < tl; i++)
    {
        if (com_posicao)
            printf("\n      > [%.2d] - %d", i, vetor[i]);
        else
            printf("\n      > %d", vetor[i]);
    }
}

int contar_elemento (int *vetor, int tl, int elemento)
{
    int i, qnt_elemento = 0;

    for (i = 0; i < tl; i++)
    {
        if (vetor[i] == elemento)
            qnt_elemento++;
    }

    return qnt_elemento;
}

int *buscar_posicoes (int *vetor, int tl, int *posicoes_tl, int elemento)
{
    int *posicoes;
    int i;

    posicoes = (int *) malloc(contar_elemento(vetor, tl, elemento) * sizeof(int));

    for (i = 0; i < tl; i++)
    {
        if (vetor[i] == elemento)
        {
            posicoes[*posicoes_tl] = i;
            (*posicoes_tl)++;
        }
    }

    return posicoes;
}

void main ()
{
    int vetor[TF];
    int tl = 0, opcao, tela_limpa = 1;

    int qnt_aleatorios, valor_inicial, valor_final, novo_elemento, nova_posicao;
    int *posicoes = NULL, posicoes_tl = 0;

    setlocale(LC_ALL, "Portuguese");

    do
    {
        if (tela_limpa)
        {
            mostrar_menu();
            tela_limpa = 0;
        }

        printf("\n.. Insira a sua opção..: ");
        scanf("%d", &opcao);

        switch (opcao)
        {

        case 0:
            resetar(&tl);
            printf("   >> Vetor resetado com sucesso!");
            break;

        case 1:

            if (tl < TF)
            {
                printf("\n   .. Determine a faixa de valores:");

                printf("\n      .. Valor inicial..: ");
                scanf("%d", &valor_inicial);

                printf("      .. Valor final..: ");
                scanf("%d", &valor_final);

                printf("\n      .. Insira a quantidade de valores..: ");
                scanf("%d", &qnt_aleatorios);

                if (qnt_aleatorios > TF - tl)
                    printf("      >> Quantidade inválida. Espaço Disponível no Vetor: %d", TF - tl);
                else
                {
                    if (valor_inicial > valor_final)
                        inserir_aleatorios(vetor, &tl, qnt_aleatorios, valor_final, valor_inicial);
                    else
                        inserir_aleatorios(vetor, &tl, qnt_aleatorios, valor_inicial, valor_final);

                    printf("\n   >> Valores inseridos com sucesso!");
                }
            }
            else
                printf("   >> O vetor está cheio.");


            break;

        case 2:
            if (tl > 0)
            {
                printf("\n   >> Apresentando o Vetor:");
                apresentar_elementos(vetor, tl, 1);
            }
            else
                printf("   >> O vetor está vazio.");

            break;

        case 3:
            if (tl < TF)
            {
                printf("\n   .. Insira o novo elemento..: ");
                scanf("%d", &novo_elemento);

                inserir_elemento(vetor, &tl, novo_elemento, tl);
                printf("   >> Valor inserido com sucesso!");
            }
            else
                printf("   >> O vetor está cheio.");

            break;

        case 4:
            if (tl < TF && tl > 0)
            {
                printf("\n   .. Insira o novo elemento..: ");
                scanf("%d", &novo_elemento);

                printf("   .. Insira a posição..: ");
                scanf("%d", &nova_posicao);

                if (nova_posicao > tl - 1 || nova_posicao < 0)
                    printf("      >> Posição inválida.");
                else
                {
                    inserir_elemento(vetor, &tl, novo_elemento, nova_posicao);
                    printf("   >> Valor inserido com sucesso!");
                }
            }
            else
                printf("   >> O vetor está cheio ou não possui elementos.");

            break;

        case 5:
            if (tl < TF)
            {
                printf("\n   .. Insira o novo elemento..: ");
                scanf("%d", &novo_elemento);

                inserir_elemento(vetor, &tl, novo_elemento, 0);
                printf("   >> Valor inserido com sucesso!");
            }
            else
                printf("   >> O vetor está cheio.");

            break;

        case 6:
            if (tl > 0)
            {
                excluir_elemento(vetor, &tl, 0);
                printf("   >> Valor excluído com sucesso!");
            }
            else
                printf("   >> O vetor está vazio.");

            break;

        case 7:
            if (tl > 0)
            {
                excluir_elemento(vetor, &tl, tl-1);
                printf("   >> Valor excluído com sucesso!");
            }
            else
                printf("   >> O vetor está vazio.");

            break;

        case 8:
            if (tl > 0)
            {
                printf("\n   .. Insira a posição..: ");
                scanf("%d", &nova_posicao);

                if (nova_posicao > tl - 1 || nova_posicao < 0)
                    printf("      >> Posição inválida.");
                else
                {
                    excluir_elemento(vetor, &tl, nova_posicao);
                    printf("   >> Valor excluído com sucesso!");
                }
            }
            else
                printf("   >> O vetor está vazio.");

            break;

        case 9:
            if (tl > 2)
            {
                printf("\n   .. Insira a posição inicial..: ");
                scanf("%d", &valor_inicial);

                printf("   .. Insira a posição final..: ");
                scanf("%d", &valor_final);

                if (valor_inicial > tl - 1 || valor_inicial < 0 || valor_final > tl - 1 || valor_final < 0
                    || valor_inicial > valor_final)
                    printf("      >> Posições inválidas.");
                else
                {
                    excluir_entre_posicoes(vetor, &tl, valor_inicial, valor_final);
                    printf("   >> Valores excluídos com sucesso!");
                }
            }
            else
                printf("   >> O vetor não possui elementos no meio.");

            break;

        case 10:
            if (tl > 0)
            {
                printf("\n   .. Insira o elemento..: ");
                scanf("%d", &novo_elemento);

                resetar(&posicoes_tl);
                free(posicoes);

                posicoes = buscar_posicoes(vetor, tl, &posicoes_tl, novo_elemento);

                if (posicoes_tl > 0)
                {
                    printf("\n   >> Apresentando as posições do elemento %d:", novo_elemento);
                    apresentar_elementos(posicoes, posicoes_tl, 0);
                }
                else
                    printf("\n   >> O elemento %d não foi encontrado.", novo_elemento);
            }
            else
                printf("   >> O vetor está vazio.");

            break;

        case -1:
            system("cls");
            tela_limpa = 1;

            break;

        case -2:
            printf("   >> Encerrando o programa.");
            break;

        default:
            printf("   >> Opção inválida.");
        }

        if (!tela_limpa)
            printf("\n\n------------------------------------------------------------------------------");

    } while (opcao != -2);
}
