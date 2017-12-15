
#
# Global data (x1, x2, and x3)
#
    .data
    .comm x1,1
    .global x1
    .comm x2,1
    .global x2
    .comm x3,1
    .global x3

#
# Program code (addition function)
#
    .text
    .global addition
addition:
    ldi  r17, 0x20
    out  0x04, r17
    ldi   r17, 0x00
    out 0x05, r17
    lds  r18, x1
    ldi  r21, 5 
    add  r18, r21
    lds  r19, x2
    lds  r20, x3
    ldi  r22, -4
    add  r19, r22
    ldi r23,  -8
    add r20,  r23
    add r20,  r20
    add r18,  r19
    add r18,  r20
    sts  x3, r18
    ldi r17,  0x20
    out 0x05, r17
    ret
    
