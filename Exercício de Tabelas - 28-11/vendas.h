#include <stdio.h>
#include "produtos.h"
#include "datas.h"

typedef struct
{
    tp_data data;
    int produto, qnt;

} tp_venda;

void adicionar_venda (tp_venda tab_venda[], int *tl, tp_data data, int produto, int qnt)
{
    tab_venda[*tl].data = data;
    tab_venda[*tl].produto = produto;
    tab_venda[*tl].qnt = qnt;

    (*tl)++;
}

float calcular_total_venda_pos (tp_venda tab_venda[], tp_produto tab_produto[], int tl_produtos, int pos_venda)
{
    float total;
    int cod_produto, pos_produto;

    cod_produto = tab_venda[pos_venda].produto;
    pos_produto = buscar_pos_produto(tab_produto, tl_produtos, cod_produto);

    total = tab_produto[pos_produto].preco * tab_venda[pos_venda].qnt;

    return total;
}

float calcular_total_vendas_produto (tp_venda tab_venda[], int tl_vendas, tp_produto tab_produto[], int tl_produtos, int cod)
{
    int i;
    float total_vendas = 0;

    for (i = 0; i < tl_vendas; i++)
    {
        if (tab_venda[i].produto == cod)
            total_vendas += calcular_total_venda_pos(tab_venda, tab_produto, tl_produtos, i);
    }

    return total_vendas;
}

float calcular_total_vendas_data (tp_venda tab_venda[], int tl_vendas, tp_produto tab_produto[], int tl_produtos, tp_data data)
{
    int i;
    float total_vendas = 0;

    for (i = 0; i < tl_vendas; i++)
    {
        if (datas_iguais(data, tab_venda[i].data))
            total_vendas += calcular_total_venda_pos(tab_venda, tab_produto, tl_produtos, i);
    }

    return total_vendas;
}

float calcular_total_vendas_mes (tp_venda tab_venda[], int tl_vendas, tp_produto tab_produto[], int tl_produtos, int mes)
{
    int i;
    float total = 0;

    for (i = 0; i < tl_vendas; i++)
    {
        if (mes == tab_venda[i].data.mes)
            total += calcular_total_venda_pos(tab_venda, tab_produto, tl_produtos, i);
    }

    return total;
}

void realizar_venda (tp_venda tab_venda[], int *tl_vendas, tp_produto tab_produto[], int tl_produtos)
{
    int teste_codigo, teste_qnt, pos_produto, qnt_estoque;
    float total_venda;
    tp_data teste_data;

    printf("\n[CADASTRO DE PRODUTO]:");

    printf("\n.. Insira o codigo do produto..: ");
    scanf("%d", &teste_codigo);

    if (cod_produto_existe(tab_produto, tl_produtos, teste_codigo))
    {
        pos_produto = buscar_pos_produto(tab_produto, tl_produtos, teste_codigo);
        qnt_estoque = tab_produto[pos_produto].qnt;

        if (qnt_estoque > 0)
        {
            cadastrar_data(&teste_data);

            do
            {
                printf(".. Insira a quantidade a ser vendida..: ");
                scanf("%d", &teste_qnt);

                if (teste_qnt > qnt_estoque)
                    printf("    >> A quantidade inserida excede a quantidade em estoque (%d), tente novamente.\n", qnt_estoque);
                else if (teste_qnt < 1)
                    printf("    >> Quantidade invalida, tente novamente.\n");

            } while (teste_qnt > qnt_estoque || teste_qnt < 1);

            tab_produto[pos_produto].qnt -= teste_qnt;
            adicionar_venda (tab_venda, tl_vendas, teste_data, teste_codigo, teste_qnt);

            total_venda = teste_qnt * tab_produto[pos_produto].preco;

            printf("\n>> Venda realizada com sucesso!\n");
            printf(">> Total da Venda: RS%.2f\n", total_venda);
        }
        else
            printf("\n>> Nao ha unidades desse produto em estoque.\n");
    }
    else
        printf("\n>> Produto nao cadastrado.\n");
}

