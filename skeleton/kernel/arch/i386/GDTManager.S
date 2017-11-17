	.file	"GDTManager.cpp"
	.text
.Ltext0:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"bad gdt entry...\n"
	.text
	.align 2
	.align 16
	.globl	_ZN10GDTManager9encodeGDTEv
	.type	_ZN10GDTManager9encodeGDTEv, @function
_ZN10GDTManager9encodeGDTEv:
.LFB3:
	.file 1 "kernel/arch/i386/GDTManager.cpp"
	.loc 1 37 0
	.cfi_startproc
.LVL0:
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$12, %esp
	.cfi_def_cfa_offset 32
	.loc 1 37 0
	movl	32(%esp), %ebp
.LBB2:
	.loc 1 40 0
	movl	8(%ebp), %eax
.LBE2:
	.loc 1 38 0
	movl	0(%ebp), %ebx
.LVL1:
.LBB5:
	.loc 1 40 0
	testl	%eax, %eax
	je	.L1
	xorl	%edi, %edi
	jmp	.L6
.LVL2:
	.align 16
.L16:
.LBB3:
	.loc 1 43 0 discriminator 1
	movl	%eax, %edx
	andl	$4095, %edx
	cmpl	$4095, %edx
	je	.L4
	.loc 1 44 0
	subl	$12, %esp
	.cfi_def_cfa_offset 44
	pushl	$.LC0
	.cfi_def_cfa_offset 48
	call	terminal_writestring
.LVL3:
	.loc 1 47 0
	movl	4(%ebx), %eax
	addl	$16, %esp
	.cfi_def_cfa_offset 32
	cmpl	$65536, %eax
	jbe	.L3
.L4:
	.loc 1 48 0
	shrl	$12, %eax
	movl	$-64, %edx
	movl	%eax, 4(%ebx)
	.loc 1 49 0
	movb	$-64, 6(%esi)
.L5:
	.loc 1 55 0
	movl	4(%ebx), %eax
	movb	%al, (%esi)
	.loc 1 56 0
	movl	4(%ebx), %eax
	movb	%ah, 1(%esi)
	.loc 1 57 0
	movzwl	6(%ebx), %eax
	andl	$15, %eax
	orl	%edx, %eax
	movb	%al, 6(%esi)
	.loc 1 60 0
	movl	(%ebx), %eax
	movb	%al, 2(%esi)
	.loc 1 61 0
	movl	(%ebx), %eax
	movb	%ah, 3(%esi)
	.loc 1 62 0
	movl	(%ebx), %eax
	shrl	$16, %eax
	movb	%al, 4(%esi)
	.loc 1 63 0
	movl	(%ebx), %eax
	shrl	$24, %eax
	movb	%al, 7(%esi)
	.loc 1 65 0
	movzbl	8(%ebx), %eax
	movb	%al, 5(%esi)
	.loc 1 68 0
	movl	16(%ebx), %ebx
.LVL4:
	testl	%ebx, %ebx
	je	.L1
.LVL5:
.LBE3:
	.loc 1 40 0 discriminator 2
	addl	$1, %edi
.LVL6:
	cmpl	%edi, 8(%ebp)
	jbe	.L1
.LVL7:
.L6:
.LBB4:
	.loc 1 42 0
	movl	4(%ebp), %eax
	leal	(%eax,%edi,8), %esi
.LVL8:
	.loc 1 43 0
	movl	4(%ebx), %eax
	cmpl	$65536, %eax
	ja	.L16
.L3:
	.loc 1 51 0
	movb	$64, 6(%esi)
	movl	$64, %edx
	jmp	.L5
.LVL9:
	.align 16
.L1:
.LBE4:
.LBE5:
	.loc 1 72 0
	addl	$12, %esp
	.cfi_def_cfa_offset 20
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 16
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 12
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 8
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE3:
	.size	_ZN10GDTManager9encodeGDTEv, .-_ZN10GDTManager9encodeGDTEv
	.align 2
	.align 16
	.globl	_ZN10GDTManagerC2Ev
	.type	_ZN10GDTManagerC2Ev, @function
