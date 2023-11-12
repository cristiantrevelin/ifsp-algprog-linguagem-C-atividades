#include <stdio.h>
#include "mystring.h"
#define TAM_NOME 80

typedef struct
{
    int codigo, qnt;
    char nome[TAM_NOME];
    float preco;

} tp_produto;

void adicionar_produto (tp_produto tab_produto[], int *tl, int cod, int qnt, char nome[], float preco)
{
    tab_produto[*tl].codigo = cod;
    tab_produto[*tl].qnt = qnt;
    tab_produto[*tl].preco = preco;

    copiar_string(nome, tab_produto[*tl].nome);

    (*tl)++;
}

int novo_cod_produto_valido (tp_produto tab_produto[], int tl, int codigo)
{
    int i, valido = 1;

    for (i = 0; i < tl; i++)
    {
        if (tab_produto[i].codigo == codigo)
            valido = 0;
    }

    return valido;
}

int cod_produto_existe (tp_produto tab_produto[], int tl, int codigo)
{
    int i, valido = 0;

    for (i = 0; i < tl; i++)
    {
        if (tab_produto[i].codigo == codigo)
            valido = 1;
    }

    return valido;
}

void cadastrar_produto (tp_produto tab_produto[], int *tl)
{
    int teste_codigo, teste_qnt;
    float teste_preco;

    int codigo_valido, tamanho_nome;

    char teste_nome[TAM_NOME];

    printf("\n[CADASTRO DE PRODUTO]:");

    do
    {
        printf("\n.. Insira o codigo..: ");
        scanf("%d", &teste_codigo);

        codigo_valido = novo_cod_produto_valido(tab_produto, *tl, teste_codigo);

        if (!codigo_valido)
            printf("    >> Codigo invalido, tente novamente.");

    } while (!codigo_valido);

    do
    {
        printf(".. Insira a quantidade..: ");
        scanf("%d", &teste_qnt);

        if (teste_qnt < 0)
            printf("    >> Quantidade invalida, tente novamente.\n");

    } while (teste_qnt < 0);

    do
    {
        fflush(stdin);

        printf(".. Insira o nome..: ");
        ler_string(teste_nome, TAM_NOME);

        tamanho_nome = contar_string_tl(teste_nome);

        if (tamanho_nome < 2)
            printf("    >> Nome invalido, tente novamente.\n");

    } while (tamanho_nome < 2);

    do
    {
        printf(".. Insira o preco..: ");
        scanf("%f", &teste_preco);

        if (teste_preco <= 0)
            printf("    >> Preco invalido, tente novamente.\n");

    } while (teste_preco <= 0);

    adicionar_produto(tab_produto, tl, teste_codigo, teste_qnt, teste_nome, teste_preco);
}

void alterar_produto (tp_produto tab_produto[], int tl, int codigo)
{
    int i, teste_qnt, tamanho_nome;
    float teste_preco;

    char teste_nome[TAM_NOME];

    for (i = 0; i < tl; i++)
    {
        if (tab_produto[i].codigo == codigo)
        {
            printf("\n[ALTERACAO DE PRODUTO]:");

            do
            {
                printf("\n>> Quantidade atual: %d", tab_produto[i].qnt);
                printf("\n.. Insira a nova quantidade..: ");
                scanf("%d", &teste_qnt);

                if (teste_qnt < 0)
                    printf("    >> Quantidade invalida, tente novamente.\n");

            } while (teste_qnt < 0);

            do
            {
                fflush(stdin);

                printf("\n>> Nome atual: %s", tab_produto[i].nome);
                printf("\n.. Insira o novo nome..: ");
                ler_string(teste_nome, TAM_NOME);

                tamanho_nome = contar_string_tl(teste_nome);

                if (tamanho_nome < 2)
                    printf("    >> Nome invalido, tente novamente.\n");

            } while (tamanho_nome < 2);

            do
            {
                printf("\n>> Preco atual RS:%.2f", tab_produto[i].preco);
                printf("\n.. Insira o novo preco..: ");
                scanf("%f", &teste_preco);

                if (teste_preco <= 0)
                    printf("    >> Preco invalido, tente novamente.\n");

            } while (teste_preco <= 0);

            tab_produto[i].qnt = teste_qnt;
            tab_produto[i].preco = teste_preco;

            copiar_string(teste_nome, tab_produto[i].nome);
        }
    }
}

