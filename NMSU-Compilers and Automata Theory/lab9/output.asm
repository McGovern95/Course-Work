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
	mov rbp, rsp; for main only
	mov r8, rsp ;inital mov to r8
	add r8, -968 ;add - total value to r8
	mov [r8], rbp ; initial move of base to value r8
	mov [r8+8],rsp ;initial move of stack p to value r8 with added 8
	mov rsp, r8 ;FUNC header new sp
	PRINT_STRING _L0  ;standard write value with string 
	NEWLINE ;standard newline

	mov rax, y ;name moved to rax
	GET_DEC 8, [rax] ;read into value of rax

	mov rax, y ;name moved to rax
	mov rsi,[rax] ; load immediate value  to rsi IDENT
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline
	PRINT_STRING _L1  ;standard write value with string 
	NEWLINE ;standard newline
	mov rax, 0 ; move NUMBER to rax 
	mov [rsp+840],rax ;move rax to memory address of added offset to rsp 

	mov rax, 16 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rbx, [rsp+840] ;offset of assignment added to rsp then moved to rax
	mov [rax], rbx ;move rbx to value of 
	mov rax, 0 ; move NUMBER to rax 
	mov [rsp+848],rax ;move rax to memory address of added offset to rsp 

	mov rax, 24 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rbx, [rsp+848] ;offset of assignment added to rsp then moved to rax
	mov [rax], rbx ;move rbx to value of 
	mov rax, 2 ; move NUMBER to rax 
	mov [rsp+856],rax ;move rax to memory address of added offset to rsp 

	mov rax, 32 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rbx, [rsp+856] ;offset of assignment added to rsp then moved to rax
	mov [rax], rbx ;move rbx to value of 
	PRINT_STRING _L5  ;standard write value with string 
	NEWLINE ;standard newline

	mov rax, 16 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rsi,[rax] ; load immediate value  to rsi IDENT
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline

_L31:   ;WHILE TOP target 

	mov rax, 16 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rax, [rax] ;move value rax to rax, ident left 
	mov [rsp+864], rax ;move rax to rsp value with added offset, after left
	mov rbx, 5 ;move NUMBER to rbx, right
	mov rax, [rsp+864] ;offset add to rsp value and move to rax
	cmp rax, rbx ;EXPR LESSTHAN 
	setl al ;EXPR LESSTHAN 
	mov rbx, 1 ;set rbx to one to filter rax
	and rax, rbx ;filter RAX
	mov [rsp+864], rax ;rax to value of rsp + offset end
	mov rax, [rsp+864] ;WHILE expression expr 
	CMP rax, 0 ;WHILE compare
	JE _L32, ;WHILE branch out
	PRINT_STRING _L7  ;standard write value with string 
	NEWLINE ;standard newline

	mov rax, 16 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rax, [rax] ;move value rax to rax, ident left 
	mov [rsp+872], rax ;move rax to rsp value with added offset, after left
	mov rbx, 1 ;move NUMBER to rbx, right
	mov rax, [rsp+872] ;offset add to rsp value and move to rax
	add rax, rbx ;EXPR ADD 
	mov [rsp+872], rax ;rax to value of rsp + offset end
	mov rax, [rsp+872] ; expression offset adding to stack and then move to rax
	mov [rsp+880],rax ;move rax to memory address of added offset to rsp 

	mov rax, 16 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rbx, [rsp+880] ;offset of assignment added to rsp then moved to rax
	mov [rax], rbx ;move rbx to value of 
	JMP _L31 ; WHILE jump back 

_L32:   ;WHILE END target 
	PRINT_STRING _L10  ;standard write value with string 
	NEWLINE ;standard newline

	mov rax, 24 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rsi,[rax] ; load immediate value  to rsi IDENT
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline

