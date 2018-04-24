%include "io64.inc" 
	common y 8
	common b 800
section .data 
_L0: db "Enter a number", 0	; global string
_L1: db "read and write success!", 0	; global string
_L5: db "value of x for while", 0	; global string
_L10: db "value of z for if", 0	; global string
_L15: db "value of a for if/else", 0	; global string
_L19: db "math operators tests", 0	; global string
_L28: db "math tests success!", 0	; global string
_L17: db "SHOULD NOT GO HERE", 0	; global string
_L18: db "else success!", 0	; global string
_L12: db "if success!", 0	; global string
_L7: db "while success!", 0	; global string

section .text 
	global main
main:
	mov rbp, rsp
	mov r8, rsp
	add r8, -160
	mov [r8], rbp
	mov [r8+8],rsp
	mov rsp, r8
	PRINT_STRING _L0  ;standard write value 
	NEWLINE ;standard newline

	mov rax, y
	GET_DEC 8, [rax]

	mov rax, y
	mov rsi,[rax] ; load immediate value 
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline
	PRINT_STRING _L1  ;standard write value 
	NEWLINE ;standard newline
	mov rax, 0 
	mov [rsp+40],rax 

	mov rax, 16
	add rax, rsp
	mov rbx, [40 + rsp] 
	mov [rax], rbx 
	mov rax, 0 
	mov [rsp+48],rax 

	mov rax, 24
	add rax, rsp
	mov rbx, [48 + rsp] 
	mov [rax], rbx 
	mov rax, 2 
	mov [rsp+56],rax 

	mov rax, 32
	add rax, rsp
	mov rbx, [56 + rsp] 
	mov [rax], rbx 
	PRINT_STRING _L5  ;standard write value 
	NEWLINE ;standard newline

	mov rax, 16
	add rax, rsp
	mov rsi,[rax] ; load immediate value 
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline

_L30:   ;WHILE TOP target 

	mov rax, 16
	add rax, rsp
	mov rax, [rax] 
	mov [rsp + 64], rax
	mov rbx, 5
	mov rax, [rsp+64]
	cmp rax, rbx ;EXPR LESSTHAN 
	setl al ;EXPR LESSTHAN 
	mov rbx, 1 ;set rbx to one to filter rax
	and rax, rbx ;filter RAX
	mov [rsp+64], rax 
	mov rax, [rsp+64] ;WHILE expression expr 
	CMP rax, 0 ;WHILE compare
	JE _L31, ;WHILE branch out
	PRINT_STRING _L7  ;standard write value 
	NEWLINE ;standard newline

	mov rax, 16
	add rax, rsp
	mov rax, [rax] 
	mov [rsp + 72], rax
	mov rbx, 1
	mov rax, [rsp+72]
	add rax, rbx ;EXPR ADD 
	mov [rsp+72], rax 
	mov rax, [rsp+72] 
	mov [rsp+80],rax 

	mov rax, 16
	add rax, rsp
	mov rbx, [80 + rsp] 
	mov [rax], rbx 
	JMP _L30 ; WHILE jump back 

_L31:   ;WHILE END target 
	PRINT_STRING _L10  ;standard write value 
	NEWLINE ;standard newline

	mov rax, 24
	add rax, rsp
	mov rsi,[rax] ; load immediate value 
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline

_L32:   ;IF TOP target 

	mov rax, 24
	add rax, rsp
	mov rax, [rax] 
	mov [rsp + 72], rax
	mov rbx, 1
	mov rax, [rsp+72]
	cmp rax, rbx ;EXPR LESSTHAN 
	setl al ;EXPR LESSTHAN 
	mov rbx, 1 ;set rbx to one to filter rax
	and rax, rbx ;filter RAX
	mov [rsp+72], rax 
	mov rax, [rsp+72] ;IF expression expr 
	CMP rax, 0 ;IF compare
	JE _L33, ;IF branch to ELSE
	PRINT_STRING _L12  ;standard write value 
	NEWLINE ;standard newline

	mov rax, 24
	add rax, rsp
	mov rax, [rax] 
	mov [rsp + 80], rax
	mov rbx, 1
	mov rax, [rsp+80]
	add rax, rbx ;EXPR ADD 
	mov [rsp+80], rax 
	mov rax, [rsp+80] 
	mov [rsp+88],rax 

	mov rax, 24
	add rax, rsp
	mov rbx, [88 + rsp] 
	mov [rax], rbx 
	JMP _L32 ;IF S1 end

