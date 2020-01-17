;-------------------------------------------------------------------------

.586
.MODEL  Flat,C
OPTION CASEMAP:NONE
INCLUDE C:\masm32\include\windows.inc

.CODE
DllEntry PROC hInstDLL:HINSTANCE, reason:DWORD, reserved1:DWORD

    mov eax, TRUE  
    ret

DllEntry ENDP
;-------------------------------------------------------------------------
brightenImage proc len: DWORD, inArray: DWORD, outArray: DWORD, mult: QWORD


	mov ECX, [len]				; load size of array to ECX
	mov EBX, [inArray]			; base address of in array to EBX
	mov EDX, [outArray]			; base address of result to EDX
	mov EAX, ECX				; number of size of array to EAX
	add EBX, EAX				; add EAX to EBX, EBX now points to last inArray
	dec EAX						; decrease EAX
	jmp skip					; skip first mutliplication, coprocessor is 0 anyway
forLoop:						; for i=size - 1, i >= 0, i--
	fmul [ mult ]				; accumulator = (accumulator * multiplier)
skip:
	sub EBX, 8					; move to the previous inArray
	loop forLoop				; for loop
	fstp REAL8 PTR [ EDX ]		; accumulator into result pointer
ret
brightenImage endp
END DllEntry
;-------------------------------------------------------------------------