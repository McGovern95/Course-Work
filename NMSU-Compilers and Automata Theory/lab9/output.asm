%include "io64.inc" 
section .data 
_L2: db "enter X", 0	; global string

section .text 
	global main
main:
	mov rbp, rsp; for main only
	mov r8, rsp
	add r8, -120
	mov [r8], rbp
	mov [r8+8],rsp
	mov rsp, r8 ;FUNC header new sp
	mov rax, 0 
	mov [rsp+64],rax 

	mov rax, 56
	add rax, rsp
	mov rbx, [64 + rsp] 
	mov [rax], rbx 

_L10:   ;WHILE TOP target 

	mov rax, 56
	add rax, rsp
	mov rax, [rax] 
	mov [rsp + 72], rax
	mov rbx, 5
	mov rax, [rsp+72]
	cmp rax, rbx ;EXPR LESSTHAN 
	setl al ;EXPR LESSTHAN 
	mov rbx, 1 ;set rbx to one to filter rax
	and rax, rbx ;filter RAX
	mov [rsp+72], rax 
	mov rax, [rsp+72] ;WHILE expression expr 
	CMP rax, 0 ;WHILE compare
	JE _L11, ;WHILE branch out
	PRINT_STRING _L2  ;standard write value 
	NEWLINE ;standard newline

	mov rax, 56
	add rax, rsp
	mov rbx, [rax] 
	shl rbx, 3 ;dereference array size 

	mov rax, 16
	add rax, rsp
	add rax, rbx ;add offset and stack pointer 
	GET_DEC 8, [rax]

	mov rax, 56
	add rax, rsp
	mov rax, [rax] 
	mov [rsp + 80], rax
	mov rbx, 1
	mov rax, [rsp+80]
	add rax, rbx ;EXPR ADD 
	mov [rsp+80], rax 
	mov rax, [rsp+80] 
	mov [rsp+88],rax 

	mov rax, 56
	add rax, rsp
	mov rbx, [88 + rsp] 
	mov [rax], rbx 
	JMP _L10 ; WHILE jump back 

_L11:   ;WHILE END target 
	mov rax, 0 
	mov [rsp+80],rax 

	mov rax, 56
	add rax, rsp
	mov rbx, [80 + rsp] 
	mov [rax], rbx 

_L12:   ;WHILE TOP target 

	mov rax, 56
	add rax, rsp
	mov rax, [rax] 
	mov [rsp + 88], rax
	mov rbx, 5
	mov rax, [rsp+88]
	cmp rax, rbx ;EXPR LESSTHAN 
	setl al ;EXPR LESSTHAN 
	mov rbx, 1 ;set rbx to one to filter rax
	and rax, rbx ;filter RAX
	mov [rsp+88], rax 
	mov rax, [rsp+88] ;WHILE expression expr 
	CMP rax, 0 ;WHILE compare
	JE _L13, ;WHILE branch out

	mov rax, 56
	add rax, rsp
	mov rbx, [rax] 
	shl rbx, 3 ;dereference array size 

	mov rax, 16
	add rax, rsp
	add rax, rbx ;add offset and stack pointer 
	mov rax, [rax] 
	mov [rsp + 96], rax

	mov rax, 56
	add rax, rsp
	mov rbx, [rax] 
	shl rbx, 3 ;dereference array size 

	mov rax, 16
	add rax, rsp
	add rax, rbx ;add offset and stack pointer 
	mov rbx, [rax] 
	mov rax, [rsp+96]
	imul rax, rbx ;EXPR TIMES 
	mov [rsp+96], rax 
	mov rsi, [rsp+96] 
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline

	mov rax, 56
	add rax, rsp
	mov rax, [rax] 
	mov [rsp + 104], rax
	mov rbx, 1
	mov rax, [rsp+104]
	add rax, rbx ;EXPR ADD 
	mov [rsp+104], rax 
	mov rax, [rsp+104] 
	mov [rsp+112],rax 

	mov rax, 56
	add rax, rsp
	mov rbx, [112 + rsp] 
	mov [rax], rbx 
	JMP _L12 ; WHILE jump back 

_L13:   ;WHILE END target 

	mov rbp, [rsp] ;FUNC end restore old BP
	mov rsp, [rsp+8] ;FUNC end restore old SP
	mov rsp, rbp	 ;stack and BP need to be same on exit for main
	ret
