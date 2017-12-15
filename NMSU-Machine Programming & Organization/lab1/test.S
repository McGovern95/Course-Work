
    .file "test.S"
    .text
    .global testf
testf:
      ldi    r17, 0x20
      out    0x04, r17
      ldi    r16, 50
all:  ldi    r17, 0x20
      out    0x05, r17
      ldi    r18, 0xff
dl1:  ldi    r19, 0xff
dl2:  nop
      nop
      nop
      nop
      dec    r19
      brne   dl2
      dec    r18
      brne   dl1
      ldi    r17, 0x00
      out    0x05, r17
      ldi    r18, 0xff
dl3:  ldi    r19, 0xff
dl4:  nop
      nop
      nop
      nop
      dec    r19
      brne   dl4
      dec    r18
      brne   dl3
      dec    r16
      brne   all
      ret
    
