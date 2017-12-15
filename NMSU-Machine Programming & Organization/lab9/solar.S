#
# Constants
#
      ; portB setup
      .set PORTB,0x05
      .set DDIRB,0x04
      .set MOTDATA,0
      .set MOTLATCH,4
      .set M1ENABLE,3
      .set BOARDLED, 5
      .set PINB, 0x03
      .set SWITCH1, 1
      .set SWITCH2, 2
      
      ; portD setup
      .set PORTD,0x0B
      .set DDIRD,0x0A
      .set MOTCLOCK,4
      .set M2ENABLE,3
      .set M4ENABLE,6
      .set M3ENABLE,5


#
# External symbols
#
    .extern delay

#
# Global data 
#
#     .data       
      .text
      .global control
      .global operatePanel, initializePanel      
      .global returnPanel, queryPanel, resetPanel, parkPanel
      .global moveWest
      .global readAD
      .global switch2

#
# Program code
#   

initializePanel:
       call resetPanel ; power up operation

 #
 # Moves the board to the west
 #
moveWest:
      ldi   r24, 0b00100111
      call  sendMotorByte
      call  delay1
      ldi   r24, 0b00000000
      call  sendMotorByte
#
# configures the second switch to move the board east on click 
#
switch2:
      cbi   DDIRB,SWITCH2   ; make pin 1 an input pin            
      sbi   PORTB,SWITCH2   ; turn on pullup resistor for pin 2         
      call  delay1          ; give pull-up time to settle
      
      SBIC  PINB, 0x02
      ret
      call returnPanel
      ret
#
# reads the light sensor 
#
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
   
returnPanel:
      cbi   DDIRB,SWITCH1   ; make pin 1 an input pin            
      sbi   PORTB,SWITCH1   ; turn on pullup resistor for pin 2         
      call  delay1          ; give pull-up time to settle
      
      L1:
      SBIS  PINB, 0x01
      jmp   L2              ; jump tp L2 if set  
      ldi   r24, 0b11011000 ; all motors return to east 0b11011000
      call  sendMotorByte
      jmp   L1

      L2:
      SBIC  PINB, 0x01
      jmp   L1      
      ldi   r24, 0b00000000   ; all motors off
      call  sendMotorByte
      ret
      
resetPanel:
      ;just calls returnPanel
      call returnPanel
      ret
     
control: 
      ; set ports B and D to be output
      ldi r20 ,0xff
      out DDIRB, r20
      out DDIRD, r20
      ret

      ; argument to sendMotorByte (r24) holds the 8-bits 
      ; to control 4 bidirectional motors: 
      ; (bits 2+3  for motor1, bits 0+6  for motor4, 
      ;  bits 1+4  for motor2, bits 5+7  for motor3)

#
# Delays for 1 and 255 milliseconds
#

delay1:
      ldi   r22, 0x01
      ldi   r23, 0x00
      ldi   r24, 0
      ldi   r25, 0
      call  delay
      ret
#
#Delays for much longer
#
delayTwo:
      ldi r22, 0xD0
      ldi r23, 0x07
      ldi r24, 0
      ldi r25, 0
      call delay
      ret

#  1 bit transmission
sendOneBit:
      cbi PORTD, MOTCLOCK
      call delay1
      sbi PORTB, MOTDATA
      sbi PORTD, MOTCLOCK
      call delay1
      cbi PORTB, MOTDATA
      call delay1
      ret
           
# 0 bit transmission
sendZeroBit:
      cbi PORTD, MOTCLOCK
      call delay1
      cbi PORTB, MOTDATA
      sbi PORTD, MOTCLOCK
      call delay1
      cbi PORTB, MOTDATA
      call delay1
      ret     

#
# latch now should be enabled (one) in order to release 
# the control pattern to the motor driver chips 
#
latchData:
      sbi   PORTB,MOTLATCH
      call  delay1
      ; make sure PWM outputs are on
      sbi   PORTB, M1ENABLE
      sbi   PORTD, M2ENABLE
      sbi   PORTD, M3ENABLE
      sbi   PORTD, M4ENABLE
      ret

# latch should be zero in order to send the control 
# pattern to shift register    
latchReset: 
      cbi   PORTB,MOTLATCH
      call  delay1
      ret

sendMotorByte:
      push  r15 ;push register r15
      push  r16 ;push register r16
      mov   r15, r24  ;moves r15 to r24
      call  latchReset 
      ldi   r16, 8
      
smbloop:
      lsl   r15
      brcs  smbone
      call  sendZeroBit   
      rjmp  smbdone
      
smbone:
      call  sendOneBit
      
smbdone:
      dec   r16
      brne  smbloop ;when r16 is not equal, continues
      call  latchData
      call  latchReset
      pop   r16
      pop   r15
      ret

