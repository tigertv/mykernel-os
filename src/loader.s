.intel_syntax noprefix
/*.set MAGIC, 0x1BADB002 - version 1 */
.set MAGIC, 0xe85250d6 /* version 2 */
.set ARCH, 0 /* i386 */
.set HEADER_LEN, header_end - header_start
.set CHECKSUM, -(MAGIC + ARCH + HEADER_LEN)

.section .multiboot
header_start:
	.long MAGIC
	.long ARCH 
	.long HEADER_LEN 
	.long CHECKSUM

	/* multiboot tags are here */

	/* end tag */
	.short 0 /* end tag type */
	.short 0 /* flags */
	.long 8 /* size of the tag including itself */
header_end:

.code32

.section .text
.extern kernelMain
.extern callConstructors
.global loader

loader:
	mov esp, offset kernel_stack
	call callConstructors
	push eax
	push ebx
	call kernelMain

_stop:
	cli
	hlt
	jmp _stop

.section .bss
.space 2*1024*1024;
kernel_stack: 
