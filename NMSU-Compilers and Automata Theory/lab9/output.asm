%include "io64.inc"

common	x	8
common	y	80

section .data

_L12:	db	"Testing Function Returns",0	;global string
_L17:	db	"Array fill test",0	;global string
_L37:	db	"nequals 0",0	;global string
_L38:	db	"equals 55",0	;global string
_L34:	db	"equals 55",0	;global string
_L35:	db	"nequals 55",0	;global string
_L7:	db	"x",0	;global string
_L8:	db	"y",0	;global string

section .text

	global main

sumArray:		;Start of Function
	mov	r8, rsp	;FUNC header RSP has to be at most RBP
	add	r8, -88	;adjust Stack Pointer for Activation record
	mov	[r8], rbp	;FUNC header store old BP
	mov	[r8+8], rsp	;FUNC header store old SP
	mov	rbp, rsp	;FUNC header TSP has to be at most rbp
	mov	rsp, r8	;FUNC header new SP
	mov	rax, 0 	;get identifier offset
	mov	[rsp+32], rax	;store rhs

	mov	rax, 24 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rbx, [rsp+32]	;fetch rhs of assign temporarily
	mov	[rax], rbx	;move rhs into rax
	mov	rax, 1 	;get identifier offset
	mov	[rsp+40], rax	;store rhs

	mov	rax, 16 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rbx, [rsp+40]	;fetch rhs of assign temporarily
	mov	[rax], rbx	;move rhs into rax

_L39:	;while top target

	mov	rax, 16 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rax, [rax]	;LHS expression is identifier
	mov	[rsp+48], rax	;store rax
	mov	rbx, 10 	;get identifier offset
	mov	rax, [rsp+48]	;store rsp + offset into rax
	cmp	rax, rbx	;EXPR LESSTHANEQUAL
	setle	al	;EXPR LESSTHANEQUAL
	mov	rbx, 1	;Set rbx to 1 to filter rax
	and	rax, rbx	;filter rax
	mov	[rsp+48], rax	;store rax
	mov	rax, [rsp+48]	;while expression expr
	CMP	rax, 0	;while compare
	JE	_L40,	;while branch

	mov	rax, 24 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rax, [rax]	;LHS expression is identifier
	mov	[rsp+56], rax	;store rax

	mov	rax, 16 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rbx, [rax]	;move rax value to rbx
	shl	rbx, 3	;Array reference needs WSIZE differencing

	mov	rax, y	;put address into rax
	add	rax, rbx	;add offset and stack pointer
	mov	rbx, [rax]	;RHS expression is identifier
	mov	rax, [rsp+56]	;store rsp + offset into rax
	add	rax, rbx	;EXPR ADD
	mov	[rsp+56], rax	;store rax
	mov	rax, [rsp+56]	;expressionstmt expr
	mov	[rsp+64], rax	;store rhs

	mov	rax, 24 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rbx, [rsp+64]	;fetch rhs of assign temporarily
	mov	[rax], rbx	;move rhs into rax

	mov	rax, 16 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rax, [rax]	;LHS expression is identifier
	mov	[rsp+72], rax	;store rax
	mov	rbx, 1 	;get identifier offset
	mov	rax, [rsp+72]	;store rsp + offset into rax
	add	rax, rbx	;EXPR ADD
	mov	[rsp+72], rax	;store rax
	mov	rax, [rsp+72]	;expressionstmt expr
	mov	[rsp+80], rax	;store rhs

	mov	rax, 16 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rbx, [rsp+80]	;fetch rhs of assign temporarily
	mov	[rax], rbx	;move rhs into rax
	JMP	_L39	;while jump back 

_L40:	;while end target

	mov	rax, 24 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rsi, [rax]	;load immediate value
	PRINT_DEC	8, rsi	;standard write value
	NEWLINE		;standard newline

	mov	rax, 24 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rax, [rax]	;return identifier value

	mov	rbp, [rsp]	;FUNC end restore old BP
	mov	rsp, [rsp+8]	;FUNC end restore old SP
	ret
	xor	rax, rax	;nothing to return

	mov	rbp, [rsp]	;FUNC end restore old BP
	mov	rsp, [rsp+8]	;FUNC end restore old SP
	ret
