#include <stdio.h>
#include "vendas.h"

#define TAB_PRODUTOS_TF 50
#define TAB_VENDAS_TF 50

int menu_principal ()
{
    int opcao;

    do
    {
        system("cls");

        printf("\n[MENU INICIAL] ------------------------------------------------------------------------------");
        printf("\n[1] Acessar o Menu de Produtos");
        printf("\n[2] Acessar o Menu de Vendas");

        printf("\n\n[0] Sair do programa");
        printf("\n---------------------------------------------------------------------------------------------");

        printf("\n.. Insira uma das opcoes acima..: ");
        scanf("%d", &opcao);

    } while (opcao < 0 || opcao > 2);

    return opcao;
}

int menu_produtos ()
{
    int opcao;

    do
    {
        system("cls");

        printf("\n[MENU - PRODUTOS] ---------------------------------------------------------------------------");
        printf("\n[1] Incluir produto");
        printf("\n[2] Alterar produto");
        printf("\n[3] Pesquisar produto pelo codigo");
        printf("\n[4] Comprar produto");
        printf("\n[5] Listar produtos");
        printf("\n[6] Apresentar balancete");

        printf("\n\n[0] Voltar ao Menu Inicial");
        printf("\n---------------------------------------------------------------------------------------------");

        printf("\n.. Insira uma opcao valida..: ");
        scanf("%d", &opcao);

    } while (opcao < 0 || opcao > 6);

    return opcao;
}

int menu_vendas ()
{
    int opcao;

    do
    {
        system("cls");

        printf("\n[MENU - VENDAS] -----------------------------------------------------------------------------");
        printf("\n[1] Incluir venda");
        printf("\n[2] Apresentar vendas de um produto");
        printf("\n[3] Apresentar vendas por data");
        printf("\n[4] Apresentar total arrecadado em um mes");

        printf("\n\n[0] Voltar ao Menu Inicial");
        printf("\n---------------------------------------------------------------------------------------------");

        printf("\n.. Insira uma opcao valida..: ");
        scanf("%d", &opcao);

    } while (opcao < 0 || opcao > 4);

    return opcao;
}

