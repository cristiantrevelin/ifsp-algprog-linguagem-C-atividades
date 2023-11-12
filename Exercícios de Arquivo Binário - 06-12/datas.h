#include <stdio.h>

typedef struct
{
    int dia, mes, ano;

} tp_data;

void cadastrar_data (tp_data *data)
{
    int teste_dia, teste_mes, teste_ano;

    do
    {
        printf(".. Insira o dia..: ");
        scanf("%d", &teste_dia);

        if (teste_dia < 1 || teste_dia > 31)
            printf("    >> Dia invalido, tente novamente.\n");

    } while (teste_dia < 1 || teste_dia > 31);

    do
    {
        printf(".. Insira o mes..: ");
        scanf("%d", &teste_mes);

        if (teste_mes < 1 || teste_mes > 12)
            printf("    >> Mes invalido, tente novamente.\n");

    } while (teste_mes < 1 || teste_mes > 12);

    do
    {
        printf(".. Insira o ano..: ");
        scanf("%d", &teste_ano);

        if (teste_ano < 2000)
            printf("    >> Ano invalido, tente novamente.\n");

    } while (teste_ano < 2000);

    (*data).dia = teste_dia;
    (*data).mes = teste_mes;
    (*data).ano = teste_ano;
}

int datas_iguais (tp_data data1, tp_data data2)
{
    int iguais = 0;

    if (data1.dia == data2.dia && data1.mes == data2.mes && data1.ano == data2.ano)
        iguais = 1;

    return iguais;
}
