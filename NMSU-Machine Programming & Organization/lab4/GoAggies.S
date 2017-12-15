#
# Global data(times)
#   
        .data
        .comm times. 1
        .global times
        .extern delay

#code

         .text
         .global GoAggies

GoAggies:
          ldi r18, 0b00100000
          out 0x04, r18
          lds r18, times 
timescheck:
        ldi r19, 0
        cp r21, r19
        brne progstart
        call progend
          
progstart:







progend:
      ret

dot:
    ldi r17, 0b00100000
    out, 0x05 r17
    ldi r22,  0xf4
    ldi r23,0x01
    ldi r24, 0x00
    ldi r25, 0x00
    call delay
dash:
    ldi r17, 0b00100000
    out, 0x05 r17
    ldi r22, 0xdc
    ldi r23, 0x05
    ldi r24, 0x00
    ldi r25, 0x00
call delay

interletterspace:

letterspace:
     ldi r22, 0xac
     ldi r23, 0x05
     

wordspace:

           










