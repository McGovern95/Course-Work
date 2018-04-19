%include "io64.inc" 
	common y 8
section .data 

_L0: db "FUCK MY LIFEs", 0
_L1: db "just kidding", 0
section .text 
	global main
main:
	mov rbp, rsp
	mov r8, rsp
	add r8, -64
	mov [r8], rbp
	mov [r8+8],rsp
	mov rsp, r8
	PRINT_STRING _L0  ;standard write value 
	NEWLINE ;standard newline
	PRINT_STRING _L1  ;standard write value 
	NEWLINE ;standard newline
	mov rax, 5
	mov [rsp + 24], rax
	mov rbx, 1
	mov rax, [rsp+24]
	add rax, rbx ;EXPR ADD 
	mov [rsp+24], rax 
	mov rax, [rsp + 24] 
	mov [rsp + 32], rax
	mov rbx, 12
	mov rax, [rsp+32]
	add rax, rbx ;EXPR ADD 
	mov [rsp+32], rax 
	mov rax, [rsp + 32] 
	mov [rsp + 40], rax
	mov rbx, 0
	mov rax, [rsp+40]
	add rax, rbx ;EXPR ADD 
	mov [rsp+40], rax 
	mov rsi, [rsp+40] 
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline
	mov rax, 10
	mov [rsp + 48], rax
	mov rbx, 5
	mov rax, [rsp+48]
	xor rdx, rdx 
	idiv rbx ;EXPR DIV 
	mov [rsp+48], rax 
	mov rsi, [rsp+48] 
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline
	mov rax, 5 
	mov [rsp+56],rax 

	mov rax, 16
	add rax, rsp
	mov rbx, [56 + rsp] 
	mov [rax], rbx 

	mov rax, 16
	add rax, rsp
	mov rsi,[rax] ; load immediate value 
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline

	mov rbp, [rsp] ;FUNC end restore old BP
	mov rsp, [rsp+8] ;FUNC end restore old SP
	mov rsp, rbp	 ;stack and BP need to be same on exit for main
	ret
