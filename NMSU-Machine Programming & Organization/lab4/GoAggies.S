#
# Global data(times)
#   
        .data
        .comm times, 1
        .global times
        .extern delay

#code

         .text
         .global GoAggies
         .global MorseOutput
         .global done 

GoAggies:
          ldi r18, 0b00100000
          out 0x04, r18
          lds r18, times 
          ldi r19, 0 
MorseOutput:

    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xdc
    ldi r23, 0x05
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;dash
    ldi r17, 0b0
    out 0x05, r17
    

    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;interspace

    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xdc
    ldi r23, 0x05
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ; dash
      ldi r17, 0b0
    out 0x05, r17

    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;interspace
    
    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ; dotG
      ldi r17, 0b0
    out 0x05, r17

    ldi r22, 0xdc
    ldi r23, 0x05
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ; letterspace
     
    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xdc
    ldi r23, 0x05
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ; dash
      ldi r17, 0b0
    out 0x05, r17
    
    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;interspace


    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xdc
    ldi r23, 0x05
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ; dash
      ldi r17, 0b0
    out 0x05, r17

    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;interspace

    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xdc
    ldi r23, 0x05
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ; dashO
    ldi r17, 0b0
    out 0x05, r17

    ldi r22, 0xbb
    ldi r23, 0x08
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ; wordspace

    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;dot
      ldi r17, 0b0
    out 0x05, r17

    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;interspace

    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xdc
    ldi r23, 0x05
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ; dashA
      ldi r17, 0b0
    out 0x05, r17

    ldi r22, 0xdc
    ldi r23, 0x05
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ; letterspace

    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xdc
    ldi r23, 0x05
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;dash
      ldi r17, 0b0
    out 0x05, r17

    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;interspace

    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xdc
    ldi r23, 0x05
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ; dash
      ldi r17, 0b0
    out 0x05, r17

    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;interspace
    
    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ; dotG
      ldi r17, 0b0
    out 0x05, r17

    ldi r22, 0xdc
    ldi r23, 0x05
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ; letterspace

    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xdc
    ldi r23, 0x05
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;dash
      ldi r17, 0b0
    out 0x05, r17

    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;interspace

    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xdc
    ldi r23, 0x05
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ; dash
      ldi r17, 0b0
    out 0x05, r17

    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;interspace
    
    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ; dotG
      ldi r17, 0b0
    out 0x05, r17

    ldi r22, 0xdc
    ldi r23, 0x05
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ; letterspace

    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;dot
      ldi r17, 0b0
    out 0x05, r17

    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;interspace

    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;dotI
      ldi r17, 0b0
    out 0x05, r17

    ldi r22, 0xdc
    ldi r23, 0x05
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ; letterspace

    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ; dotE
      ldi r17, 0b0
    out 0x05, r17

    ldi r22, 0xdc
    ldi r23, 0x05
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ; letterspace

    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;dot
      ldi r17, 0b0
    out 0x05, r17

    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;interspace

    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;dot
      ldi r17, 0b0
    out 0x05, r17

    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;interspace

    ldi r17, 0b00100000
    out 0x05, r17
    ldi r22, 0xf4
    ldi r23, 0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay ;dotS
      ldi r17, 0b0
    out 0x05, r17

     DEC r18
     cp  r18,r19
     BRLO done
     RJMP MorseOutput

    done: 
       RJMP done 


           










