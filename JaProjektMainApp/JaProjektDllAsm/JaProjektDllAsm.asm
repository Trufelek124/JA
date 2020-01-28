;-------------------------------------------------------------------------
.DATA

.CODE
brightenImage proc

mov R10, rcx				;inArray - argumenty (w kolejnoœci) rcx, rdx, r8, r9
mov R12, rdx				;outArray
mov rsi, R9					;multiplier

mov ebx ,0					;iterator for loop
mov R11, R8					;size

push rdi					;w xmm3 mam wartoœæ [1.70005, 0000000, 0000000, 0000000] - nie wiem czemu i sk¹d

shufps xmm3,xmm3,0h			;propagowanie wartosci 1.70005 na wszystkie


start:						;loop beginning

;mov rcx, [R12]
mov rdx, [R10]
mov rsi, R9

;mov eax, edx



;CVTSI2SS xmm0, eax
movd xmm1, rdx
PAND xmm1, xmm1
PUNPCKLWD xmm1, xmm0 ;xmm0 - zero vector
CVTDQ2PS xmm2, xmm1

;mulps xmm2, xmm3 

movd eax, xmm2
movd xmm0, eax
CVTPS2PD xmm0, xmm0
CVTSD2SI rax, xmm0


movd rax, xmm1
mov [R12], rax


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