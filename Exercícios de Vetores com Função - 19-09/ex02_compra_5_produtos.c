#include <stdio.h>
#define PRODUTOS_TF 5

int escrever_produtos (float vetor[], int vetor_tf, char mensagem[])
{
    int vetor_tl = 0;
    float valor;

    do
    {
        printf(mensagem, vetor_tl+1);
        scanf("%f", &valor);

        if (valor > 0)
        {
            vetor[vetor_tl] = valor;
            vetor_tl++;
        }
        else
            printf("      >> Valor invalido, tente novamente.\n");

    } while (vetor_tl < vetor_tf);

    return vetor_tl;
}

void apresentar_cupom (float produtos[], int produtos_tl)
{
    int i;

    printf("\n    >> CUPOM DE COMPRA <<");
    printf("\n-----------------------------");

    for (i = 0; i < produtos_tl; i++)
    {
        printf("\n   Produto: %.2d - RS%7.2f", i+1, produtos[i]);
    }

    printf("\n-----------------------------");
}

float somar_produtos (float produtos[], int produtos_tl)
{
    int i;
    float soma = 0;

    for (i = 0; i < produtos_tl; i++)
        soma += produtos[i];

    return soma;
}

float buscar_valor_mais_caro (float produtos[], int produtos_tl)
{
    int i;
    float mais_caro;

    for (i = 0; i < produtos_tl; i++)
    {
        if (produtos[i] > mais_caro || i == 0)
            mais_caro = produtos[i];
    }

    return mais_caro;
}

int buscar_cod_mais_barato (float produtos[], int produtos_tl)
{
    int i, mais_barato, codigo_mais_barato;

    for (i = 0; i < produtos_tl; i++)
    {
        if (produtos[i] < mais_barato || i == 0)
        {
            mais_barato = produtos[i];
            codigo_mais_barato = i;
        }
    }

    return codigo_mais_barato;
}

void main ()
{
    int cod_mais_barato;
    float produtos[PRODUTOS_TF], produtos_tl, soma_produtos, produto_mais_caro;

    produtos_tl = escrever_produtos(produtos, PRODUTOS_TF, ".. Insira o Valor do Produto %d em RS ");

    soma_produtos = somar_produtos(produtos, produtos_tl);
    produto_mais_caro = buscar_valor_mais_caro(produtos, produtos_tl);
    cod_mais_barato = buscar_cod_mais_barato(produtos, produtos_tl);

    apresentar_cupom(produtos, produtos_tl);

    printf("\n\n>> Total da Compra: RS%.2f", soma_produtos);
    printf("\n>> Valor do Produto Mais Caro: RS%.2f", produto_mais_caro);
    printf("\n>> Codigo do Produto Mais Barato: %.2d", cod_mais_barato+1);

    printf("\n");

}
