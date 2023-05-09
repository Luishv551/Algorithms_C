int main()
{

int x=5;
int *y;
y=&x; //recebendo o endereco de memoria da variavel x como conteudo

printf("Conteudo de x: %d\n", x);
printf("Endereco de x: %d\n", &x);

printf("Conteudo de y: %d\n", y);
printf("Conteudo da variavel apontada por y: %d\n", *y);


*y = *y * 3;

printf("Conteudo de x * 3 acessando atraves do ponteiro: %d\n", *y);
printf("Conteudo de x: %d\n", x);


}
