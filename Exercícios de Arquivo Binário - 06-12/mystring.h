#include <stdio.h>

void ler_string (char *str, int tf)
{
    int tl = 0;
    char caractere;

    do
    {
        caractere = getc(stdin);

        if (caractere != '\n')
        {
            str[tl] = caractere;
            tl++;
        }

    } while (caractere != '\n' && tl < tf - 1);

    str[tl] = '\0';
    tl++;
}

void copiar_string (char *str, char *str_copia)
{
    int pos = 0;

    while (str[pos] != '\0')
    {
        str_copia[pos] = str[pos];
        pos++;
    }

    str_copia[pos] = '\0';
    pos++;
}

int contar_string_tl (char *str)
{
    int tl = 0;

    while (str[tl] != '\0')
        tl++;

    tl++;

    return tl;
}
