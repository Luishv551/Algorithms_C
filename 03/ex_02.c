//Making a function that does a 2 degree equation calculation

#include <math.h>

int calcularEquacaoSegundoGrau(double a, double b, double c, double *x1, double *x2) {
    double delta = pow(b, 2) - 4 * a * c;

    if(delta < 0) {
        // não há raízes reais
        return 1;
    }
    else if(delta == 0) {
        // há uma raiz real
        *x1 = (-b / (2 * a));
        *x2 = (-b / (2 * a));
        return 2;
    }
    else {
        // há duas raízes reais
        *x1 = (-b + sqrt(delta)) / (2 * a);
        *x2 = (-b - sqrt(delta)) / (2 * a);
        return 3;
    }
}

#include <stdio.h>

int main() {
    double a, b, c, x1, x2;
    int result;


    printf("Digite os coeficientes a, b e c da equacao de 2o grau:\n");
    scanf("%lf %lf %lf", &a, &b, &c);

    result = calcularEquacaoSegundoGrau(a, b, c, &x1, &x2); //Colocamos o & pois precisamos enviar para a função o endereço de memoria

    switch (result)
    {

    case 1:
        {
        printf("Não existem raizes reais para delta");
        break;
        }

    case 2:
        {
        printf("Existe uma raiz real para delta");
        printf("Raiz: %lf", x1);
        break;
        }

     case 3:
        {
        printf("Existem duas raizes reais para delta\n");
        printf("Raiz1: %lf \n Raiz2: %lf", x1, x2);
        break;
        }
    }
}