_ZN10GDTManagerC2Ev:
.LFB1:
	.loc 1 9 0
	.cfi_startproc
.LVL10:
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	subl	$104, %esp
	.cfi_def_cfa_offset 112
.LBB6:
	.loc 1 16 0
	leal	32(%esp), %ecx
.LBE6:
	.loc 1 9 0
	movl	112(%esp), %eax
.LBB7:
	.loc 1 18 0
	leal	12(%esp), %edx
	.loc 1 22 0
	leal	52(%esp), %ebx
	.loc 1 12 0
	movl	$0, 24(%esp)
	.loc 1 13 0
	movl	$0, 12(%esp)
	.loc 1 16 0
	movl	%ecx, 28(%esp)
	.loc 1 24 0
	movl	%ecx, 64(%esp)
	.loc 1 31 0
	leal	72(%esp), %ecx
	.loc 1 22 0
	movl	%ebx, 48(%esp)
	.loc 1 14 0
	movl	$0, 16(%esp)
	.loc 1 34 0
	subl	$12, %esp
	.cfi_def_cfa_offset 124
	.loc 1 15 0
	movb	$0, 32(%esp)
	.loc 1 18 0
	movl	%edx, 56(%esp)
	.loc 1 19 0
	movl	$0, 44(%esp)
	.loc 1 20 0
	movl	$-1, 48(%esp)
	.loc 1 21 0
	movb	$-102, 52(%esp)
	.loc 1 25 0
	movl	$0, 64(%esp)
	.loc 1 26 0
	movl	$-1, 68(%esp)
	.loc 1 27 0
	movb	$-110, 72(%esp)
	.loc 1 28 0
	movl	$0, 80(%esp)
	.loc 1 31 0
	movl	%ecx, 4(%eax)
	.loc 1 32 0
	movl	%edx, (%eax)
	.loc 1 34 0
	pushl	%eax
	.cfi_def_cfa_offset 128
	call	_ZN10GDTManager9encodeGDTEv
.LVL11:
.LBE7:
	.loc 1 35 0
	addl	$120, %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE1:
	.size	_ZN10GDTManagerC2Ev, .-_ZN10GDTManagerC2Ev
	.globl	_ZN10GDTManagerC1Ev
	.set	_ZN10GDTManagerC1Ev,_ZN10GDTManagerC2Ev
	.align 2
	.align 16
	.globl	_ZN10GDTManager6setGDTEv
	.type	_ZN10GDTManager6setGDTEv, @function
_ZN10GDTManager6setGDTEv:
.LFB4:
	.loc 1 76 0
	.cfi_startproc
.LVL12:
	subl	$20, %esp
	.cfi_def_cfa_offset 24
	.loc 1 76 0
	movl	24(%esp), %eax
.LVL13:
	.loc 1 78 0
	pushl	4(%eax)
	.cfi_def_cfa_offset 28
.LVL14:
	.loc 1 77 0
	movl	8(%eax), %eax
	leal	-1(,%eax,8), %eax
	.loc 1 78 0
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	setGdtASM
.LVL15:
	.loc 1 80 0
	addl	$28, %esp
	.cfi_def_cfa_offset 4
	.loc 1 79 0
	jmp	reloadSegments
.LVL16:
	.cfi_endproc
.LFE4:
	.size	_ZN10GDTManager6setGDTEv, .-_ZN10GDTManager6setGDTEv
	.globl	defChain
	.section	.bss
	.align 4
	.type	defChain, @object
	.size	defChain, 4
defChain:
	.zero	4
	.text
