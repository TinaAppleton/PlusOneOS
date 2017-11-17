#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/multiboot.h>
#include <kernel/GDTManager.h>
#include <kernel/paging.h>

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main(multiboot_info_t* multiboot) {
	/* Initialize terminal interface */
	terminal_initialize();
	terminal_writestring("Terminal Initialized successfully.\n");
	
	
	//GDT stuff
	terminal_writestring("Initializing GDT...\n");
	GDTManager gdt();
	
	terminal_writestring("GDT initialized successfully.\n");
 
	//paging stuff
	terminal_writestring("Initializing MMU..\n");
	Paging paging;
	paging.setupMultiboot(multiboot);
	
	//puts("testing...");
 
	/* Newline support is left as an exercise. */
	terminal_writestring("Hello, kernel World!\n");
}

//virtual function helper
extern "C" void __cxa_pure_virtual()
{
    // Do nothing or print an error message.
}