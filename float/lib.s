.global poly
.global old_poly

#; Input:
#; x: double  -> xmm0
#; n: int     -> rdi
#; c: double* -> rsi
#; Output:
#; rax
poly:
  movq  rax, xmm0
  push  rax
  fld qword ptr [rsp]
  fldz
  test  rdi, rdi
  jz    poly_end
  mov   rcx, rdi
horner:
    fmul  st(1)
    fadd qword ptr [rsi + rcx * 8 - 8]
    loop  horner
poly_end:
  fstp qword ptr [rsp]
  pop   rax
  movq  xmm0, rax
  ret

#; Input:
#; x: double  -> xmm0
#; n: int     -> rdi
#; c: double* -> rsi
old_poly:
  movsd xmm1, xmm0
  subsd xmm0, xmm0
  test  rdi, rdi
  jz    old_poly_end
  mov   rcx, rdi
old_horner:
   mulsd xmm0, xmm1
   addsd xmm0, [rsi + rcx * 8 - 8]
   loop  old_horner
old_poly_end:
  ret
