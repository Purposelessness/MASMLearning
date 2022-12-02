#include <stdio.h>
#include <stdlib.h>

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
  for (int i = n - 1; i > -1; --i) {
    test *= x;
    test += constants[i];
  }

  double result = poly(x, n, constants);
  printf("Result is:\n%lf\n", result);
  printf("Test is:\n%lf\n", test);

  free(constants);

  return 0;
}
