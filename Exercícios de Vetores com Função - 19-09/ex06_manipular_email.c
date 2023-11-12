#include <stdio.h>
#include <stdlib.h>
#define EMAIL_TF 50

void escrever_vetor (char *vetor, int *tl, int tf)
{
    char caractere;

    do
    {
        scanf("%c", &caractere);

        if (caractere != '\n')
        {
            vetor[*tl] = caractere;
            (*tl)++;
        }

    } while (*tl < tf && caractere != '\n');
}

int contar_ate (char *vetor, int tl, char elemento)
{
    int i = 0;

    while (i < tl && vetor[i] != elemento)
        i++;

    return i;
}

char *copiar_ate (char *vetor, int tl, char elemento, int *novo_tl)
{
    int i;
    char *novo_vetor;

    *novo_tl = contar_ate(vetor, tl, elemento);
    novo_vetor = (char *) malloc((*novo_tl) * sizeof(char));

    for (i = 0; i < *novo_tl; i++)
        novo_vetor[i] = vetor[i];

    return novo_vetor;
}

char *copiar_desde (char *vetor, int tl, char elemento, int *novo_tl)
{
    int i, j = 0;
    int copiar = 0;
    char *novo_vetor;

    *novo_tl = tl - contar_ate(vetor, tl, elemento) - 1;
    novo_vetor = (char *) malloc((*novo_tl) * sizeof(char));

    for (i = contar_ate(vetor, tl, elemento) + 1; i < tl; i++)
    {
        novo_vetor[j] = vetor[i];
        j++;
    }

    return novo_vetor;
}

void resetar_vetor (int *tl)
{
    *tl = 0;
}

void remover_elemento (char *vetor, int *tl, int posicao)
{
    int i;

    (*tl)--;

    for (i = posicao; i < *tl; i++)
        vetor[i] = vetor[i + 1];
}

void normalizar_espacos (char *vetor, int *tl)
{
    int i;

    for (i = 0; i < *tl; i++)
    {
        if (vetor[i] == ' ' && (i == 0 || i == *tl - 1 || vetor[i + 1] == ' '))
        {
            remover_elemento(vetor, tl, i);
            i--;
        }
    }
}

int possui (char *vetor, int tl, char elemento)
{
    int i, elemento_encontrado = 0;

    for (i = 0; i < tl; i++)
    {
        if (vetor[i] == elemento)
            elemento_encontrado = 1;
    }

    return elemento_encontrado;
}

int email_brasileiro (char *vetor, int tl)
{
    int brasileiro = 0;

    if (vetor[tl - 1] == 'r' && vetor[tl - 2] == 'b')
        brasileiro = 1;

    return brasileiro;
}

void apresentar_vetor (char *vetor, int tl)
{
    int i;

    for (i = 0; i < tl; i++)
        printf("%c", vetor[i]);
}

void main ()
{
    char email[EMAIL_TF], *usuario, *servidor;
    int email_tl = 0, usuario_tl = 0, servidor_tl = 0;

    int email_invalido;

    do
    {
        printf(".. Insira o Email (limite de %d caracteres)..: ", EMAIL_TF);
        escrever_vetor(email, &email_tl, EMAIL_TF);

        normalizar_espacos(email, &email_tl);

        if (possui(email, email_tl, ' ') || !possui(email, email_tl, '@') || !possui(email, email_tl, '.'))
        {
            printf("   >> Email invalido, tente novamente.\n\n");
            email_invalido = 1;
            resetar_vetor(&email_tl);
        }
        else
            email_invalido = 0;

    } while (email_invalido);

    usuario = copiar_ate(email, email_tl, '@', &usuario_tl);
    servidor = copiar_desde(email, email_tl, '@', &servidor_tl);

    printf("\n>> Email Registrado: ");
    apresentar_vetor(email, email_tl);

    printf("\n   > Nome de Usuario: ");
    apresentar_vetor(usuario, usuario_tl);

    printf("\n   > Servidor: ");
    apresentar_vetor(servidor, servidor_tl);

    if (email_brasileiro(email, email_tl))
        printf("\n\n   > O Email pertence ao Brasil.");
    else
        printf("\n\n   > O Email nao pertence ao Brasil.");

    printf("\n");
}
