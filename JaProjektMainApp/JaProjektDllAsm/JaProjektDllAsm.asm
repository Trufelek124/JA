;-------------------------------------------------------------------------
.DATA

.CODE
brightenImage proc

mov R10, rcx				;inArray
mov R12, rdx				;out array
mov R9, rsi					;multiplier

mov ebx ,0					;iterator for loop
mov R11, R8					;size

push rdi

start:						;loop beginning

mov rcx, [R12]
mov rdx, [R10]

mov [R12], edx



add R10, 1	;move loop by one
add R12, 1
add ebx, 1


mov eax, R11d
cmp ebx, eax	;check if iterator is bigger than mainsize
jb start		;if not - loop

pop rdi

ret

brightenImage ENDP

;-------------------------------------------------------------------------
END