_L33:   ;ELSE target 
	PRINT_STRING _L15  ;standard write value 
	NEWLINE ;standard newline

	mov rax, 32
	add rax, rsp
	mov rsi,[rax] ; load immediate value 
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline

_L34:   ;IF TOP target 

	mov rax, 32
	add rax, rsp
	mov rax, [rax] 
	mov [rsp + 80], rax
	mov rbx, 1
	mov rax, [rsp+80]
	cmp rax, rbx ;EXPR LESSTHAN 
	setl al ;EXPR LESSTHAN 
	mov rbx, 1 ;set rbx to one to filter rax
	and rax, rbx ;filter RAX
	mov [rsp+80], rax 
	mov rax, [rsp+80] ;IF expression expr 
	CMP rax, 0 ;IF compare
	JE _L35, ;IF branch to ELSE
	PRINT_STRING _L17  ;standard write value 
	NEWLINE ;standard newline
	JMP _L34 ;IF S1 end

_L35:   ;ELSE target 
	PRINT_STRING _L18  ;standard write value 
	NEWLINE ;standard newline
	PRINT_STRING _L19  ;standard write value 
	NEWLINE ;standard newline
	mov rax, 5
	mov [rsp + 88], rax
	mov rbx, 5
	mov rax, [rsp+88]
	add rax, rbx ;EXPR ADD 
	mov [rsp+88], rax 
	mov rax, [rsp + 88] 
	mov [rsp + 96], rax
	mov rbx, 5
	mov rax, [rsp+96]
	sub rax, rbx ;EXPR SUB 
	mov [rsp+96], rax 
	mov rsi, [rsp+96] 
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline
	mov rax, 10
	mov [rsp + 104], rax
	mov rbx, 5
	mov rax, [rsp+104]
	xor rdx, rdx 
	idiv rbx ;EXPR DIV 
	mov [rsp+104], rax 
	mov rax, [rsp + 104] 
	mov [rsp + 112], rax
	mov rbx, 2
	mov rax, [rsp+112]
	imul rax, rbx ;EXPR TIMES 
	mov [rsp+112], rax 
	mov rsi, [rsp+112] 
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline
	mov rax, 5
	mov [rsp + 120], rax
	mov rbx, 5
	mov rax, [rsp+120]
	add rax, rbx ;EXPR ADD 
	mov [rsp+120], rax 
	mov rax, [rsp + 120] 
	mov [rsp + 144], rax
	mov rax, 5
	mov [rsp + 128], rax
	mov rbx, 1
	mov rax, [rsp+128]
	imul rax, rbx ;EXPR TIMES 
	mov [rsp+128], rax 
	mov rax, [rsp + 128] 
	mov [rsp + 136], rax
	mov rbx, 1
	mov rax, [rsp+136]
	xor rdx, rdx 
	idiv rbx ;EXPR DIV 
	mov [rsp+136], rax 
	mov rbx,[rsp+136] 
	mov rax, [rsp+144]
	sub rax, rbx ;EXPR SUB 
	mov [rsp+144], rax 
	mov rsi, [rsp+144] 
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline
	PRINT_STRING _L28  ;standard write value 
	NEWLINE ;standard newline
	mov rax, 5 
	mov [rsp+152],rax 
	mov rbx, 200 ;assign value to rbx

	mov rax, b
	add rax, rbx ;add offset and stack pointer 
	mov rbx, [152 + rsp] 
	mov [rax], rbx 
	mov rbx, 200 ;assign value to rbx

	mov rax, b
	add rax, rbx ;add offset and stack pointer 
	mov rsi,[rax] ; load immediate value 
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline

	mov rbp, [rsp] ;FUNC end restore old BP
	mov rsp, [rsp+8] ;FUNC end restore old SP
	mov rsp, rbp	 ;stack and BP need to be same on exit for main
	ret
