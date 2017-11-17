
.section .bss, "aw", @nobits
gdtr:
	.skip 6

.section .text
.global _setGdtASM
.type _setGdtASM, @function
	
_setGdtASM:
	push %ebp
	mov %esp, %ebp
	mov 8(%ebp), %eax
	mov %eax, gdtr
	mov 12(%ebp), %eax
	mov %eax, gdtr+2
	lgdt gdtr
	leave
	ret
	
.global _reloadSegments
.type _reloadSegments, @function
_reloadSegments:
	jmp reload_CS
	
reload_CS:
	mov 0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	ret