int produto_vendido (tp_venda tab_venda[], int tl, int cod_produto)
{
    int i, vendido = 0;

    for (i = 0; i < tl; i++)
    {
        if (tab_venda[i].produto == cod_produto)
            vendido = 1;
    }

    return vendido;
}

void apresentar_venda_pos (tp_venda tab_venda[], int tl_vendas, tp_produto tab_produto[], int tl_produtos, int pos)
{
    float total_venda;
    int pos_produto;
    tp_data data = tab_venda[pos].data;

    total_venda = calcular_total_venda_pos(tab_venda, tab_produto, tl_produtos, pos);
    pos_produto = buscar_pos_produto(tab_produto, tl_produtos, tab_venda[pos].produto);

    if (pos < tl_vendas && pos > -1)
    {
        printf("\n[Data da Venda]: %.2d/%.2d/%d", data.dia, data.mes, data.ano);
        printf("\n    > Codigo do Produto: %d", tab_venda[pos].produto);
        printf("\n    > Descricao: %s", tab_produto[pos_produto].nome);
        printf("\n    > Quantidade Vendida: %d", tab_venda[pos].qnt);
        printf("\n    > Total da Venda: RS%.2f", total_venda);

        printf("\n");
    }
}

void apresentar_vendas_produto (tp_venda tab_venda[], int tl_vendas, tp_produto tab_produto[], int tl_produtos, int cod_produto)
{
    int i;
    float total_vendas;

    if (produto_vendido(tab_venda, tl_vendas, cod_produto))
    {
        printf("\n[VENDAS DO PRODUTO: %d]\n", cod_produto);

        for (i = 0; i < tl_vendas; i++)
        {
            if (tab_venda[i].produto == cod_produto)
                apresentar_venda_pos(tab_venda, tl_vendas, tab_produto, tl_produtos, i);
        }

        total_vendas = calcular_total_vendas_produto(tab_venda, tl_vendas, tab_produto, tl_produtos, cod_produto);
        printf("\n>> Valor total das vendas: RS%.2f\n", total_vendas);
    }
    else
        printf("\n>> O produto nao foi vendido.\n");
}

void apresentar_vendas_data (tp_venda tab_venda[], int tl_vendas, tp_produto tab_produto[], int tl_produtos, tp_data data)
{
    int i;
    float total_vendas;

    printf("\n[VENDAS NA DATA: %.2d/%.2d/%d]\n", data.dia, data.mes, data.ano);

    for (i = 0; i < tl_vendas; i++)
    {
        if (datas_iguais(tab_venda[i].data, data))
            apresentar_venda_pos(tab_venda, tl_vendas, tab_produto, tl_produtos, i);
    }

    total_vendas = calcular_total_vendas_data(tab_venda, tl_vendas, tab_produto, tl_produtos, data);

    printf("\n>> Valor total das vendas: RS%.2f\n", total_vendas);
}

void apresentar_qnt_vendas_produto (tp_venda tab_venda[], int tl_vendas, tp_produto tab_produto[], int tl_produtos)
{
    int i, pos_produto;
    float total;

    printf("\n[QUANTIDADE DE VENDAS POR PRODUTO]:\n");

    for (i = 0; i < tl_vendas; i++)
    {
        total = calcular_total_venda_pos(tab_venda, tab_produto, tl_produtos, i);
        pos_produto = buscar_pos_produto(tab_produto, tl_produtos, tab_venda[i].produto);

        printf("\n[Codigo do Produto]: %d", tab_venda[i].produto);
        printf("\n    > Descricao: %s", tab_produto[pos_produto].nome);
        printf("\n    > Quantidade Vendida: %d", tab_venda[i].qnt);
        printf("\n    > Total Arrecadado: RS%.2f", total);

        printf("\n");
    }
}
