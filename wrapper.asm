.data
EXTERN procs:QWORD

.code

wrapper MACRO name, index
name PROC
    mov rax, QWORD PTR procs[index * 8]
    jmp rax
name ENDP
ENDM

wrapper GetFileVersionInfoA_wrapper, 0
wrapper GetFileVersionInfoByHandle_wrapper, 1
wrapper GetFileVersionInfoExA_wrapper, 2
wrapper GetFileVersionInfoExW_wrapper, 3
wrapper GetFileVersionInfoSizeA_wrapper, 4
wrapper GetFileVersionInfoSizeExA_wrapper, 5
wrapper GetFileVersionInfoSizeExW_wrapper, 6
wrapper GetFileVersionInfoSizeW_wrapper, 7
wrapper GetFileVersionInfoW_wrapper, 8
wrapper VerFindFileA_wrapper, 9
wrapper VerFindFileW_wrapper, 10
wrapper VerInstallFileA_wrapper, 11
wrapper VerInstallFileW_wrapper, 12
wrapper VerLanguageNameA_wrapper, 13
wrapper VerLanguageNameW_wrapper, 14
wrapper VerQueryValueA_wrapper, 15
wrapper VerQueryValueW_wrapper, 16

END
