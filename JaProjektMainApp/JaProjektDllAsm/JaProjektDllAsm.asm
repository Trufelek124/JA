;-------------------------------------------------------------------------
.DATA

.CODE
brightenImage proc

mov R10, rcx				;pierwsza tablica
mov R12, rdx				;druga tablica

mov ebx ,0					;zmienna i
mov R11, R8					;rozmiar

ret

brightenImage ENDP

;-------------------------------------------------------------------------
END