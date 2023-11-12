#include <stdio.h>
#define NOME_TF 50
#include "mystring.h"

typedef struct
{
    int codigo, estoque;
    char nome[NOME_TF];
    float preco;

} tp_produto;

void cadastrar_produto (tp_produto *produto)
{
    int teste_codigo, teste_estoque;
    char teste_nome[NOME_TF];
    float teste_preco;

    printf("\n[CADASTRO DE PRODUTO]\n");

    printf("\n.. Insira o codigo..: ");
    scanf("%d", &teste_codigo);

    do
    {
        printf(".. Insira o nome..: ");
        ler_string(teste_nome, NOME_TF);

        if (contar_string_tl(teste_nome) < 2)
            printf("    > Nome invalido, tente novamente.\n");

    } while (contar_string_tl(teste_nome) < 2);

    do
    {
        printf(".. Insira a quantidade em estoque..: ");
        scanf("%d", &teste_estoque);

        if (teste_estoque < 0)
            printf("    > Quantidade invalida, tente novamente.\n");

    } while (teste_estoque < 0);

    do
    {
        printf(".. Insira o preco..: RS");
        scanf("%f", &teste_preco);

        if (teste_preco <= 0)
            printf("    > Preco invalido, tente novamente.\n");

    } while (teste_preco <= 0);

    (*produto).codigo = teste_codigo;
    (*produto).estoque = teste_estoque;
    (*produto).preco = teste_preco;

    copiar_string(teste_nome, (*produto).nome);
}

void importar_produtos_arquivo (FILE *arquivo, char nome[], tp_produto tab_produtos[], int *tl)
{
    int codigo, estoque;
    char descricao[NOME_TF];
    float preco;

    arquivo = fopen(nome, "r");

    if (arquivo == NULL)
        printf("\n>> Nao foi possivel abrir o arquivo.");
    else
    {
        /*while (fscanf(arquivo, "%d\n%s\n%d %f", &codigo, descricao, &estoque, &preco))
        {
            printf("oi ");
            tab_produtos[*tl].codigo = codigo;
            tab_produtos[*tl].estoque = estoque;
            tab_produtos[*tl].preco = preco;

            copiar_string(descricao, tab_produtos[*tl].nome);

            (*tl)++;
        } */
            fscanf(arquivo, "%d\n%s\n%d %f", &codigo, descricao, &estoque, &preco);
            tab_produtos[*tl].codigo = codigo;
            tab_produtos[*tl].estoque = estoque;
            tab_produtos[*tl].preco = preco;

            copiar_string(descricao, tab_produtos[*tl].nome);

            (*tl)++;
        fclose(arquivo);
    }
}

void apresentar_produto_pos (tp_produto tab_produto[], int tl, int pos_produto)
{
    if (pos_produto < tl && pos_produto > -1)
    {
        printf("\n[Codigo do Produto]: %d", tab_produto[pos_produto].codigo);
        printf("\n    > Descricao: %s", tab_produto[pos_produto].nome);
        printf("\n    > Quantidade em Estoque: %d", tab_produto[pos_produto].estoque);
        printf("\n    > Preco: RS%.2f", tab_produto[pos_produto].preco);

        printf("\n");
    }
}

void listar_produtos (tp_produto tab_produto[], int tl)
{
    int i;

    printf("\n[LISTA DE PRODUTOS]:\n");

    for (i = 0; i < tl; i++)
        apresentar_produto_pos(tab_produto, tl, i);
}
