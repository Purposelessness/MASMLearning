#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TESTS_COUNT 10
#define TEST_MAX_NUMBER 30
#define TEST_MAX_CONSTANT_COUNT 20

extern double poly(double x, int n, double *c);

void run_tests();

int main() {
  char c;
  printf("Select program mode (default: 2):"
         "\n\t1. Manual input;"
         "\n\t2. Random generated test.\n");
  scanf("%c", &c);
  if (c == '2') {
    run_tests();
    return 0;
  }

  double x;
  printf("Enter x: ");
  scanf("%lf", &x);

  int n;
  printf("Enter number of constants: ");
  scanf("%d", &n);

  double *constants = malloc(n * sizeof(double));
  printf("Enter constants: ");
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

double generate_double() {
  float k = rand() % 10;
  double x = rand() % TEST_MAX_NUMBER;
  x /= pow(10.0, k);
  return x;
}

void run_tests() {
  srand(time(NULL));
  double *constants = malloc(2 * sizeof(double));
  for (int i = 0; i < TESTS_COUNT; ++i) {
    double x = generate_double();
    int n = rand() % TEST_MAX_CONSTANT_COUNT;
    constants = realloc(constants, n * sizeof(double));
    for (int i = 0; i < n; ++i) {
      constants[i] = generate_double();
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

    printf("TEST #%d:\n", i);
    printf("(asm) Result is:\n\t%lf (%ld : %lf)\n", result, asm_time,
           (double)asm_time / CLOCKS_PER_SEC);
    printf("(c) Test is:\n\t%lf (%ld : %lf)\n", test, c_time,
           (double)c_time / CLOCKS_PER_SEC);
    putchar('\n');
  }
  free(constants);
}
