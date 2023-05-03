#include <stdio.h>

int add_up(x)

{

if (x == 0){
return 0;
}

else{
return (x + add_up(x-1));
}

}

int main()
{

int x, result;
printf("Type a number: ");
scanf("%d",&x);

result = add_up(x);
printf("%d", result);

}
