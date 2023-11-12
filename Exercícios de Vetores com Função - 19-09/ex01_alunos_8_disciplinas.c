#include <stdio.h>
#define MATRICULAS_TF 8

int escrever_matriculas (int vetor[], int vetor_tf, char mensagem[])
{
    int valor, vetor_tl = 0;

    do
    {
     printf(mensagem, vetor_tl+1);
     scanf("%d", &valor);

     if (valor < 0)
        printf("      >> Valor invalido, tente novamente.\n");
     else
     {
        vetor[vetor_tl] = valor;
        vetor_tl++;
     }

    } while (vetor_tl < vetor_tf);

    return vetor_tl;
}

void apresentar_situacao (int vetor[], int vetor_tl, int limite)
{
    int i;

    for (i = 0; i < vetor_tl; i++)
    {
        printf("\n>> Situacao da Disciplina %d: ", i+1);

        if (vetor[i] < limite)
            printf("HA VAGAS.");
        else
            printf("LOTADA.");
    }
}

int somar_elementos (int vetor[], int vetor_tl)
{
    int i, somador = 0;

    for (i = 0; i < vetor_tl; i++)
        somador += vetor[i];

    return somador;
}

void main ()
{
    int matriculas[MATRICULAS_TF], matriculas_tl, qnt_matriculas;
    float media_matriculas;

    matriculas_tl = escrever_matriculas(matriculas, MATRICULAS_TF, ".. Insira a Quantidade de Matriculas da Disciplina %d..: ");
    qnt_matriculas = somar_elementos(matriculas, matriculas_tl);

    media_matriculas = (float) qnt_matriculas / matriculas_tl;

    apresentar_situacao(matriculas, matriculas_tl, 40);

    printf("\n\n>> Media de Alunos Matriculados: %.2f", media_matriculas);
    printf("\n>> Total de Matriculas Realizadas: %d", qnt_matriculas);

    printf("\n");
}
