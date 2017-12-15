#
# I2C interface is wired to Arduino PORTC bits
# 4 and 5, with 4 being data and 5 being clock,
# so these symbols give us the values needed
#
      .set PORTC,0x08
      .set DDIRC,0x07
      .set PINC,0x06
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
    .comm tempV1, 1
    .comm tempV2, 1
    .global tempV1
    .global tempV2

#
# Program code
#
     .text
     .extern delayMicroseconds
     .global setupTherm
     .global readTherm
     
setupTherm: 
      ; set pins to output mode
      sbi   DDIRC,SDA
      sbi   DDIRC,SCL
      call  clockDelay        ; wait to make sure PORTC ready
      call  startBit          ; send start bit
      call  sendAddress92     ; send 7SEG address 0x92
      call  sendControl01      ; send control params 0x01
      call  sendByte          ; send byte 0x60 
      call  stopBit           ; send stop bit
      call  clockDelay
      call  startBit          ; send start bit
      call  sendAddress92     ; send 7SEG address 0x92
      call  sendControl00      ; send control params 0x00
      call  stopBit           ; send stop bit
      call  clockDelay        ; wait to allow settling
      ret                     ; all done, return to main program!

readTherm:

      ; set pins to output mode
      call startBit           ; send start bit
      call sendAddress93      ; send 7SEG address 0x93
      call readI2CByte
      sts  tempV1, r24
      call readI2CByte        ; read a while clock is high.
      sts  tempV2, r24
      call stopBit            ; send stop bit
      call clockDelay         ; wait to allow settling
      ret                     ; all done, return to main program!
# 
# Delay for creating our clock period (50usec delay)
# 

clockDelay:       
      push  r18       
      push  r19       
      push  r20       
      push  r22
      push r24    
      ldi   r24, 50       
      ldi   r25, 0       
      call  delayMicroseconds       
      pop r24
      pop   r22       
      pop   r20       
      pop   r19       
      pop   r18       
      ret
  
#
# I2C 1 bit transmission: SDA high while clock is high
# 
oneBit:
      cbi   PORTC,SCL
      call  clockDelay
      sbi   PORTC,SDA
      sbi   PORTC,SCL
      call  clockDelay
      cbi   PORTC,SCL
      call  clockDelay
      ret

#
# I2C 0 bit transmission: SDA low while clock is high
# 
zeroBit:
      cbi   PORTC,SCL
      call  clockDelay
      cbi   PORTC,SDA
      sbi   PORTC,SCL
      call  clockDelay
      cbi   PORTC,SCL
      call  clockDelay
      ret
      
#
# I2C startbit: a high-to-low transition on SDA while clock is high
#
startBit:
      sbi   PORTC,SDA    ; set data bit high ;start bit
      sbi   PORTC,SCL    ; set clock high ;
      call  clockDelay       ; leave clock high long enough
      cbi   PORTC,SDA    ; set data bit low (this causes the transition)
      call  clockDelay       ; keep clock high for a while
      cbi   PORTC,SCL    ; finally bring clock low
      cbi   PORTC,SDA    ; bring data line low
      call  clockDelay       ; leave clock low for long enough
      ret

#
# I2C stopit: a low-to-high transition on SDA while clock is high
#
stopBit:
      
      cbi   PORTC,SDA   ;data low
      sbi   PORTC,SCL   ;clock high
      call  clockDelay      ;clock high
      sbi   PORTC,SDA   ;data high
      call  clockDelay      ;clock high
      cbi   PORTC,SCL   ;data low
      cbi   PORTC,SDA    ; bring data line low
      call  clockDelay      ;clock low
      ret

#
# Subcommand (control byte): Must transmit the byte value 0x01
#  - in binary, 01000111
#
sendControl01:
      call  zeroBit
      call  zeroBit
      call  zeroBit
      call  zeroBit
      call  zeroBit
      call  zeroBit
      call  zeroBit
      call  oneBit
      call  zeroBit     
      ret

#
# Subcommand (control byte): Must transmit the byte value 0x00
#  - in binary, 01000111
#
sendControl00:
      call  zeroBit
      call  zeroBit
      call  zeroBit
      call  zeroBit
      call  zeroBit
      call  zeroBit
      call  zeroBit
      call  zeroBit
      call  zeroBit    
      ret

#
# I2C LED address transmission: must transmit the byte value 0x92
#
sendAddress92:
      call  oneBit
      call  zeroBit
      call  zeroBit
      call  oneBit
      call  zeroBit
      call  zeroBit
      call  oneBit
      call  zeroBit
      call  zeroBit     
      ret

#
# I2C LED address transmission: must transmit the byte value 0x93
#
sendAddress93:
      call  oneBit
      call  zeroBit
      call  zeroBit
      call  oneBit
      call  zeroBit
      call  zeroBit
      call  oneBit
      call  oneBit
      call  zeroBit     
      ret



#
# Instruction transmit: for us the instruction should be 0x60 
#  - all zeros means data is in order of: ctl d1 d2 d3 d4
#
sendByte:
      call  zeroBit
      call  oneBit
      call  oneBit
      call  zeroBit
      call  zeroBit
      call  zeroBit
      call  zeroBit
      call  zeroBit
      call  zeroBit   
      ret

# 
# Read a byte from the I2C bus (assumes all initialization has been done, 
# and that the start bit and address have been sent; this only reads one 
# byte (and does the ACK), caller must complete the communication, reading   
# more bytes, sending a stop bit, etc.) 
# - leaves data byte in register r24; does not corrupt any other registers 
#       

readI2CByte:       
     push  r20               ; save r20 in case program is using it       
     cbi   PORTC, SDA        ; ensure output is low to switch to input       
     cbi   DDIRC, SDA        ; change SDA pin to input rather than output         
     ldi   r20, 8            ; we're going to read 8 bits       
     clr   r24               ; r24 will hold data byte, so start it at 0 

readLoop:       
     lsl   r24               ; shift the bits we have so far one place to left         
     sbi   PORTC, SCL        ; set clock high       
     call  clockDelay        ; keep high for a bit, gives time for therm to send bit       
     sbic  PINC, SDA         ; skip next instruction if input bit is 0       
     ori   r24, 0x01         ; input bit is a 1, so put a 1 into data byte          
     cbi   PORTC, SCL        ; set clock low       
     call  clockDelay        ; keep low for a bit       
     dec   r20               ; decrement our loop counter       
     brne  readLoop          ; if it is still not 0, go back to top of loop 

readDone:       
     sbi   DDIRC, SDA        ; change SDA pin back to output       
     cbi   PORTC, SDA        ; set data line low for ACK       
     sbi   PORTC, SCL        ; start ACK clock period       
     call  clockDelay        ; hold high       
     cbi   PORTC, SCL        ; set clock low       
     call  clockDelay        ; hold low       
     pop   r20               ; restore original r20       
     ret   
