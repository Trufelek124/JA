;------------------------------------------------------------------------- .386 .MODEL FLAT, STDCALL

.586
.MODEL  Flat,StdCall
OPTION CASEMAP:NONE
INCLUDE C:\masm32\include\windows.inc

.CODE
DllEntry PROC hInstDLL:HINSTANCE, reason:DWORD, reserved1:DWORD
DllEntry ENDP
;-------------------------------------------------------------------------
MyProc1 proc x: DWORD, y: DWORD
xor eax,eax
mov eax,x
mov ecx,y
ror ecx,1
shld eax,ecx,2
jnc ET1 
mul y 
ret 
ET1: 
Neg x 
Mul x 
ret
MyProc1 endp
END DllEntry ;-------------------------------------------------------------------------