_L33:   ;IF TOP target 

	mov rax, 24 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rax, [rax] ;move value rax to rax, ident left 
	mov [rsp+872], rax ;move rax to rsp value with added offset, after left
	mov rbx, 1 ;move NUMBER to rbx, right
	mov rax, [rsp+872] ;offset add to rsp value and move to rax
	cmp rax, rbx ;EXPR LESSTHAN 
	setl al ;EXPR LESSTHAN 
	mov rbx, 1 ;set rbx to one to filter rax
	and rax, rbx ;filter RAX
	mov [rsp+872], rax ;rax to value of rsp + offset end
	mov rax, [rsp+872] ;IF expression expr 
	CMP rax, 0 ;IF compare
	JE _L34, ;IF branch to ELSE
	PRINT_STRING _L12  ;standard write value with string 
	NEWLINE ;standard newline

	mov rax, 24 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rax, [rax] ;move value rax to rax, ident left 
	mov [rsp+880], rax ;move rax to rsp value with added offset, after left
	mov rbx, 1 ;move NUMBER to rbx, right
	mov rax, [rsp+880] ;offset add to rsp value and move to rax
	add rax, rbx ;EXPR ADD 
	mov [rsp+880], rax ;rax to value of rsp + offset end
	mov rax, [rsp+880] ; expression offset adding to stack and then move to rax
	mov [rsp+888],rax ;move rax to memory address of added offset to rsp 

	mov rax, 24 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rbx, [rsp+888] ;offset of assignment added to rsp then moved to rax
	mov [rax], rbx ;move rbx to value of 
	JMP _L33 ;IF S1 end

_L34:   ;ELSE target 
	PRINT_STRING _L15  ;standard write value with string 
	NEWLINE ;standard newline

	mov rax, 32 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rsi,[rax] ; load immediate value  to rsi IDENT
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline

_L35:   ;IF TOP target 

	mov rax, 32 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rax, [rax] ;move value rax to rax, ident left 
	mov [rsp+880], rax ;move rax to rsp value with added offset, after left
	mov rbx, 1 ;move NUMBER to rbx, right
	mov rax, [rsp+880] ;offset add to rsp value and move to rax
	cmp rax, rbx ;EXPR LESSTHAN 
	setl al ;EXPR LESSTHAN 
	mov rbx, 1 ;set rbx to one to filter rax
	and rax, rbx ;filter RAX
	mov [rsp+880], rax ;rax to value of rsp + offset end
	mov rax, [rsp+880] ;IF expression expr 
	CMP rax, 0 ;IF compare
	JE _L36, ;IF branch to ELSE
	PRINT_STRING _L17  ;standard write value with string 
	NEWLINE ;standard newline
	JMP _L35 ;IF S1 end

