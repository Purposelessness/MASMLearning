#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define N 81

int main() {
  setlocale(LC_CTYPE, "");

  wchar_t *translit = L"a\0" // А
                      L"b\0" // Б
                      L"v\0" // В
                      L"g\0" // Г
                      L"d\0" // Д
                      L"e\0" // Е
                      L"zh"  // Ж
                      L"z\0" // З
                      L"i\0" // И
                      L"i\0" // Й
                      L"k\0" // К
                      L"l\0" // Л
                      L"m\0" // М
                      L"n\0" // Н
                      L"o\0" // О
                      L"p\0" // П
                      L"r\0" // Р
                      L"s\0" // С
                      L"t\0" // Т
                      L"u\0" // У
                      L"f\0" // Ф
                      L"kh"  // Х
                      L"ts"  // Ц
                      L"ch"  // Ч
                      L"sh"  // Ш
                      L"\0\0"// Щ
                      L"ie"  // Ъ
                      L"y\0" // Ы
                      L"\0\0"// Ь
                      L"e\0" // Э
                      L"iu"  // Ю
                      L"ia"; // Я

  wchar_t str[N];
  wchar_t out[N * 4] = {};

  fgetws(str, N, stdin);

  // wchar_t c;
  // for (int i = 0; i < N; ++i) {
  //   c = str[i];
  //   if (c == L'\0') {
  //     break;
  //   }
  //   wprintf(L"%d ", c);
  // }

  asm("xor  rsi, rsi             \n\t" // rsi = 0 --> `in`
      "xor  rdi, rdi             \n" // rdi = 0 --> `out`
      "process_str:              \n" // Loop of string processing
      "  cmp  rsi, 316           \n" // Check if in array bounds
      "  jg   end_process        \n" // If not --> goto exit (loop ends)
      "  xor  rax, rax           \n"
      "  mov  eax, [%[in] + rsi] \n" // Get letter from input string
      "  add  rsi, 4             \n"
      "  cmp  eax, 0             \n" // Check if input string ends
      "  je   end_process        \n"

      "ru_lower_check:           \n" // Check if letter is ru and in lower case
      "  cmp  eax, 1072          \n" // 'а'
      "  jl   ru_upper_check     \n"
      "  cmp  eax, 1103          \n" // 'я'
      "  jg   write_ch           \n" // If false --> just write letter to outer string
      "  jmp  transliterate_lowercase \n" // If true --> goto transliteration

      "ru_upper_check:           \n" // Check if letter is ru and in UPPER case
      "  cmp  eax, 1040          \n" // 'А'
      "  jl   write_ch           \n" // If false --> just write letter to outer string
      "  cmp  eax, 1071          \n" // 'Я'
      "  jg   write_ch           \n"
      "  jmp  transliterate_uppercase \n" // If true --> goto transliteration (UPPER)

      "write_ch:                  \n" // Write letter to outer string
      "  mov  [%[out] + rdi], eax \n"
      "  add  rdi, 4              \n"
      "  jmp  process_str         \n" // Continue loop

      "transliterate_uppercase:  \n"
      "  sub  eax, 1040          \n" // Find index of letter in ru alphabet
      "  xor  rcx, rcx           \n"
      "  mov  ecx, eax           \n"
      "  shl  ecx, 3             \n"
      "  mov  eax, [%[translit] + rcx]    \n" // Get letter from 'dictionary'
      "  cmp  eax, 0             \n" // Check if letter exists
      "  je   trans_upper_exit   \n" // If not --> goto exit
      "  sub  eax, 32            \n" // Make letter UPPER case
      "  mov  [%[out] + rdi], eax \n" // Write letter to outer string
      "  add  rdi, 4             \n"
      "  add  rcx, 4             \n"
      "  mov  eax, [%[translit] + rcx]    \n" // Write second char of transliteration
      "  cmp  eax, 0             \n" // Check if it exists
      "  je   trans_upper_exit   \n" // If not --> goto exit
      "  mov  [%[out] + rdi], eax\n" // Else write letter to outer string
      "  add  rdi, 4             \n"
      "trans_upper_exit:         \n" // Exit of transliteration
      "  jmp  process_str        \n" // Continue loop

      "transliterate_lowercase:  \n"
      "  sub  eax, 1072          \n"
      "  xor  rcx, rcx           \n"
      "  mov  ecx, eax           \n"
      "  shl  ecx, 3             \n"
      "  mov  eax, [%[translit] + rcx]   \n"
      "  cmp  eax, 0             \n"
      "  je   trans_lower_exit   \n"
      "  mov  [%[out] + rdi], eax\n"
      "  add  rdi, 4             \n"
      "  add  rcx, 4             \n"
      "  mov  eax, [%[translit] + rcx]    \n"
      "  cmp  eax, 0             \n"
      "  je   trans_lower_exit   \n"
      "  mov  [%[out] + rdi], eax\n"
      "  add  rdi, 4             \n"
      "trans_lower_exit:         \n"
      "  jmp  process_str        \n"

      "end_process:              \n"
      "  mov dword ptr [%[out] + rdi], 0 \n"
      : // Output parameters
      : [out] "b"(out), [in] "d"(str), [translit] "r"(translit)
      : "rsi", "rdi", "rcx", "rax"); // Clobber list

  wprintf(L"%ls", out);

  return 0;
}