.Letext0:
	.file 2 "/home/tina/opt/cross/lib/gcc/i686-elf/7.1.0/include/stdint-gcc.h"
	.file 3 "/mnt/c/Users/TIna/OSDev/PlusOne/skeleton/sysroot/usr/include/kernel/GDTManager.h"
	.file 4 "/mnt/c/Users/TIna/OSDev/PlusOne/skeleton/sysroot/usr/include/kernel/tty.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x346
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF33
	.byte	0x4
	.long	.LASF34
	.long	.LASF35
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.long	.LASF0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF1
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF2
	.uleb128 0x2
	.byte	0xc
	.byte	0x4
	.long	.LASF3
	.uleb128 0x2
	.byte	0x10
	.byte	0x4
	.long	.LASF4
	.uleb128 0x3
	.long	.LASF36
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF5
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF6
	.uleb128 0x4
	.long	.LASF9
	.byte	0x2
	.byte	0x2e
	.long	0x66
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF7
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF8
	.uleb128 0x4
	.long	.LASF10
	.byte	0x2
	.byte	0x34
	.long	0x2c
	.uleb128 0x4
	.long	.LASF11
	.byte	0x2
	.byte	0x37
	.long	0x8a
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF12
	.uleb128 0x5
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF13
	.uleb128 0x6
	.long	.LASF37
	.byte	0x14
	.byte	0x3
	.byte	0x6
	.long	0xe8
	.uleb128 0x7
	.long	.LASF14
	.byte	0x3
	.byte	0x7
	.long	0x74
	.byte	0
	.uleb128 0x7
	.long	.LASF15
	.byte	0x3
	.byte	0x8
	.long	0x74
	.byte	0x4
	.uleb128 0x7
	.long	.LASF16
	.byte	0x3
	.byte	0x9
	.long	0x5b
	.byte	0x8
	.uleb128 0x7
	.long	.LASF17
	.byte	0x3
	.byte	0xa
	.long	0xe8
	.byte	0xc
	.uleb128 0x7
	.long	.LASF18
	.byte	0x3
	.byte	0xb
	.long	0xe8
	.byte	0x10
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.long	0x9f
	.uleb128 0x4
	.long	.LASF19
	.byte	0x3
	.byte	0xc
	.long	0x9f
	.uleb128 0x9
	.long	.LASF38
	.byte	0xc
	.byte	0x3
	.byte	0xe
	.long	0x172
	.uleb128 0x7
	.long	.LASF20
	.byte	0x3
	.byte	0x12
	.long	0x172
	.byte	0
	.uleb128 0xa
	.string	"gdt"
	.byte	0x3
	.byte	0x13
	.long	0x178
	.byte	0x4
	.uleb128 0x7
	.long	.LASF21
	.byte	0x3
	.byte	0x14
	.long	0x74
	.byte	0x8
	.uleb128 0xb
	.long	.LASF38
	.byte	0x3
	.byte	0x10
	.long	.LASF39
	.byte	0x1
	.long	0x13d
	.long	0x143
	.uleb128 0xc
	.long	0x17e
	.byte	0
	.uleb128 0xd
	.long	.LASF40
	.byte	0x3
	.byte	0x15
	.long	.LASF41
	.long	0x156
	.long	0x15c
	.uleb128 0xc
	.long	0x17e
	.byte	0
	.uleb128 0xe
	.long	.LASF42
	.byte	0x3
	.byte	0x16
	.long	.LASF43
	.long	0x16b
	.uleb128 0xc
	.long	0x17e
	.byte	0
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.long	0xee
	.uleb128 0x8
	.byte	0x4
	.long	0x7f
	.uleb128 0x8
	.byte	0x4
	.long	0xf9
	.uleb128 0xf
	.long	0x17e
	.uleb128 0x10
	.long	.LASF44
	.byte	0x1
	.byte	0x5
	.long	0x172
	.uleb128 0x5
	.byte	0x3
	.long	defChain
	.uleb128 0x11
	.long	0x15c
	.byte	0x1
	.byte	0x4c
	.long	0x1b7
	.long	.LFB4
	.long	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.long	0x1b7
	.long	0x1e5
	.uleb128 0x12
	.long	.LASF22
	.long	0x184
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x13
	.long	.LASF23
	.byte	0x1
	.byte	0x4d
	.long	0x74
	.long	.LLST3
	.uleb128 0x14
	.long	.LVL15
	.long	0x328
	.uleb128 0x15
	.long	.LVL16
	.long	0x333
	.byte	0
	.uleb128 0x11
	.long	0x143
	.byte	0x1
	.byte	0x25
	.long	0x202
	.long	.LFB3
	.long	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.long	0x202
	.long	0x24f
	.uleb128 0x12
	.long	.LASF22
	.long	0x184
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x13
	.long	.LASF24
	.byte	0x1
	.byte	0x26
	.long	0x172
	.long	.LLST0
	.uleb128 0x16
	.long	.Ldebug_ranges0+0
	.uleb128 0x17
	.string	"i"
	.byte	0x1
	.byte	0x28
	.long	0x91
	.long	.LLST1
	.uleb128 0x16
	.long	.Ldebug_ranges0+0x18
	.uleb128 0x13
	.long	.LASF25
	.byte	0x1
	.byte	0x29
	.long	0x24f
	.long	.LLST2
	.uleb128 0x14
	.long	.LVL3
	.long	0x33e
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.long	0x5b
	.uleb128 0x18
	.long	0x129
	.byte	0x1
	.byte	0x9
	.byte	0
	.long	0x265
	.long	0x29d
	.uleb128 0x19
	.long	.LASF22
	.long	0x184
	.uleb128 0x1a
	.uleb128 0x1b
	.long	.LASF26
	.byte	0x1
	.byte	0xb
	.long	0xee
	.uleb128 0x1b
	.long	.LASF27
	.byte	0x1
	.byte	0xb
	.long	0xee
	.uleb128 0x1b
	.long	.LASF28
	.byte	0x1
	.byte	0xb
	.long	0xee
	.uleb128 0x1b
	.long	.LASF29
	.byte	0x1
	.byte	0x1e
	.long	0x29d
	.byte	0
	.byte	0
	.uleb128 0x1c
	.long	0x7f
	.long	0x2ad
	.uleb128 0x1d
	.long	0x2c
	.byte	0x2
	.byte	0
	.uleb128 0x1e
	.long	0x255
	.long	.LASF45
	.long	0x2cc
	.long	.LFB1
	.long	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0x2cc
	.long	0x328
	.uleb128 0x1f
	.long	0x265
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x20
	.long	0x26e
	.long	0x2f2
	.uleb128 0x21
	.long	0x26f
	.uleb128 0x21
	.long	0x27a
	.uleb128 0x21
	.long	0x285
	.uleb128 0x21
	.long	0x290
	.byte	0
	.uleb128 0x22
	.long	0x26e
	.long	.Ldebug_ranges0+0x30
	.uleb128 0x23
	.long	0x26f
	.uleb128 0x3
	.byte	0x91
	.sleb128 -100
	.uleb128 0x23
	.long	0x27a
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x23
	.long	0x285
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.uleb128 0x23
	.long	0x290
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x14
	.long	.LVL11
	.long	0x1e5
	.byte	0
	.byte	0
	.uleb128 0x24
	.long	.LASF30
	.long	.LASF30
	.byte	0x1
	.byte	0x49
	.uleb128 0x24
	.long	.LASF31
	.long	.LASF31
	.byte	0x1
	.byte	0x4a
	.uleb128 0x24
	.long	.LASF32
	.long	.LASF32
	.byte	0x4
	.byte	0xa
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x3b
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x2
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x2115
	.uleb128 0x19
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0xb
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST3:
	.long	.LVL13-.Ltext0
	.long	.LVL14-.Ltext0
	.value	0x8
	.byte	0x70
	.sleb128 8
	.byte	0x6
	.byte	0x33
	.byte	0x24
	.byte	0x31
	.byte	0x1c
	.byte	0x9f
	.long	0
	.long	0