_L36:   ;ELSE target 
	PRINT_STRING _L18  ;standard write value with string 
	NEWLINE ;standard newline
	PRINT_STRING _L19  ;standard write value with string 
	NEWLINE ;standard newline
	mov rax, 5 ;move NUMBER to rax, left 
	mov [rsp+888], rax ;move rax to rsp value with added offset, after left
	mov rbx, 5 ;move NUMBER to rbx, right
	mov rax, [rsp+888] ;offset add to rsp value and move to rax
	add rax, rbx ;EXPR ADD 
	mov [rsp+888], rax ;rax to value of rsp + offset end
	mov rax, [rsp+888] ;add offset to rsp and move to rax, expr left
	mov [rsp+896], rax ;move rax to rsp value with added offset, after left
	mov rbx, 5 ;move NUMBER to rbx, right
	mov rax, [rsp+896] ;offset add to rsp value and move to rax
	sub rax, rbx ;EXPR SUB 
	mov [rsp+896], rax ;rax to value of rsp + offset end
	mov rsi, [rsp+896] ;offset added to stack p mov to rsi, expr writestmt
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline
	mov rax, 10 ;move NUMBER to rax, left 
	mov [rsp+904], rax ;move rax to rsp value with added offset, after left
	mov rbx, 5 ;move NUMBER to rbx, right
	mov rax, [rsp+904] ;offset add to rsp value and move to rax
	xor rdx, rdx 
	idiv rbx ;EXPR DIV 
	mov [rsp+904], rax ;rax to value of rsp + offset end
	mov rax, [rsp+904] ;add offset to rsp and move to rax, expr left
	mov [rsp+912], rax ;move rax to rsp value with added offset, after left
	mov rbx, 2 ;move NUMBER to rbx, right
	mov rax, [rsp+912] ;offset add to rsp value and move to rax
	imul rax, rbx ;EXPR TIMES 
	mov [rsp+912], rax ;rax to value of rsp + offset end
	mov rsi, [rsp+912] ;offset added to stack p mov to rsi, expr writestmt
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline
	mov rax, 5 ;move NUMBER to rax, left 
	mov [rsp+920], rax ;move rax to rsp value with added offset, after left
	mov rbx, 5 ;move NUMBER to rbx, right
	mov rax, [rsp+920] ;offset add to rsp value and move to rax
	add rax, rbx ;EXPR ADD 
	mov [rsp+920], rax ;rax to value of rsp + offset end
	mov rax, [rsp+920] ;add offset to rsp and move to rax, expr left
	mov [rsp+944], rax ;move rax to rsp value with added offset, after left
	mov rax, 5 ;move NUMBER to rax, left 
	mov [rsp+928], rax ;move rax to rsp value with added offset, after left
	mov rbx, 1 ;move NUMBER to rbx, right
	mov rax, [rsp+928] ;offset add to rsp value and move to rax
	imul rax, rbx ;EXPR TIMES 
	mov [rsp+928], rax ;rax to value of rsp + offset end
	mov rax, [rsp+928] ;add offset to rsp and move to rax, expr left
	mov [rsp+936], rax ;move rax to rsp value with added offset, after left
	mov rbx, 1 ;move NUMBER to rbx, right
	mov rax, [rsp+936] ;offset add to rsp value and move to rax
	xor rdx, rdx 
	idiv rbx ;EXPR DIV 
	mov [rsp+936], rax ;rax to value of rsp + offset end
	mov rbx, [rsp+936] ;add offset to rsp and move to rax, expr right
	mov rax, [rsp+944] ;offset add to rsp value and move to rax
	sub rax, rbx ;EXPR SUB 
	mov [rsp+944], rax ;rax to value of rsp + offset end
	mov rsi, [rsp+944] ;offset added to stack p mov to rsi, expr writestmt
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline
	PRINT_STRING _L28  ;standard write value with string 
	NEWLINE ;standard newline
	mov rax, 5 ; move NUMBER to rax 
	mov [rsp+952],rax ;move rax to memory address of added offset to rsp 
	mov rbx, 208 ;assign value to rbx

	mov rax, b ;name moved to rax
	add rax, rbx ;add offset and stack pointer 
	mov rbx, [rsp+952] ;offset of assignment added to rsp then moved to rax
	mov [rax], rbx ;move rbx to value of 
	mov rax, 25 ;move NUMBER to rax, left 
	mov [rsp+960], rax ;move rax to rsp value with added offset, after left
	mov rbx, 1 ;move NUMBER to rbx, right
	mov rax, [rsp+960] ;offset add to rsp value and move to rax
	add rax, rbx ;EXPR ADD 
	mov [rsp+960], rax ;rax to value of rsp + offset end
	mov rbx, [rsp + 960] 
	shl rbx, 3 ;dereference array size 

	mov rax, b ;name moved to rax
	add rax, rbx ;add offset and stack pointer 
	mov rsi,[rax] ; load immediate value  to rsi IDENT
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline

	mov rbp, [rsp] ;FUNC end restore old BP
	mov rsp, [rsp+8] ;FUNC end restore old SP
	mov rsp, rbp	 ;stack and BP need to be same on exit for main
	ret ;return
