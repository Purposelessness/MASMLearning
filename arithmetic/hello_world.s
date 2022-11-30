.section .rodata
  hello_str:
    .string "Hello world!\n"
    .set hello_str_len, . - hello_str - 1

#; Uninitialized data
.bss
  number_str:
    .space 11
    .set number_str_len, 11

.section .text
.global  _start
_start:
  #; mov  rax, 4
  #; mov  rbx, 1
  #; mov  rcx, offset hello_str
  #; mov  rdx, hello_str_len
  #; int  0x80
  mov  rax, 1
  mov  rdi, 1
  mov  rsi, offset hello_str
  mov  rdx, hello_str_len
  syscall

  mov  ax, -35

  #; mov  rax, 1
  #; mov  rbx, 0
  #; int  0x80
  mov  rax, 60
  mov  rdi, 0
  syscall