.LLST0:
	.long	.LVL1-.Ltext0
	.long	.LVL4-.Ltext0
	.value	0x1
	.byte	0x53
	.long	.LVL5-.Ltext0
	.long	.LVL9-.Ltext0
	.value	0x1
	.byte	0x53
	.long	0
	.long	0
.LLST1:
	.long	.LVL1-.Ltext0
	.long	.LVL2-.Ltext0
	.value	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL2-.Ltext0
	.long	.LVL9-.Ltext0
	.value	0x1
	.byte	0x57
	.long	0
	.long	0
.LLST2:
	.long	.LVL2-.Ltext0
	.long	.LVL7-.Ltext0
	.value	0x1
	.byte	0x56
	.long	.LVL8-.Ltext0
	.long	.LVL9-.Ltext0
	.value	0x1
	.byte	0x56
	.long	0
	.long	0
	.section	.debug_aranges,"",@progbits
	.long	0x1c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.value	0
	.value	0
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	0
	.long	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.long	.LBB2-.Ltext0
	.long	.LBE2-.Ltext0
	.long	.LBB5-.Ltext0
	.long	.LBE5-.Ltext0
	.long	0
	.long	0
	.long	.LBB3-.Ltext0
	.long	.LBE3-.Ltext0
	.long	.LBB4-.Ltext0
	.long	.LBE4-.Ltext0
	.long	0
	.long	0
	.long	.LBB6-.Ltext0
	.long	.LBE6-.Ltext0
	.long	.LBB7-.Ltext0
	.long	.LBE7-.Ltext0
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF30:
	.string	"setGdtASM"
