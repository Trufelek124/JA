;-------------------------------------------------------------------------
.DATA

.CODE
brightenImage proc

mov R10, rcx				;pierwsza tablica
mov R12, rdx				;druga tablica

mov ebx ,0					;zmienna i
mov R11, R8					;rozmiar

push rdi

start:						;poczatek petli
;wczytaj do xmm
mov rcx, [R12]
mov rdx, [R10]
movd xmm1, ecx
movd xmm2, edx

;porownaj:
pcmpeqd xmm1, xmm2
movd eax, xmm1
cmp eax, 0
je false

;przesun o 32 bity
add R10, 32
add R12, 32
add ebx, 32

mov eax, R11d
cmp ebx, eax	;sprawdz czy i nie jest wieksze od mainSize
jb start		;jak nie powtorz petle

; jesli i (ebx) bylo powyzej mainSize (R10d) znajdz wartosc roznicy
sub ebx, eax ;odejmij roznice aby sprawdzic ostatnie 32 bity
sub ecx, ebx
sub edx, ebx
;wczytywanie do xmm:
mov ecx, [R12]
mov edx, [R10]
movd xmm1, ecx
movd xmm2, edx

pcmpeqd xmm1, xmm2
movd eax, xmm1
cmp eax, 0
je false

true:
mov eax, 1
jmp return

false:
mov eax, 0

return:
mov dword ptr [r9], eax
pop rdi
ret

compareAsm ENDP

;-------------------------------------------------------------------------
END