foo:		;Start of Function
	mov	r8, rsp	;FUNC header RSP has to be at most RBP
	add	r8, -40	;adjust Stack Pointer for Activation record
	mov	[r8], rbp	;FUNC header store old BP
	mov	[r8+8], rsp	;FUNC header store old SP
	mov	rbp, rsp	;FUNC header TSP has to be at most rbp
	mov	rsp, r8	;FUNC header new SP
	PRINT_STRING	_L7	;standard write value
	NEWLINE		;standard newline

	mov	rax, 16 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rsi, [rax]	;load immediate value
	PRINT_DEC	8, rsi	;standard write value
	NEWLINE		;standard newline
	PRINT_STRING	_L8	;standard write value
	NEWLINE		;standard newline

	mov	rax, 24 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rsi, [rax]	;load immediate value
	PRINT_DEC	8, rsi	;standard write value
	NEWLINE		;standard newline

	mov	rax, 16 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rax, [rax]	;LHS expression is identifier
	mov	[rsp+32], rax	;store rax

	mov	rax, 24 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rbx, [rax]	;RHS expression is identifier
	mov	rax, [rsp+32]	;store rsp + offset into rax
	imul	rax, rbx	;EXPR TIMES
	mov	[rsp+32], rax	;store rax
	mov	rax, [rsp+32]	;return value of expression

	mov	rbp, [rsp]	;FUNC end restore old BP
	mov	rsp, [rsp+8]	;FUNC end restore old SP
	ret
	xor	rax, rax	;nothing to return

	mov	rbp, [rsp]	;FUNC end restore old BP
	mov	rsp, [rsp+8]	;FUNC end restore old SP
	ret
main:		;Start of Function
	mov	rbp, rsp	;For main only
	mov	r8, rsp	;FUNC header RSP has to be at most RBP
	add	r8, -184	;adjust Stack Pointer for Activation record
	mov	[r8], rbp	;FUNC header store old BP
	mov	[r8+8], rsp	;FUNC header store old SP
	mov	rsp, r8	;FUNC header new SP
	mov	rax, 1 	;get identifier offset
	mov	[rsp+40], rax	;store rhs

	mov	rax, 32 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rbx, [rsp+40]	;fetch rhs of assign temporarily
	mov	[rax], rbx	;move rhs into rax

	mov	rax, 16 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	GET_DEC	8, [rax]	;readstmt
	mov	rax, 10 	;get identifier offset
	mov	[rsp+48], rax	;store rhs

	mov	rax, 24 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rbx, [rsp+48]	;fetch rhs of assign temporarily
	mov	[rax], rbx	;move rhs into rax
	PRINT_STRING	_L12	;standard write value
	NEWLINE		;standard newline

	mov	rax, 16 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rax, [rax]	;arg identifier value
	mov	[rsp+80], rax	;store arg into arglist offset

	mov	rax, 32 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rax, [rax]	;arg identifier value
	mov	[rsp+64], rax	;store arg into arglist offset

	mov	rax, 24 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rax, [rax]	;arg identifier value
	mov	[rsp+56], rax	;store arg into arglist offset
	mov	rbx, rsp	;store rsp in rbx
	sub	rbx, 48 	;subtract functionSize+1 to get location on stack
	mov	rax, [rsp+64]	;temporarily store arg contents
	mov	[rbx+16], rax	;copy contents of rax into param
	mov	rax, [rsp+56]	;temporarily store arg contents
	mov	[rbx+24], rax	;copy contents of rax into param
	call	foo	;call function
	mov	[rsp+72], rax	;store arg into arglist offset
	mov	rbx, rsp	;store rsp in rbx
	sub	rbx, 48 	;subtract functionSize+1 to get location on stack
	mov	rax, [rsp+80]	;temporarily store arg contents
	mov	[rbx+16], rax	;copy contents of rax into param
	mov	rax, [rsp+72]	;temporarily store arg contents
	mov	[rbx+24], rax	;copy contents of rax into param
	call	foo	;call function
	mov	rsi, rax	;store function return into rsi
	PRINT_DEC	8, rsi	;standard write value
	NEWLINE		;standard newline
	PRINT_STRING	_L17	;standard write value
	NEWLINE		;standard newline

