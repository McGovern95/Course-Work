
.data
.text

.global initAD
.global readAD
  

initAD:
  
  ldi r18, 0b00111111
  sts 0x007E, r18

  ldi r19, 0b10000111
  sts 0x007A, r19 
  
  ret


readAD:

  ldi r20, 0b01100000
  
  OR r20, r24
  sts 0x007C, r20
  
  ldi r19, 0b11000111
  sts 0x007A, r19
  
  
  
  L0: 
  lds r19, 0x007A
  SBRC r19, 6
      jmp L0

      lds r24, 0x0079
      clr r25

      ret
