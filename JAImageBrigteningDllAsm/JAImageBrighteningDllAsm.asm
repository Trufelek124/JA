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
	mov EAX, ECX
	shl EAX, 3					; shift left by 3, same as multiply by 8, 
	add EBX, EAX				;jesteœmy na koñcu tablicy
	add EDX, EAX
forLoop:						; for i=size - 1, i >= 0, i--
	sub EBX, 8					; move to the previous inArray
	sub EDX, 8					; move to the previous inArray
	mov EAX, EBX
	fmul [mult]
	mov EDX, EAX
	loop forLoop				; for loop
	mov EAX, EDX
ret
brightenImage endp
END DllEntry
;-------------------------------------------------------------------------