_L41:	;while top target

	mov	rax, 32 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rax, [rax]	;LHS expression is identifier
	mov	[rsp+88], rax	;store rax
	mov	rbx, 10 	;get identifier offset
	mov	rax, [rsp+88]	;store rsp + offset into rax
	cmp	rax, rbx	;EXPR LESSTHANEQUAL
	setle	al	;EXPR LESSTHANEQUAL
	mov	rbx, 1	;Set rbx to 1 to filter rax
	and	rax, rbx	;filter rax
	mov	[rsp+88], rax	;store rax
	mov	rax, [rsp+88]	;while expression expr
	CMP	rax, 0	;while compare
	JE	_L42,	;while branch

	mov	rax, 32 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rax, [rax]	;expression ident
	mov	[rsp+112], rax	;store rhs

	mov	rax, 32 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rax, [rax]	;LHS expression is identifier
	mov	[rsp+96], rax	;store rax
	mov	rbx, 1 	;get identifier offset
	mov	rax, [rsp+96]	;store rsp + offset into rax
	add	rax, rbx	;EXPR ADD
	mov	[rsp+96], rax	;store rax
	mov	rax, [rsp+96]	;fetch LHS of expression from memory
	mov	[rsp+104], rax	;store rax
	mov	rbx, 1 	;get identifier offset
	mov	rax, [rsp+104]	;store rsp + offset into rax
	sub	rax, rbx	;EXPR SUB
	mov	[rsp+104], rax	;store rax
	mov	rbx, [rsp+104]	;move array value at sp to rbx
	shl	rbx, 3	;Array reference needs WSIZE differencing

	mov	rax, y	;put address into rax
	add	rax, rbx	;add offset and stack pointer
	mov	rbx, [rsp+112]	;fetch rhs of assign temporarily
	mov	[rax], rbx	;move rhs into rax

	mov	rax, 32 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rax, [rax]	;LHS expression is identifier
	mov	[rsp+120], rax	;store rax
	mov	rbx, 1 	;get identifier offset
	mov	rax, [rsp+120]	;store rsp + offset into rax
	add	rax, rbx	;EXPR ADD
	mov	[rsp+120], rax	;store rax
	mov	rax, [rsp+120]	;expressionstmt expr
	mov	[rsp+128], rax	;store rhs

	mov	rax, 32 	;get identifier offset
	add	rax, rsp	;Add the sp to have direct reference to memory
	mov	rbx, [rsp+128]	;fetch rhs of assign temporarily
	mov	[rax], rbx	;move rhs into rax
	JMP	_L41	;while jump back 

