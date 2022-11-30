.section .rodata
  hello_str:
    .string "Hello world!\n"
    .set hello_str_len, . - hello_str - 1
  newline_str:
    .string "\n"

.section .data
  input_number: 
    .long 32768

#; Uninitialized data
.bss
  number_str:
    .space 12  #; first symbol is 8 if num < 0
    .set number_str_len, 12
  buf:
    .space 1

.section .text

#; Input:
#; dx:ax -- number
#; Output:
#; number_str -- number to oct string
make_str:
  push cx
  push rdi
  std

  mov  rdi, offset number_str
  add  rdi, 11

#; process ax
  mov  cl, 5
ax_loop:
  push ax

  and  ax, 0x7
  add  ax, '0'
  stosb

  pop  ax
  shr  ax, 3

  loop ax_loop

#; between ax and dx
  push dx

  and  dx, 0x3
  shl  dx, 1
  add  ax, dx
  add  ax, '0'
  stosb

  pop  dx
  mov  ax, dx
  shr  ax, 2

#; process dx
  mov  cl, 6
dx_loop:
  push ax

  and  ax, 0x7
  add  ax, '0'
  stosb

  pop  ax
  shr  ax, 3

  loop dx_loop

  cld
  pop rdi
  pop  cx

  ret

invert_number:
  test ax, ax
  jz   ax_null
  dec  ax
  jmp  neg_number

ax_null:
  dec  dx

neg_number:
  xor  ax, 0xffff
  xor  dx, 0xffff

  ret

.global  _start
_start:
#; Insert number
  mov  edx, -555555

  mov  ax, dx
  shr  edx, 16

  rcl  dx, 1
  jnc  positive
  rcr  dx, 1
  call invert_number
  jmp  make_number_str

positive:
  shr  dx, 1

make_number_str:
  call make_str

  mov  rax, 1
  mov  rdi, 1
  mov  rsi, offset number_str
  mov  rdx, number_str_len
  syscall

  mov  rax, 1
  mov  rdi, 1
  mov  rsi, offset newline_str
  mov  rdx, 1
  syscall

  mov  rax, 60
  mov  rdi, 0
  syscall
