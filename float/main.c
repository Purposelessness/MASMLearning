#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern double poly(double x, int n, double *c);

int main() {
  double x;
  printf("Enter x:\n");
  scanf("%lf", &x);

  int n;
  printf("Enter number of constants:\n");
  scanf("%d", &n);

  double *constants = malloc(n * sizeof(double));
  printf("Enter constants:\n");
  char c;
  for (int i = 0; i < n; ++i) {
    scanf("%lf%c", &constants[i], &c);
  }

  double test = 0;
  clock_t c_time = clock();
  for (int i = n - 1; i > -1; --i) {
    test *= x;
    test += constants[i];
  }
  c_time = clock() - c_time;

  clock_t asm_time = clock();
  double result = poly(x, n, constants);
  asm_time = clock() - asm_time;

  printf("(asm) Result is:\n\t%lf (%ld : %lf)\n", result, asm_time,
         (double)asm_time / CLOCKS_PER_SEC);
  printf("(c) Test is:\n\t%lf (%ld : %lf)\n", test, c_time,
         (double)c_time / CLOCKS_PER_SEC);

  free(constants);

  return 0;
}
