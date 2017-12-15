#
# Global data (gender,age, and fat)
#
    .data
    .comm gender,1
    .global gender
    .comm age,1
    .global age
    .comm fat,1
    .global fat  

#
# program code (LED test) 
#
    .text
    .global lightup
lightup:
     lds  r19, gender
     lds  r20,  age
     lds  r21,  fat
     ldi  r22,  0x01 
     ldi  r23,  0x02 


     

     ldi  r18, 0b00110001 
     out  0x04, r18 ; 0x04 is I/O address of DDRB
     out  0x05, r18 ; 0x05 is the I/O address of PORTB
     ret
