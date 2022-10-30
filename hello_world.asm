assume ss:my_stack, cs:my_code, ds:my_data

my_stack segment stack 
    dw 12 dup('?')
my_stack ends

my_data segment
    hello_message db 'Hello world!', 0ah, 0dh, '$'
my_data ends

my_code segment

display_message proc near
    push ax

    mov ah, 09h
    int 21h

    pop ax
    ret
display_message endp

main proc far
    push ds
    sub ax, ax
    push ax

    mov ax, my_data
    mov ds, ax

    mov dx, offset hello_message
    call display_message

    ret
main endp

my_code ends

end main