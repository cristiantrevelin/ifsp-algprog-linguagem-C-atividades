#include <stdio.h>
#include <stdlib.h>

#define TAM_MAT 3
#define J1_ELEMENTO 'x'
#define J2_ELEMENTO 'o'

void limpar_tabuleiro (char mat[TAM_MAT][TAM_MAT])
{
    int i, j;

    for (i = 0; i < TAM_MAT; i++)
    {
        for (j = 0; j < TAM_MAT; j++)
            mat[i][j] = ' ';
    }
}

void desenhar_tabuleiro (char mat[TAM_MAT][TAM_MAT])
{
    int i, j;

    for (i = 0; i < TAM_MAT+1; i++)
    {
        printf("                   ");

        if (i > 0)
            printf("%d  ", i-1);
        else
            printf("   ");

        for (j = 0; j < TAM_MAT; j++)
        {
            if (i == 0)
                printf(" %d  ", j);
            else
                printf("|%c| ", mat[i-1][j]);
        }

        printf("\n\n");
    }
}

int tem_linha_cheia (char mat[TAM_MAT][TAM_MAT], char elemento)
{
    int i, j, cont, linha_cheia = 0;

    for (i = 0; i < TAM_MAT; i++)
    {
        cont = 0;

        for (j = 0; j < TAM_MAT; j++)
        {
            if (mat[i][j] == elemento)
                cont++;
        }

        if (cont == TAM_MAT)
            linha_cheia = 1;
    }

    return linha_cheia;
}

int tem_coluna_cheia (char mat[TAM_MAT][TAM_MAT], char elemento)
{
    int i, j, cont, coluna_cheia = 0;

    for (j = 0; j < TAM_MAT; j++)
    {
        cont = 0;

        for (i = 0; i < TAM_MAT; i++)
        {
            if (mat[i][j] == elemento)
                cont++;
        }

        if (cont == TAM_MAT)
            coluna_cheia = 1;
    }

    return coluna_cheia;
}

int diagonal_p_cheia (char mat[TAM_MAT][TAM_MAT], char elemento)
{
    int i, cont = 0, diagonal_cheia = 0;

    for (i = 0; i < TAM_MAT; i++)
    {
        if (mat[i][i] == elemento)
            cont++;
    }

    if (cont == TAM_MAT)
        diagonal_cheia = 1;

    return diagonal_cheia;
}

int diagonal_s_cheia (char mat[TAM_MAT][TAM_MAT], char elemento)
{
    int i, cont = 0, diagonal_cheia = 0;

    for (i = 0; i < TAM_MAT; i++)
    {
        if (mat[i][TAM_MAT - 1 - i] == elemento)
            cont++;
    }

    if (cont == TAM_MAT)
        diagonal_cheia = 1;

    return diagonal_cheia;
}

int vitoria_valida (char mat[TAM_MAT][TAM_MAT], char elemento)
{
    int venceu = 0;

    if (tem_linha_cheia(mat, elemento) || tem_coluna_cheia(mat, elemento) ||
        diagonal_p_cheia(mat, elemento) || diagonal_s_cheia(mat, elemento))
            venceu = 1;

    return venceu;
}

int mat_cheia (char mat[TAM_MAT][TAM_MAT])
{
    int i, j, cont = 0, cheia = 0, qnt_total_elementos = TAM_MAT * TAM_MAT;

    for (i = 0; i < TAM_MAT; i++)
    {
        for (j = 0; j < TAM_MAT; j++)
        {
            if (mat[i][j] != ' ')
                cont++;
        }
    }

    if (cont == qnt_total_elementos)
        cheia = 1;

    return cheia;
}

int pos_valida (char mat[TAM_MAT][TAM_MAT], int pos_x, int pos_y)
{
    int valida = 1;

    if (mat[pos_x][pos_y] != ' ' || pos_x >= TAM_MAT || pos_y >= TAM_MAT || pos_x < 0 || pos_y < 0)
        valida = 0;

    return valida;
}

void main ()
{
    char tabuleiro[TAM_MAT][TAM_MAT], enter;
    int i, jogador_atual, cont_turnos, vencedor;
    int pos_x, pos_y;

    int jogando;    //booleano

    printf(">> [JOGO DA VELHA - PRESSIONE ENTER PARA INICIAR!]");
    scanf("%c", &enter);

    fflush(stdin);
    limpar_tabuleiro(tabuleiro);

    jogador_atual = 1;
    vencedor = 0;
    cont_turnos = 0;

    jogando = 1;

    while (jogando)
    {
        system("cls");

        printf("\n--------------------->> TURNO %d <<------------------------", cont_turnos+1);

        printf("\n\n\n");
        desenhar_tabuleiro(tabuleiro);
        printf("\n----------------------------------------------------------");

        if (vencedor == 0 && !mat_cheia(tabuleiro))
        {
            printf("\n.. [Vez do Jogador %d]:\n", jogador_atual);

            do
            {
                printf("   .. Insira a Linha..: ");
                scanf("%d", &pos_x);
                printf("   .. Insira a Coluna..: ");
                scanf("%d", &pos_y);

                if (!pos_valida(tabuleiro, pos_x, pos_y))
                    printf("      >> Posicao invalida, tente novamente\n\n");

            } while (!pos_valida(tabuleiro, pos_x, pos_y));

            if (jogador_atual == 1)
            {
                tabuleiro[pos_x][pos_y] = J1_ELEMENTO;
                jogador_atual = 2;
            }

            else
            {
                tabuleiro[pos_x][pos_y] = J2_ELEMENTO;
                jogador_atual = 1;
                cont_turnos++;
            }

            if (vitoria_valida(tabuleiro, J1_ELEMENTO))
                vencedor = 1;
            else if (vitoria_valida(tabuleiro, J2_ELEMENTO))
            {
                vencedor = 2;
                cont_turnos--;
            }
        }

        else if (vencedor == 0)
        {
            printf("\n\n>> Jogo Encerrado! Deu velha!\n\n", vencedor);
            jogando = 0;
        }

        else
        {
            printf("\n\n>> Jogo Encerrado! Vitoria do jogador %d!\n\n", vencedor);
            jogando = 0;
        }
    }
}
