.global ldexp

#; val: double -> xmm0
#; exp: int    -> rdi
ldexp:
  push rdi
  fild dword ptr [rsp]
  movq rax, xmm0
  movq [rsp], rax
  fld qword ptr [rsp]
  fscale
  fst qword ptr [rsp]
  pop  rax
  movq xmm0, rax
  ret
