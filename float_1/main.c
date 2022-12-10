#include <stdio.h>
#include <stdlib.h>

double ldexp(double value, int exp);

int main() {
  printf("Enter value: ");
  double val;
  scanf("%lf", &val);

  printf("Enter exp: ");
  int exp;
  scanf("%d", &exp);

  double result = ldexp(val, exp);

  printf("Result is:\n\t%.9lf\n", result);

  return 0;
}
