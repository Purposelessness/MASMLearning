#include <locale.h>
#include <stdio.h>
#include <wchar.h>

#define N 81

int main() {
  setlocale(LC_CTYPE, "");

  wchar_t in[N];
  wchar_t out[N];

  fgetws(in, N, stdin);

  asm("xor rsi, rsi                 \n"

      "process_str:                 \n"
      "  cmp  rsi, 316              \n"
      "  jg   end_process           \n"
      "  xor  rax, rax              \n"
      "  mov  eax, [%[in] + rsi]    \n"
      "  cmp  eax, 0                \n"
      "  je   end_process           \n"

      "latin_check:                 \n"
      "  cmp  eax, 65               \n"
      "  jl   oct_check             \n"
      "  cmp  eax, 90               \n"
      "  jg   write_ch              \n"
      "  add  eax, 32               \n"
      "  jmp  write_ch              \n"

      "oct_check:                   \n"
      "  cmp  eax, 48               \n"
      "  jl   write_ch              \n"
      "  cmp  eax, 56               \n"
      "  jg   write_ch              \n"
      "  sub  eax, 48               \n"
      "  sub  eax, 8                \n"
      "  neg  eax                   \n"
      "  add  eax, 48               \n"
      "  jmp  write_ch              \n"

      "write_ch:                    \n"
      "  mov  [%[out] + rsi], eax   \n"
      "  add  rsi, 4                \n"
      "  jmp  process_str           \n"

      "end_process:                 \n"
      "  mov dword ptr [%[out] + rsi], 0 \n"
      :
      : [in] "r"(in), [out] "r"(out)
      : "rsi", "rax");

  wprintf(L"%ls", out);

  return 0;
}
