int main()
{

int x=5;
int *y;
y=&x; //recebendo o endereco de memoria da variavel x como conteudo

printf("Conteudo de x: %d\n", x);
printf("Endereco de x: %d\n", &x);

printf("Conteudo de y: %d\n", y);
printf("Conteudo da variavel apontada por y: %d\n", *y);


*y = x * 3;
printf("Conteudo de x: %d", x);
}
