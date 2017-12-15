# MorseCode.S
# Feb 9, 2016

#--------------------------------------------------------------------
    .data
morse_table: # binary representation of Morse code: 0: dot; 1: dash
    .byte 0b01, 0b1000, 0b1010, 0b100, 0b0, 0b0010
morse_width: # the number of binary digits in each character
    .byte 2, 4, 4, 3, 1, 4
ascii_table: # the English symbols encoded by the above Morse code 
    .byte 'A', 'B', 'C', 'D', 'E', 'F'

table_length:
    .byte 6

    .comm val, 1
    .comm width, 1
    .comm ascii, 1
    .global val, ascii, width

#---------------------------------------------------------------------
    .text
    .global decode_morse

decode_morse:
    push R31
    push R30
    push R29
    push R28
    push R27
    push R26
    
    LDI R31, hi8(morse_table) ; initialize high byte of Z
    LDI R30, lo8(morse_table) ; initialize low byte of Z
    LDI R29, hi8(ascii_table) ; initialize high byte of Y
    LDI R28, lo8(ascii_table) ; initialize low byte of Y
    LDI R27, hi8(morse_width) ; initialize high byte of X
    LDI R26, lo8(morse_width) ; initialize low byte of X

    # ENTER YOUR CODE BELOW

    
    
    pop R26
    pop R27
    pop R28
    pop R29
    pop R30
    pop R31
    RET

