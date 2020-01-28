;-------------------------------------------------------------------------
.DATA

.CODE
brightenImage proc

mov R10, rcx						; inArray - argumenty (w kolejnoœci) rcx, rdx, r8, r9
mov R12, rdx						; outArray
mov rsi, R9							; multiplier
	
mov ebx ,0							; iterator for loop
mov R11, R8							; size

;push rdi							

shufps xmm3,xmm3,0h					; making sure all 4 of 32bit segments are filled with this value


start: ;loop beginning

PMOVZXBD xmm0, DWORD PTR [R10]		; DWORD PTR means "the size of the target operand is 32 bits" - so it takes 4 values. instruction converts 8bit integers to 32bit integers
CVTDQ2PS xmm1, xmm0					; integers to floats

mulps xmm1, xmm3					; multiplying of registers
CVTPS2DQ xmm0, xmm1					; floats to integers (but values might be higher than 255)

packssdw xmm0, xmm0					; Converts 2 packed signed doubleword integers from mm1 and from mm2/m64 into 4 packed signed word integers in mm1 using signed saturation
packuswb xmm0, xmm0					; Converts 8 signed word integers from xmm1 and 8 signed word integers from xmm2/m128 into 16 unsigned byte integers in xmm1 using unsigned saturation.

movd DWORD PTR [R12],xmm0			; mov result to outArray

add R10, 4							; move loop by 4 bytes (cause we took 4 elements from array)
add R12, 4
add ebx, 4

mov eax, R11d						
cmp ebx, eax						; check if iterator is bigger than mainsize
jb start							; if not - loop

;pop rdi

ret

brightenImage ENDP

;-------------------------------------------------------------------------
END
