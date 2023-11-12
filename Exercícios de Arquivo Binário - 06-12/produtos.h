#include <stdio.h>
#include "mystring.h"
#define TAM_NOME 80

typedef struct
{
    int codigo, qnt;
    char nome[TAM_NOME];
    float preco;

} tp_produto;

int cod_produto_existe (FILE *arquivo, char *nome, int codigo)
{
    int existe = 0;
    tp_produto produto;

    fseek(arquivo, 0, SEEK_SET);

    while (fread(&produto, sizeof(tp_produto), 1, arquivo) == 1)
    {
        if (produto.codigo == codigo)
            existe = 1;
    }

    return existe;
}

void cadastrar_produto (FILE *arquivo, char *nome)
{
    int teste_codigo, teste_qnt;
    float teste_preco;

    int codigo_existe, tamanho_nome;

    char teste_nome[TAM_NOME];

    tp_produto produto;

    arquivo = fopen(nome, "ab+");

    if (arquivo != NULL)
    {
        printf("\n[CADASTRO DE PRODUTO]:");

        do
        {
            printf("\n.. Insira o codigo..: ");
            scanf("%d", &teste_codigo);

            codigo_existe = cod_produto_existe(arquivo, nome, teste_codigo);

            if (codigo_existe)
                printf("    >> Codigo invalido, tente novamente.");

        } while (codigo_existe);

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

        produto.codigo = teste_codigo;
        produto.qnt = teste_qnt;
        produto.preco = teste_preco;
        copiar_string(teste_nome, produto.nome);

        fwrite(&produto, sizeof(tp_produto), 1, arquivo);
        fclose(arquivo);

        printf("\n>> Arquivo cadastrado com sucesso!\n");
    }
    else
        printf("\n>> Nao foi possivel abrir o arquivo.\n");
}

void alterar_produto (FILE *arquivo, char *nome, int codigo)
{
    tp_produto produto;

    int pos = 0, teste_qnt, tamanho_nome, encontrado = 0;
    float teste_preco;

    char teste_nome[TAM_NOME];

    arquivo = fopen(nome, "rb+");

    if (arquivo != NULL)
    {
        while (!encontrado)
        {
            if (fread(&produto, sizeof(tp_produto), 1, arquivo) == 1)
            {
                pos++;

                if (produto.codigo == codigo)
                {
                    printf("\n[ALTERACAO DE PRODUTO]:");

                    do
                    {
                        printf("\n>> Quantidade atual: %d", produto.qnt);
                        printf("\n.. Insira a nova quantidade..: ");
                        scanf("%d", &teste_qnt);

                        if (teste_qnt < 0)
                            printf("    >> Quantidade invalida, tente novamente.\n");

                    } while (teste_qnt < 0);

                    do
                    {
                        fflush(stdin);

                        printf("\n>> Nome atual: %s", produto.nome);
                        printf("\n.. Insira o novo nome..: ");
                        ler_string(teste_nome, TAM_NOME);

                        tamanho_nome = contar_string_tl(teste_nome);

                        if (tamanho_nome < 2)
                            printf("    >> Nome invalido, tente novamente.\n");

                    } while (tamanho_nome < 2);

                    do
                    {
                        printf("\n>> Preco atual RS:%.2f", produto.preco);
                        printf("\n.. Insira o novo preco..: ");
                        scanf("%f", &teste_preco);

                        if (teste_preco <= 0)
                            printf("    >> Preco invalido, tente novamente.\n");

                    } while (teste_preco <= 0);

                    produto.qnt = teste_qnt;
                    produto.preco = teste_preco;
                    copiar_string(teste_nome, produto.nome);

                    encontrado = 1;
                }
            }
        }

        fseek(arquivo, sizeof(tp_produto)* (pos-1), SEEK_SET);
        fwrite(&produto, sizeof(tp_produto), 1, arquivo);

        fclose(arquivo);
        printf("\n>> Produto alterado com sucesso!\n");
    }
    else
        printf("\n>> Nao foi possivel abrir o arquivo.\n");
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

void apresentar_produto (tp_produto produto)
{
    printf("\n[Codigo do Produto]: %d", produto.codigo);
    printf("\n    > Descricao: %s", produto.nome);
    printf("\n    > Quantidade em Estoque: %d", produto.qnt);
    printf("\n    > Preco: RS%.2f", produto.preco);

    printf("\n");
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

void listar_produtos (FILE *arquivo, char *nome)
{
    tp_produto produto;

    arquivo = fopen(nome, "rb");

    if (arquivo != NULL)
    {
        while (fread(&produto, sizeof(tp_produto), 1, arquivo) == 1)
            apresentar_produto(produto);

        fclose(arquivo);
    }
    else
        printf("\n>> Nao foi possivel abrir o arquivo.\n");
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
