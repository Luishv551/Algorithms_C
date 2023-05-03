//Week 03 - Functions

void increment(int* num1, int* num2) {
  *num1 += 5;
  *num2 += 5;
}

int main() {
  int a = 10, b = 20;
  increment(&a, &b);
  printf("a = %d, b = %d\n", a, b);
  return 0;
}
