#include <stdio.h>

int bigger_num(int a, int b)

{

if (a > b){
    return a;
}

else{
    return b;
}

}

int main()
{

int x = 3, y = 1;
int result = bigger_num(x, y);

printf("%d", result );


}