_L42:	;while end target
	mov	rax, 1 	;get identifier offset
	mov	[rsp+96], rax	;store rax
	mov	rbx, 2 	;get identifier offset
	mov	rax, [rsp+96]	;store rsp + offset into rax
	add	rax, rbx	;EXPR ADD
	mov	[rsp+96], rax	;store rax
	mov	rax, [rsp+96]	;fetch LHS of expression from memory
	mov	[rsp+104], rax	;store rax
	mov	rbx, 3 	;get identifier offset
	mov	rax, [rsp+104]	;store rsp + offset into rax
	add	rax, rbx	;EXPR ADD
	mov	[rsp+104], rax	;store rax
	mov	rax, [rsp+104]	;fetch LHS of expression from memory
	mov	[rsp+112], rax	;store rax
	mov	rbx, 4 	;get identifier offset
	mov	rax, [rsp+112]	;store rsp + offset into rax
	add	rax, rbx	;EXPR ADD
	mov	[rsp+112], rax	;store rax
	mov	rax, [rsp+112]	;fetch LHS of expression from memory
	mov	[rsp+120], rax	;store rax
	mov	rbx, 5 	;get identifier offset
	mov	rax, [rsp+120]	;store rsp + offset into rax
	add	rax, rbx	;EXPR ADD
	mov	[rsp+120], rax	;store rax
	mov	rax, [rsp+120]	;fetch LHS of expression from memory
	mov	[rsp+128], rax	;store rax
	mov	rbx, 6 	;get identifier offset
	mov	rax, [rsp+128]	;store rsp + offset into rax
	add	rax, rbx	;EXPR ADD
	mov	[rsp+128], rax	;store rax
	mov	rax, [rsp+128]	;fetch LHS of expression from memory
	mov	[rsp+136], rax	;store rax
	mov	rbx, 7 	;get identifier offset
	mov	rax, [rsp+136]	;store rsp + offset into rax
	add	rax, rbx	;EXPR ADD
	mov	[rsp+136], rax	;store rax
	mov	rax, [rsp+136]	;fetch LHS of expression from memory
	mov	[rsp+144], rax	;store rax
	mov	rbx, 8 	;get identifier offset
	mov	rax, [rsp+144]	;store rsp + offset into rax
	add	rax, rbx	;EXPR ADD
	mov	[rsp+144], rax	;store rax
	mov	rax, [rsp+144]	;fetch LHS of expression from memory
	mov	[rsp+152], rax	;store rax
	mov	rbx, 9 	;get identifier offset
	mov	rax, [rsp+152]	;store rsp + offset into rax
	add	rax, rbx	;EXPR ADD
	mov	[rsp+152], rax	;store rax
	mov	rax, [rsp+152]	;fetch LHS of expression from memory
	mov	[rsp+160], rax	;store rax
	mov	rbx, 10 	;get identifier offset
	mov	rax, [rsp+160]	;store rsp + offset into rax
	add	rax, rbx	;EXPR ADD
	mov	[rsp+160], rax	;store rax
	mov	rsi, [rsp+160]	;load expr value from expr mem
	PRINT_DEC	8, rsi	;standard write value
	NEWLINE		;standard newline
	mov	rbx, rsp	;store rsp in rbx
	sub	rbx, 96 	;subtract functionSize+1 to get location on stack
	call	sumArray	;call function
	mov	[rsp+168], rax	;store rax
	mov	rbx, 55 	;get identifier offset
	mov	rax, [rsp+168]	;store rsp + offset into rax
	cmp	rax, rbx	;EXPR EQUAL
	sete	al	;EXPR EQUAL
	mov	rbx, 1	;set rbx to one to filter rax
	and	rax, rbx	;filter rax
	mov	[rsp+168], rax	;store rax
	mov	rax, [rsp+168]	;if expression expr
	CMP	rax, 0	;if compare
	JE	_L43, 	;if branch to else
	PRINT_STRING	_L34	;standard write value
	NEWLINE		;standard newline
	JMP	_L44	;If s1 end

_L43:	;else target
	PRINT_STRING	_L35	;standard write value
	NEWLINE		;standard newline

_L44:	;IF bottom target
	mov	rbx, rsp	;store rsp in rbx
	sub	rbx, 96 	;subtract functionSize+1 to get location on stack
	call	sumArray	;call function
	mov	[rsp+176], rax	;store rax
	mov	rbx, 0 	;get identifier offset
	mov	rax, [rsp+176]	;store rsp + offset into rax
	cmp	rax, rbx	;EXPR NOTEQUAL
	setne	al	;EXPR NOTEQUAL
	mov	rbx, 1	;Set rbx to 1 to filter rax
	and	rax, rbx	;filter rax
	mov	[rsp+176], rax	;store rax
	mov	rax, [rsp+176]	;if expression expr
	CMP	rax, 0	;if compare
	JE	_L45, 	;if branch to else
	PRINT_STRING	_L37	;standard write value
	NEWLINE		;standard newline
	JMP	_L46	;If s1 end

_L45:	;else target
	PRINT_STRING	_L38	;standard write value
	NEWLINE		;standard newline

_L46:	;IF bottom target
	xor	rax, rax	;nothing to return

	mov	rbp, [rsp]	;FUNC end restore old BP
	mov	rsp, [rsp+8]	;FUNC end restore old SP
	mov	rsp, rbp	;stack and BP need to be same on exit for main
	ret