void main ()
{
    tp_produto produto;
    tp_venda venda;
    tp_data data;

    FILE *arquivo_produtos, *arquivo_vendas;

    int tab_produtos_tl = 0, tab_vendas_tl = 0;
    tp_produto tab_produtos[TAB_PRODUTOS_TF];
    tp_venda tab_vendas[TAB_VENDAS_TF];

    int menu_atual = 0, programa_ativo = 1;
    int cod_produto, qnt, mes;

    float total_arrecadado;

    char enter;

    do
    {
        if (menu_atual == 1)
        {
            switch (menu_produtos())
            {
            case 0:

                menu_atual = 0;
                break;

            case 1:

                cadastrar_produto(arquivo_produtos, "produtos.bin");
                break;

            case 2:

                printf("\n.. Insira o codigo do produto que deseja alterar..: ");
                scanf("%d", &cod_produto);

                alterar_produto(arquivo_produtos, "produtos.bin", cod_produto);

                break;

            case 3:

                if (tab_produtos_tl > 0)
                {
                    printf("\n.. Insira o codigo do produto que deseja excluir..: ");
                    scanf("%d", &cod_produto);

                    if (produto_vendido(tab_vendas, tab_vendas_tl, cod_produto))
                        printf("\n>> O produto ja foi vendido e nao pode ser excluido.\n");

                    else if (cod_produto_existe(tab_produtos, tab_produtos_tl, cod_produto))
                    {
                        excluir_produto(tab_produtos, &tab_produtos_tl, cod_produto);
                        printf("\n>> Produto excluido com sucesso!\n");
                    }
                    else
                        printf("\n>> Codigo invalido.\n");
                }
                else
                    printf("\n>> Nao ha produtos cadastrados.\n");

                break;

            case 4:

                if (tab_produtos_tl > 0)
                {
                    printf("\n.. Insira o codigo do produto que deseja pesquisar..: ");
                    scanf("%d", &cod_produto);

                    if (cod_produto_existe(tab_produtos, tab_produtos_tl, cod_produto))
                        apresentar_produto_cod(tab_produtos, tab_produtos_tl, cod_produto);
                    else
                        printf("\n>> Codigo invalido.\n");
                }
                else
                    printf("\n>> Nao ha produtos cadastrados.\n");

                break;

            case 5:

                listar_produtos(arquivo_produtos, "produtos.bin");
                break;

            case 7:

                if (tab_produtos_tl > 0)
                    apresentar_balancete(tab_produtos, tab_produtos_tl);
                else
                    printf("\n>> Nao ha produtos cadastrados.\n");

                break;

            case 8:

                if (tab_produtos_tl > 0)
                    apresentar_produtos_estoque_baixo(tab_produtos, tab_produtos_tl);
                else
                    printf("\n>> Nao ha produtos cadastrados.\n");

                break;

            default:
                break;
            }

            if (menu_atual == 1)
            {
                fflush(stdin);
                printf("\n[PRESSIONE ENTER PARA CONTINUAR].");
                scanf("%c", &enter);
            }
        }

        else if (menu_atual == 2)
        {
            switch (menu_vendas())
            {
            case 0:

                menu_atual = 0;
                break;

            case 1:

                if (tab_vendas_tl < TAB_VENDAS_TF && tab_produtos_tl > 0)
                    realizar_venda(tab_vendas, &tab_vendas_tl, tab_produtos, tab_produtos_tl);
                else
                    printf("\n>> Nao e possivel realizar uma nova venda.\n");

                break;

            case 2:

                if (tab_vendas_tl > 0)
                {
                    printf("\n.. Insira o codigo do produto que deseja ver as vendas..: ");
                    scanf("%d", &cod_produto);
                    apresentar_vendas_produto(tab_vendas, tab_vendas_tl, tab_produtos, tab_produtos_tl, cod_produto);
                }
                else
                    printf("\n>> Nao foi realizada nenhuma venda.\n");

                break;

            case 3:

                if (tab_vendas_tl > 0)
                {
                    printf("\n");
                    cadastrar_data(&data);
                    apresentar_vendas_data(tab_vendas, tab_vendas_tl, tab_produtos, tab_produtos_tl, data);
                }
                else
                    printf("\n>> Nao foi realizada nenhuma venda.\n");

                break;

            case 4:

                if (tab_vendas_tl > 0)
                    apresentar_qnt_vendas_produto(tab_vendas, tab_vendas_tl, tab_produtos, tab_produtos_tl);
                else
                    printf("\n>> Nao foi realizada nenhuma venda.\n");

                break;

            case 5:

                if (tab_vendas_tl > 0)
                {
                    do
                    {
                        printf("\n.. Insira o mes..: ");
                        scanf("%d", &mes);

                        if (mes > 31 || mes < 1)
                            printf("    >> Mes invalido, tente novamente.");

                    } while (mes > 31 || mes < 1);

                    total_arrecadado = calcular_total_vendas_mes(tab_vendas, tab_vendas_tl, tab_produtos, tab_produtos_tl, mes);
                    printf("\n>> Total arrecadado no mes %d: RS%.2f\n", mes, total_arrecadado);
                }
                else
                    printf("\n>> Nao foi realizada nenhuma venda.\n");

                break;

            default:
                break;
            }

            if (menu_atual == 2)
            {
                fflush(stdin);
                printf("\n[PRESSIONE ENTER PARA CONTINUAR].");
                scanf("%c", &enter);
            }
        }

        else
        {
            switch (menu_principal())
            {
            case 0:

                programa_ativo = 0;
                break;

            case 1:

                menu_atual = 1;
                break;

            case 2:

                menu_atual = 2;
                break;

            default:
                break;
            }
        }

    } while (programa_ativo);

    system("cls");
    printf("\n>> Programa Encerrado! :]\n");
}
