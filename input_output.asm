assume cs:my_code, ss:my_stack

my_stack segment stack 
    dw 12 dup('?')
my_stack ends

my_data segment
    new_line db 0ah, 0dh, '$'
    info_message db '> Enter your name', 0ah, 0dh, '$'
    your_name_message db '> Your name is $'
    name_buffer db 64 dup('$')
my_data ends

my_code segment

print proc near
    push ax

    mov ah, 9h
    int 21h

    pop ax
    ret
print endp

getch proc near
    push ax

    mov ah, 8h
    int 21h

    mov dl, al

    pop ax
    ret
getch endp

print_ch proc near
    push ax

    mov al, dl
    mov ah, 2h
    int 21h

    pop ax
    ret
print_ch endp

scan proc near
    mov bx, offset name_buffer
start_loop:
    call getch
    call print_ch

    cmp dl, 0dh
    je end_loop

    mov [bx], dl
    add bx, 1

    jmp start_loop
end_loop:
    mov dx, offset new_line
    call print

    ret
scan endp

main proc far
    push ds
    sub ax, ax
    push ax

    mov ax, my_data
    mov ds, ax

    mov dx, offset info_message
    call print

    call scan 
    mov dx, offset your_name_message
    call print
    mov dx, offset name_buffer
    call print

    ret
main endp

my_code ends

end main