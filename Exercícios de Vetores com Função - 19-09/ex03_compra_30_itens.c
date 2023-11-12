#include <stdio.h>
#define PRODUTOS_TF 30

int escrever_produtos (int cod_barras[], int qnt_comprada[], float valor_unidade[], int vetores_tf)
{
    int vetores_tl = 0, cod_teste, qnt_teste;
    float valor_teste;

    do
    {
        printf("\n.. Insira o Codigo de Barras do Produto %d ou -1 para Sair..: ", vetores_tl+1);
        scanf("%d", &cod_teste);

        if (cod_teste != -1)
        {
            cod_barras[vetores_tl] = cod_teste;

            printf(".. Insira o Valor Unitario do Produto %d em RS..: ", vetores_tl+1);
            scanf("%f", &valor_teste);

            if (valor_teste > 0)
            {
                valor_unidade[vetores_tl] = valor_teste;

                printf(".. Insira a Quantidade Comprada %d..: ", vetores_tl+1);
                scanf("%d", &qnt_teste);

                if (qnt_teste > 0)
                {
                    qnt_comprada[vetores_tl] = qnt_teste;

                    vetores_tl++;
                }
                else
                    printf("\n>> Quantidade invalida, tente novamente.\n");
            }
            else
                printf("\n>> Valor invalido, tente novamente.\n");
        }

    } while (vetores_tl < vetores_tf && cod_teste != -1);

    return vetores_tl;
}

int calcular_quantidade (int vetor_qnt[], int tl)
{
    int i, quantidade = 0;

    for (i = 0; i < tl; i++)
        quantidade += vetor_qnt[i];

    return quantidade;
}

float calcular_compra (int qnt_comprada[], float valor_unidade[], int tl)
{
    int i;
    float total = 0;

    for (i = 0; i < tl; i++)
        total += qnt_comprada[i] * valor_unidade[i];

    return total;
}

void apresentar_cupom (int cod_barras[], int qnt_comprada[], float valor_unidade[], int tl)
{
    float total_item, total_compra;
    int i, qnt_produtos;

    printf("\n>> CUPOM DE COMPRA:");
    printf("\n--------------------------------------------");
    printf("\n  Codigo    Valor Un     Qnt      Total");

    for (i = 0; i < tl; i++)
    {
        total_item = qnt_comprada[i] * valor_unidade[i];

        printf("\n  %.6d     %6.2f      %.3d      %5.2f", cod_barras[i], valor_unidade[i], qnt_comprada[i], total_item);
    }

    qnt_produtos = calcular_quantidade(qnt_comprada, tl);
    total_compra = calcular_compra(qnt_comprada, valor_unidade, tl);

    printf("\n\n\n                         %.3d      %5.2f", qnt_produtos, total_compra);
    printf("\n\n                         Qnt de Itens: %d", tl);

    printf("\n--------------------------------------------");

}

void apresentar_mais_caros (int cod_barras[], float valor_unidade[], int tl, float referencia)
{
    int i;

    printf("\n>> Produtos com valor maior que RS%.2f:", referencia);

    for (i = 0; i < tl; i++)
    {
        if (valor_unidade[i] > referencia)
            printf("\n    > %.6d - RS%6.2f", cod_barras[i], valor_unidade[i]);
    }
}

void apresentar_produto (int codigo, int cod_barras[], int qnt_comprada[], float valor_unidade[], int tl)
{
    int i, produto_encontrado = 0;
    float total_item;

    for (i = 0; i < tl; i++)
    {
        if (cod_barras[i] == codigo)
        {
            produto_encontrado = 1;
            total_item = valor_unidade[i] * qnt_comprada[i];

            printf("\n>> Produto Encontrado:");
            printf("\n    > Codigo: %.6d", cod_barras[i]);
            printf("\n    > Quantidade Comprada: %3.d", qnt_comprada[i]);
            printf("\n    > Valor Unitario: RS%.2f", valor_unidade[i]);
            printf("\n    > Valor Total do Item: RS%.2f", total_item);
        }
    }

    if (!produto_encontrado)
        printf("\n>> Produto Nao Encontrado.");
}

void main ()
{
    int cod_barras[PRODUTOS_TF], qnt_comprada[PRODUTOS_TF], produtos_tl, cod_referencia;
    float valor_unidade[PRODUTOS_TF], valor_referencia;

    produtos_tl = escrever_produtos(cod_barras, qnt_comprada, valor_unidade, PRODUTOS_TF);
    apresentar_cupom (cod_barras, qnt_comprada, valor_unidade, produtos_tl);

    printf("\n\n.. Insira um Valor de Referencia..: ");
    scanf("%f", &valor_referencia);

    apresentar_mais_caros(cod_barras, valor_unidade, produtos_tl, valor_referencia);

    printf("\n\n.. Insira um Codigo de Barras..: ");
    scanf("%d", &cod_referencia);

    apresentar_produto(cod_referencia, cod_barras, qnt_comprada, valor_unidade, produtos_tl);

    printf("\n");
}
