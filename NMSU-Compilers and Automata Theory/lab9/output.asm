%include "io64.inc" 
	common y 8
	common b 800
section .data 
_L0: db "enter a number", 0	; global string
_L1: db "read and write success!", 0	; global string
_L5: db "value of x for while", 0	; global string
_L17: db "math operator tests", 0	; global string
_L26: db "array test", 0	; global string
_L15: db "SHOULD NOT GO HERE", 0	; global string
_L16: db "else success!", 0	; global string
_L11: db "if success!", 0	; global string
_L7: db "while success!", 0	; global string

section .text 
	global main
main:
	mov rbp, rsp; for main only
	mov r8, rsp ;inital mov to r8
	add r8, -168 ;add - total value to r8
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
	mov [rsp+40],rax ;move rax to memory address of added offset to rsp 

	mov rax, 16 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rbx, [rsp+40] ;offset of assignment added to rsp then moved to rax
	mov [rax], rbx ;move rbx to value of 
	mov rax, 0 ; move NUMBER to rax 
	mov [rsp+48],rax ;move rax to memory address of added offset to rsp 

	mov rax, 24 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rbx, [rsp+48] ;offset of assignment added to rsp then moved to rax
	mov [rax], rbx ;move rbx to value of 
	mov rax, 2 ; move NUMBER to rax 
	mov [rsp+56],rax ;move rax to memory address of added offset to rsp 

	mov rax, 32 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rbx, [rsp+56] ;offset of assignment added to rsp then moved to rax
	mov [rax], rbx ;move rbx to value of 
	PRINT_STRING _L5  ;standard write value with string 
	NEWLINE ;standard newline

	mov rax, 16 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rsi,[rax] ; load immediate value  to rsi IDENT
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline

_L29:   ;WHILE TOP target 

	mov rax, 16 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rax, [rax] ;move value rax to rax, ident left 
	mov [rsp+64], rax ;move rax to rsp value with added offset, after left
	mov rbx, 5 ;move NUMBER to rbx, right
	mov rax, [rsp+64] ;offset add to rsp value and move to rax
	cmp rax, rbx ;EXPR LESSTHAN 
	setl al ;EXPR LESSTHAN 
	mov rbx, 1 ;set rbx to one to filter rax
	and rax, rbx ;filter RAX
	mov [rsp+64], rax ;rax to value of rsp + offset end
	mov rax, [rsp+64] ;WHILE expression expr 
	CMP rax, 0 ;WHILE compare
	JE _L30, ;WHILE branch out
	PRINT_STRING _L7  ;standard write value with string 
	NEWLINE ;standard newline

	mov rax, 16 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rsi,[rax] ; load immediate value  to rsi IDENT
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline

	mov rax, 16 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rax, [rax] ;move value rax to rax, ident left 
	mov [rsp+72], rax ;move rax to rsp value with added offset, after left
	mov rbx, 1 ;move NUMBER to rbx, right
	mov rax, [rsp+72] ;offset add to rsp value and move to rax
	add rax, rbx ;EXPR ADD 
	mov [rsp+72], rax ;rax to value of rsp + offset end
	mov rax, [rsp+72] ; expression offset adding to stack and then move to rax
	mov [rsp+80],rax ;move rax to memory address of added offset to rsp 

	mov rax, 16 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rbx, [rsp+80] ;offset of assignment added to rsp then moved to rax
	mov [rax], rbx ;move rbx to value of 
	JMP _L29 ; WHILE jump back 

_L30:   ;WHILE END target 

_L31:   ;IF TOP target 

	mov rax, 24 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rax, [rax] ;move value rax to rax, ident left 
	mov [rsp+72], rax ;move rax to rsp value with added offset, after left
	mov rbx, 1 ;move NUMBER to rbx, right
	mov rax, [rsp+72] ;offset add to rsp value and move to rax
	cmp rax, rbx ;EXPR LESSTHAN 
	setl al ;EXPR LESSTHAN 
	mov rbx, 1 ;set rbx to one to filter rax
	and rax, rbx ;filter RAX
	mov [rsp+72], rax ;rax to value of rsp + offset end
	mov rax, [rsp+72] ;IF expression expr 
	CMP rax, 0 ;IF compare
	JE _L32, ;IF branch to ELSE
	PRINT_STRING _L11  ;standard write value with string 
	NEWLINE ;standard newline

	mov rax, 24 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rax, [rax] ;move value rax to rax, ident left 
	mov [rsp+80], rax ;move rax to rsp value with added offset, after left
	mov rbx, 1 ;move NUMBER to rbx, right
	mov rax, [rsp+80] ;offset add to rsp value and move to rax
	add rax, rbx ;EXPR ADD 
	mov [rsp+80], rax ;rax to value of rsp + offset end
	mov rax, [rsp+80] ; expression offset adding to stack and then move to rax
	mov [rsp+88],rax ;move rax to memory address of added offset to rsp 

	mov rax, 24 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rbx, [rsp+88] ;offset of assignment added to rsp then moved to rax
	mov [rax], rbx ;move rbx to value of 
	JMP _L31 ;IF S1 end

_L32:   ;ELSE target 