void excluir_produto (tp_produto tab_produto[], int *tl, int codigo)
{
    int i, j;

    for (i = 0; i < *tl; i++)
    {
        if (tab_produto[i].codigo == codigo)
        {
            (*tl)--;

            for (j = i; j < *tl; j++)
                tab_produto[j] = tab_produto[j + 1];
        }
    }
}

float calcular_total_estoque (tp_produto tab_produto[], int tl)
{
    float total = 0;
    int i;

    for (i = 0; i < tl; i++)
        total += tab_produto[i].qnt * tab_produto[i].preco;

    return total;
}

void apresentar_produto_pos (tp_produto tab_produto[], int tl, int pos_produto)
{
    if (pos_produto < tl && pos_produto > -1)
    {
        printf("\n[Codigo do Produto]: %d", tab_produto[pos_produto].codigo);
        printf("\n    > Descricao: %s", tab_produto[pos_produto].nome);
        printf("\n    > Quantidade em Estoque: %d", tab_produto[pos_produto].qnt);
        printf("\n    > Preco: RS%.2f", tab_produto[pos_produto].preco);

        printf("\n");
    }
}

void apresentar_produto_cod (tp_produto tab_produto[], int tl, int codigo)
{
    int i;

    for (i = 0; i < tl; i++)
    {
        if (tab_produto[i].codigo == codigo)
            apresentar_produto_pos(tab_produto, tl, i);
    }
}

int buscar_pos_produto (tp_produto tab_produto[], int tl, int codigo)
{
    int i, pos = 0;

    for (i = 0; i < tl; i++)
    {
        if (tab_produto[i].codigo == codigo)
            pos = i;
    }

    return pos;
}

void comprar_produto (tp_produto tab_produto[], int tl, int codigo, int qnt_comprada)
{
    int i;

    for (i = 0; i < tl; i++)
    {
        if (tab_produto[i].codigo == codigo)
            tab_produto[i].qnt += qnt_comprada;
    }
}

void listar_produtos (tp_produto tab_produto[], int tl)
{
    int i;

    printf("\n[LISTA DE PRODUTOS CADASTRADOS]:\n");

    for (i = 0; i < tl; i++)
        apresentar_produto_pos(tab_produto, tl, i);
}

void apresentar_balancete (tp_produto tab_produto[], int tl)
{
    int i;
    float valor_estoque, total_estoque;

    printf("\n[LISTA DE PRODUTOS - COM BALANCETE]:\n");

    for (i = 0; i < tl; i++)
    {
        valor_estoque = tab_produto[i].qnt * tab_produto[i].preco;

        apresentar_produto_pos(tab_produto, tl, i);
        printf("    > Valor em Estoque: RS%.2f\n", valor_estoque);
    }

    total_estoque = calcular_total_estoque(tab_produto, tl);
    printf("\n\n>> Total em Estoque: RS%.2f\n", total_estoque);
}

void apresentar_produtos_estoque_baixo (tp_produto tab_produto[], int tl)
{
    int i, produto_apresentado = 0;

    printf("\n[RELACAO DE PRODUTOS COM ESTOQUE BAIXO (MENOR QUE 5)]:\n");

    for (i = 0; i < tl; i++)
    {
        if (tab_produto[i].qnt < 5)
        {
            apresentar_produto_pos(tab_produto, tl, i);
            produto_apresentado = 1;
        }
    }

    if (!produto_apresentado)
        printf("\n>> Nao ha produtos com estoque baixo.\n");
}

void cadastrar_tab_produtos_teste (tp_produto tab_produto[], int *tl)
{
    *tl = 0;

    adicionar_produto(tab_produto, tl, 1, 25, "Produto A", 4.50);
    adicionar_produto(tab_produto, tl, 2, 6, "Produto B", 22.99);
    adicionar_produto(tab_produto, tl, 3, 32, "Produto C", 7.00);
    adicionar_produto(tab_produto, tl, 4, 54, "Produto D", 1.99);
    adicionar_produto(tab_produto, tl, 5, 17, "Produto E", 45.99);
    adicionar_produto(tab_produto, tl, 6, 11, "Produto F", 10.50);
    adicionar_produto(tab_produto, tl, 7, 22, "Produto G", 3.50);
    adicionar_produto(tab_produto, tl, 8, 2, "Produto H", 2.00);
    adicionar_produto(tab_produto, tl, 9, 4, "Produto I", 79.99);
    adicionar_produto(tab_produto, tl, 10, 0, "Produto J", 5.50);
}
