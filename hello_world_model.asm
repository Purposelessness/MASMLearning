.model small

.stack 100h
.data
    message db 'Hello, World$'

.code
start:
    mov ax, @data
    mov ds, ax
    
    mov dx, offset message
    mov ah, 9h
    int 21h
    
    mov ah, 8h
    int 21h
    
    mov ah, 4ch
    mov al, 00h
    int 21h
    
end start