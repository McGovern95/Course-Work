
#
# I2C interface is wired to Arduino PORTC bits
# 4 and 5, with 4 being data and 5 being clock,
# so these symbols give us the values needed
#
      .set PORTC,0x08
      .set DDIRC,0x07
      .set SDA,4
      .set SCL,5

#
# I2C addresses of the components:
#  7-segment LED: 0x70
#  Digital Thermometer: 0x92
#  EEPROM: 0xA0

#
# Global data (none)
#
#   
    .data
    .comm symbol1, 1
    .global symbol1
    .comm symbol2, 1
    .global symbol2
    .comm symbol3, 1
    .global symbol3
    .comm symbol4, 1
    .global symbol4
    .comm symbolBit, 1
    .global symbolBit

    

alphabet:
    .byte '0', '1', '2', '3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z', ' '
LEDcode:
    .byte 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111, 0b01110111, 0b01111100, 0b00111001,0b01011110, 0b01111001, 0b01110001, 0b11111101,0b01110100, 0b10000110, 0b10001110, 0b11110000, 0b00111000,0b10100011, 0b11010100, 0b01011100, 0b01110011, 0b11100111, 0b01010000, 0b11101101, 0b01111000,0b10011100, 0b00011100, 0b11011100, 0b01110110, 0b11100110, 0b11011011, 0b00000000   
length:
    .byte 37
    
# external symbol (delay function)
    .extern delay

#
# Program code
#
     .text
     .global display_symbol
     .global display_one
display_symbol: 
      ; set pins to output mode
      sbi   DDIRC,SDA
      sbi   DDIRC,SCL
      call  delay1          ; wait to make sure PORTC ready
      call  startBit        ; send start bit
      call  sendAddress     ; send 7SEG address
      call  sendInst        ; send instruction
      call  sendControl     ; send control params
      call  show_symbol_four ;
      call  show_symbol_three ; send 4 data bytes 
      call  show_symbol_two ;   for the 4 display digits
      call  show_symbol_one ;
      call  stopBit         ; send stop bit
      call  delay1          ; wait to allow settling
      ret                   ; all done, return to main program!

 display_one: 
      ; set pins to output mode
      sbi   DDIRC,SDA
      sbi   DDIRC,SCL
      call  delay1          ; wait to make sure PORTC ready
      call  startBit        ; send start bit
      call  sendAddress     ; send 7SEG address
      call  sendInst        ; send instruction
      call  sendControl     ; send control params
      call  show_one ;
      call  show_one ; send 4 data bytes 
      call  show_one ;   for the 4 display digits
      call  show_one ;
      call  stopBit         ; send stop bit
      call  delay1          ; wait to allow settling
      ret                   ; all done, return to main program!


#
# Delay for 1 millisecond (saves/restores r18-r20)
#
delay1:
      push r18
      push r19
      push r20
      ldi  r22, 0x1
      ldi  r23, 0
      ldi  r24, 0
      ldi  r25, 0
      call delay
      pop  r20
      pop  r19
      pop  r18
      ret

#
# I2C startbit: a high-to-low transition on SDA while clock is high
#
startBit:
      sbi   PORTC,SDA    ; set data bit high
      sbi   PORTC,SCL    ; set clock high
      call  delay1       ; leave clock high long enough
      cbi   PORTC,SDA    ; set data bit low (this causes the transition)
      call  delay1       ; keep clock high for a while
      cbi   PORTC,SCL    ; finally bring clock low
      cbi   PORTC,SDA    ; bring data line low
      call  delay1       ; leave clock low for long enough
      ret

#
# I2C stopbit: a low-to-high transition on SDA while clock is high
#
stopBit:
      cbi PORTC, SDA ; set data bit low
      sbi PORTC, SCL ; set clock bit high
      call delay1    ; leave clock high long enough
      sbi PORTC, SDA ; set data bit high (this causes the transistion)
      call delay1    ; keep clock high for a while 
      cbi PORTC, SCL ; finally bring clock low
      call delay1    ; leave clock low for long enough
      ret
      

#
# I2C 1 bit transmission: SDA high while clock is high
# 
oneBit:
      sbi PORTC, SDA ; set data bit high
      sbi PORTC, SCL ; set clock bit high 
      call delay1;
      cbi PORTC, SCL
      call delay1
      ret

#
# I2C 0 bit transmission: SDA low while clock is high
# 
zeroBit:
      cbi PORTC, SDA ; set data bit low
      sbi PORTC, SCL ;set clock bit high
      call delay1;
      cbi PORTC, SCL
      call delay1
      ret

#
# I2C LED address transmission: must transmit the byte value 0x70
#
sendAddress:
      call  zeroBit
      call  oneBit
      call  oneBit
      call  oneBit
      call  zeroBit
      call  zeroBit
      call  zeroBit
      call  zeroBit
      call  zeroBit     ; for ack clock period
      ret

#
# Instruction transmit: for us the instruction should be 0x00 
#  - all zeros means data is in order of: ctl d1 d2 d3 d4
#
sendInst:
      call zeroBit
      call zeroBit
      call zeroBit
      call zeroBit
      call zeroBit
      call zeroBit
      call zeroBit
      call zeroBit
      call zeroBit    ;for ack clock period
      ret

#
# Subcommand (control byte): Must transmit the byte value 0x47
#  - in binary, 01000111
#
sendControl:
       call zeroBit
       call oneBit
       call zeroBit
       call zeroBit
       call zeroBit
       call oneBit
       call oneBit
       call oneBit
       call zeroBit
      ret


show_symbol_one:
        LDS r25, symbol1;
        call show_one_symbol
        ret

show_symbol_two:
        LDS r25, symbol2;
        call show_one_symbol
        ret

show_symbol_three:
        LDS r25, symbol3;
        call show_one_symbol
        ret

show_symbol_four:
        LDS r25, symbol4;
        call show_one_symbol
        ret

#
# Transmit a byte that will display a symbol
#  - you must figure it out!
#
show_one_symbol:

         push r31
         push r30
         push r29
         push r28

         ldi r31, hi8(alphabet)
         ldi r30, lo8(alphabet)
         ldi r29, hi8(LEDcode)
         ldi r28, lo8(LEDcode)

     L1: 
         ld r20, z+
         ld r21, y+
         cp r25, r20
         BRNE L1
         sts symbolBit, r21

         SBRC r21, 0x07
         call oneBit
         SBRS r21, 0x07
         call zeroBit

         SBRC r21, 0x06
         call oneBit
         SBRS r21, 0x06
         call zeroBit

         SBRC r21, 0x05
         call oneBit
         SBRS r21, 0x05
         call zeroBit

         SBRC r21, 0x04
         call oneBit
         SBRS r21, 0x04
         call zeroBit

         SBRC r21, 0x03
         call oneBit
         SBRS r21, 0x03
         call zeroBit

         SBRC r21, 0x02
         call oneBit
         SBRS r21, 0x02
         call zeroBit

         SBRC r21, 0x01
         call oneBit
         SBRS r21, 0x01
         call zeroBit
         
         SBRC r21, 0x00
         call oneBit
         SBRS r21, 0x00
         call zeroBit

         call zeroBit

      pop r28
      pop r29
      pop r30
      pop r31

      ret

 show_one: 
        LDS r25, symbol1;
        call show_one_symbol
        ret

          

