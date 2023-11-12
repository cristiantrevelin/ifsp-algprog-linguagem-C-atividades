#include <stdio.h>
#include <locale.h>

void main() {
    long int x, y, x_simp, y_simp, ii, divisor, minor_num;
    setlocale(LC_ALL, "Portuguese");

    printf(">> SIMPLIFICADOR DE FRAÇÕES <<\n");
    printf("    Digite o Numerador: ");
    scanf("%d", &x);
    printf("    Digite o Denominador: ");
    scanf("%d", &y);

    minor_num = (x < y) ? x : y;
    x_simp = x;
    y_simp = y;
    divisor = 1;

    ii = 2;
    while (ii <= minor_num && y != 0) {

        if (x_simp % ii == 0 && y_simp % ii == 0) {
            x_simp = x_simp / ii;
            y_simp = y_simp / ii;

            divisor = divisor * ii;
        }
        else {
            ii++;
        }
    }

    if (y != 0)
        printf("\n>> Simplificando %d/%d por %d, temos %d/%d\n", x, y, divisor, x_simp, y_simp);
    else
        printf("Não é possível dividir por 0.");
}