_L33:   ;IF TOP target 

	mov rax, 32 ;offset moved to rax
	add rax, rsp ;stack added to rax
	mov rax, [rax] ;move value rax to rax, ident left 
	mov [rsp+80], rax ;move rax to rsp value with added offset, after left
	mov rbx, 1 ;move NUMBER to rbx, right
	mov rax, [rsp+80] ;offset add to rsp value and move to rax
	cmp rax, rbx ;EXPR LESSTHAN 
	setl al ;EXPR LESSTHAN 
	mov rbx, 1 ;set rbx to one to filter rax
	and rax, rbx ;filter RAX
	mov [rsp+80], rax ;rax to value of rsp + offset end
	mov rax, [rsp+80] ;IF expression expr 
	CMP rax, 0 ;IF compare
	JE _L34, ;IF branch to ELSE
	PRINT_STRING _L15  ;standard write value with string 
	NEWLINE ;standard newline
	JMP _L33 ;IF S1 end

_L34:   ;ELSE target 
	PRINT_STRING _L16  ;standard write value with string 
	NEWLINE ;standard newline
	PRINT_STRING _L17  ;standard write value with string 
	NEWLINE ;standard newline
	mov rax, 5 ;move NUMBER to rax, left 
	mov [rsp+88], rax ;move rax to rsp value with added offset, after left
	mov rbx, 5 ;move NUMBER to rbx, right
	mov rax, [rsp+88] ;offset add to rsp value and move to rax
	add rax, rbx ;EXPR ADD 
	mov [rsp+88], rax ;rax to value of rsp + offset end
	mov rax, [rsp+88] ;add offset to rsp and move to rax, expr left
	mov [rsp+96], rax ;move rax to rsp value with added offset, after left
	mov rbx, 5 ;move NUMBER to rbx, right
	mov rax, [rsp+96] ;offset add to rsp value and move to rax
	sub rax, rbx ;EXPR SUB 
	mov [rsp+96], rax ;rax to value of rsp + offset end
	mov rsi, [rsp+96] ;offset added to stack p mov to rsi, expr writestmt
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline
	mov rax, 10 ;move NUMBER to rax, left 
	mov [rsp+104], rax ;move rax to rsp value with added offset, after left
	mov rbx, 5 ;move NUMBER to rbx, right
	mov rax, [rsp+104] ;offset add to rsp value and move to rax
	xor rdx, rdx 
	idiv rbx ;EXPR DIV 
	mov [rsp+104], rax ;rax to value of rsp + offset end
	mov rax, [rsp+104] ;add offset to rsp and move to rax, expr left
	mov [rsp+112], rax ;move rax to rsp value with added offset, after left
	mov rbx, 2 ;move NUMBER to rbx, right
	mov rax, [rsp+112] ;offset add to rsp value and move to rax
	imul rax, rbx ;EXPR TIMES 
	mov [rsp+112], rax ;rax to value of rsp + offset end
	mov rsi, [rsp+112] ;offset added to stack p mov to rsi, expr writestmt
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline
	mov rax, 5 ;move NUMBER to rax, left 
	mov [rsp+120], rax ;move rax to rsp value with added offset, after left
	mov rbx, 5 ;move NUMBER to rbx, right
	mov rax, [rsp+120] ;offset add to rsp value and move to rax
	add rax, rbx ;EXPR ADD 
	mov [rsp+120], rax ;rax to value of rsp + offset end
	mov rax, [rsp+120] ;add offset to rsp and move to rax, expr left
	mov [rsp+144], rax ;move rax to rsp value with added offset, after left
	mov rax, 5 ;move NUMBER to rax, left 
	mov [rsp+128], rax ;move rax to rsp value with added offset, after left
	mov rbx, 1 ;move NUMBER to rbx, right
	mov rax, [rsp+128] ;offset add to rsp value and move to rax
	imul rax, rbx ;EXPR TIMES 
	mov [rsp+128], rax ;rax to value of rsp + offset end
	mov rax, [rsp+128] ;add offset to rsp and move to rax, expr left
	mov [rsp+136], rax ;move rax to rsp value with added offset, after left
	mov rbx, 1 ;move NUMBER to rbx, right
	mov rax, [rsp+136] ;offset add to rsp value and move to rax
	xor rdx, rdx 
	idiv rbx ;EXPR DIV 
	mov [rsp+136], rax ;rax to value of rsp + offset end
	mov rbx, [rsp+136] ;add offset to rsp and move to rax, expr right
	mov rax, [rsp+144] ;offset add to rsp value and move to rax
	sub rax, rbx ;EXPR SUB 
	mov [rsp+144], rax ;rax to value of rsp + offset end
	mov rsi, [rsp+144] ;offset added to stack p mov to rsi, expr writestmt
	PRINT_DEC 8, rsi   ;standard write value 
	NEWLINE	;standard newline
	PRINT_STRING _L26  ;standard write value with string 
	NEWLINE ;standard newline
	mov rax, 5 ; move NUMBER to rax 
	mov [rsp+152],rax ;move rax to memory address of added offset to rsp 
	mov rbx, 208 ;assign value to rbx

	mov rax, b ;name moved to rax
	add rax, rbx ;add offset and stack pointer 
	mov rbx, [rsp+152] ;offset of assignment added to rsp then moved to rax
	mov [rax], rbx ;move rbx to value of 
	mov rax, 25 ;move NUMBER to rax, left 
	mov [rsp+160], rax ;move rax to rsp value with added offset, after left
	mov rbx, 1 ;move NUMBER to rbx, right
	mov rax, [rsp+160] ;offset add to rsp value and move to rax
	add rax, rbx ;EXPR ADD 
	mov [rsp+160], rax ;rax to value of rsp + offset end
	mov rbx, [rsp + 160] 
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
