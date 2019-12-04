.586
.model flat, stdcall
includelib kernel32.lib
includelib ASM_LIB.lib
includelib libucrt.lib
includelib msvcrt.lib 

ExitProcess PROTO :DWORD
outc PROTO :DWORD
outi PROTO :DWORD
outid PROTO :DWORD
outcd PROTO :DWORD
Pow PROTO :DWORD, :DWORD
Sqrt PROTO :DWORD

.stack 4096
.const
LEX1	DWORD	10
LEX2	DWORD	25
LEX3	Byte	'ясллю пюбмю :',0
.data
mainlol  DWORD	?
mainjoj  DWORD	?
mainsum  DWORD	?
mainstr  DWORD	?


.code
main PROC
	push LEX1
	pop mainlol
	pop edx
	push LEX2
	pop mainjoj
	pop edx
	push offset LEX3
	pop mainstr
	pop edx

push mainstr
		call outc

push mainsum
		call outi

push 0

call ExitProcess
main ENDP
end main