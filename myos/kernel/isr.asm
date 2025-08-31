; kernel/isr.asm
global isr_timer

isr_timer:
    ; ACKNOWLEDGE FIRST!
    mov al, 0x20
    out 0x20, al
    
    ; DEBUG: Print single character
    pusha
    mov edi, 0xB8000 + 160  ; Second line
    mov byte [edi], 'T'
    mov byte [edi+1], 0x2A
    popa
    
    iret
; Add this after isr_timer
global isr_keyboard

isr_keyboard:
    pusha
    ; Acknowledge interrupt FIRST
    mov al, 0x20
    out 0x20, al
    out 0xA0, al
    
    ; Call C keyboard handler
    extern keyboard_handler
    call keyboard_handler
    
    popa
    iret
