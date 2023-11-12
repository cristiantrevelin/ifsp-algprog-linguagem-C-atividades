#include <stdio.h>
#include "produto.h"
#define TAB_PRODUTOS_TF 50

int menu ()
{
    int opcao;

    do
    {
        system("cls");

        printf("\n-------------------------------------------- [MENU] --------------------------------------------");
        printf("\n>> PRODUTOS:");
        printf("\n    [1] Exportar para o Arquivo de Produtos");
        printf("\n    [2] Importar e Visualizar Arquivo de Produtos");

        printf("\n\n>> DISCIPLINAS:");
        printf("\n    [3] Exportar para o Arquivo de Disciplinas");
        printf("\n    [4] Importar e Visualizar Arquivo de Disciplinas");

        printf("\n\n[0] Sair do programa");
        printf("\n------------------------------------------------------------------------------------------------");

        printf("\n.. Insira uma opcao valida..: ");
        scanf("%d", &opcao);

    } while (opcao < 0 || opcao > 4);

    return opcao;
}

void main ()
{
    FILE *arquivo;
    tp_produto produto, tab_produtos[TAB_PRODUTOS_TF];

    int programa_ativo = 1, cadastrando_produto = 1, tab_produtos_tl = 0;
    char enter;

    while (programa_ativo)
    {
        switch (menu())
        {
        case 0:

            programa_ativo = 0;
            break;

        case 1:

            arquivo = fopen("produtos.txt", "a");

            if (arquivo == NULL)
                printf("\n>> Nao foi possivel abrir o arquivo.");
            else
            {
                do
                {
                    cadastrar_produto(&produto);
                    fprintf(arquivo, "%d\n%s\n%d %.2f\n", produto.codigo, produto.nome, produto.estoque, produto.preco);

                    printf("\n.. Deseja cadastrar um novo produto?\n[1] Sim\n[0] Nao\n..: ");
                    scanf("%d", &cadastrando_produto);

                } while (cadastrando_produto);

                fclose(arquivo);
            }

            break;

        case 2:

            importar_produtos_arquivo(arquivo, "produtos.txt", tab_produtos, &tab_produtos_tl);
            listar_produtos(tab_produtos, tab_produtos_tl);

            break;

        default:
            break;

        }

        if (programa_ativo)
        {
            fflush(stdin);
            printf("\n[PRESSIONE ENTER PARA CONTINUAR].");
            scanf("%c", &enter);
        }
    }
}
