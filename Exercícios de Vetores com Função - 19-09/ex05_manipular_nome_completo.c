#include <stdio.h>
#include <stdlib.h>
#define NCOM_TF 101

void escrever_string (char string[], int limite, char *mensagem)
{
    char caractere;
    int pos = 0;

    printf("%s", mensagem);

    do
    {
        caractere = getc(stdin);

        if (caractere != '\n')
        {
            string[pos] = caractere;
            pos++;
        }

    } while (caractere != '\n' && pos < limite - 1);

    string[pos] = '\0';
}

int contar_palavras (char *string, char param_separacao)
{
    int i = 0, contador = 0;

    while (string[i] != '\0')
    {
        if (string[i] != param_separacao && (string[i - 1] == param_separacao || i == 0))
            contador++;

        i++;
    }

    return contador;
}

int contar_caracteres (char *string)
{
    int i = 0;

    while (string[i] != '\0')
        i++;

    return i;
}

int contar_caractere (char *string, char caractere)
{
    int i = 0, cont = 0;

    while (string[i] != '\0')
    {
        if (string[i] == caractere)
            cont++;

        i++;
    }

    return cont;
}

char *escrever_sem_caractere (char *string, char removido)
{
    char *nova_string;
    int i = 0, ns_pos = 0, tam_ns;

    tam_ns = contar_caracteres(string) - contar_caractere(string, removido) + 1;
    nova_string = (char *) malloc(tam_ns * sizeof(char));

    while (string[i] != '\0')
    {
        if (string[i] != removido)
        {
            nova_string[ns_pos] = string[i];
            ns_pos++;
        }

        i++;
    }

    nova_string[ns_pos] = '\0';

    return nova_string;
}

void apresentar_palavras (char *string, char param_separacao)
{
    int i = 0;

    if (string[0] != param_separacao && string[0] != '\0')
        printf("\n   > ");

    while (string[i] != '\0')
    {
        if (string[i] != param_separacao)
            printf("%c", string[i]);
        else if (string[i + 1] != param_separacao && string[i + 1] != '\0')
            printf("\n   > ");

        i++;
    }
}

void verificar_iniciais (char *string, char param_separacao)
{
    int i = 0, cont_palavras = 0, cont_minusculas = 0;

    while (string[i] != '\0')
    {
        if (string[i] != param_separacao && (string[i - 1] == param_separacao || i == 0))
        {
            cont_palavras++;

            if (string[i] > 90 || string[i] < 65)
            {
                printf("\n   > A palavra %d possui inicial minuscula.", cont_palavras);
                cont_minusculas++;
            }
        }

        i++;
    }

    if (cont_minusculas == 0 && cont_palavras > 0)
        printf("\n   > Todos as palavras possuem iniciais maiusculas.");
}

void main ()
{
    char nome_completo[NCOM_TF], *nome_sem_espacos;
    int qnt_palavras, qnt_caracteres;

    escrever_string(nome_completo, NCOM_TF, ".. Insira seu Nome Completo (limite de 100 caracteres)..: ");
    printf("\n>> Nome Registrado: %s", nome_completo);

    qnt_palavras = contar_palavras(nome_completo, ' ');
    printf("\n>> Quantidade de Palavras no Nome: %d", qnt_palavras);

    nome_sem_espacos = escrever_sem_caractere(nome_completo, ' ');
    printf("\n\n>> Nome Registrado sem Espacos: %s", nome_sem_espacos);

    qnt_caracteres = contar_caracteres(nome_sem_espacos);
    printf("\n>> Quantidade de Letras no Nome: %d", qnt_caracteres);

    printf("\n\n>> Palavras que Formam o Nome:");
    apresentar_palavras(nome_completo, ' ');

    printf("\n\n>> Verificando se ha Iniciais Minusculas no Nome:");
    verificar_iniciais(nome_completo, ' ');

    printf("\n");
}