.LASF41:
	.string	"_ZN10GDTManager9encodeGDTEv"
.LASF32:
	.string	"terminal_writestring"
.LASF18:
	.string	"next"
.LASF35:
	.string	"/mnt/c/Users/TIna/OSDev/PlusOne/skeleton"
.LASF23:
	.string	"tbl_length"
.LASF36:
	.string	"decltype(nullptr)"
.LASF11:
	.string	"uint64_t"
.LASF21:
	.string	"gdt_length"
.LASF24:
	.string	"cdef"
.LASF25:
	.string	"target"
.LASF43:
	.string	"_ZN10GDTManager6setGDTEv"
.LASF33:
	.string	"GNU C++14 7.1.0 -mtune=generic -march=pentiumpro -g -O2 -ffreestanding"
.LASF7:
	.string	"unsigned char"
.LASF22:
	.string	"this"
.LASF29:
	.string	"gdtArr"
.LASF19:
	.string	"GDTDef_t"
.LASF1:
	.string	"long unsigned int"
.LASF8:
	.string	"short unsigned int"
.LASF20:
	.string	"defs"
.LASF39:
	.string	"_ZN10GDTManagerC4Ev"
.LASF4:
	.string	"__float128"
.LASF34:
	.string	"kernel/arch/i386/GDTManager.cpp"
.LASF14:
	.string	"base"
.LASF26:
	.string	"def1"
.LASF13:
	.string	"unsigned int"
.LASF31:
	.string	"reloadSegments"
.LASF28:
	.string	"def3"
.LASF12:
	.string	"long long unsigned int"
.LASF9:
	.string	"uint8_t"
.LASF44:
	.string	"defChain"
.LASF15:
	.string	"limit"
.LASF42:
	.string	"setGDT"
.LASF2:
	.string	"long long int"
.LASF37:
	.string	"GDTDef"
.LASF45:
	.string	"_ZN10GDTManagerC2Ev"
.LASF16:
	.string	"type"
.LASF6:
	.string	"short int"
.LASF40:
	.string	"encodeGDT"
.LASF10:
	.string	"uint32_t"
.LASF0:
	.string	"long int"
.LASF3:
	.string	"long double"
.LASF27:
	.string	"def2"
.LASF5:
	.string	"signed char"
.LASF38:
	.string	"GDTManager"
.LASF17:
	.string	"prev"
	.ident	"GCC: (GNU) 7.1.0"
