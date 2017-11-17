#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/multiboot.h>
#include <kernel/paging.h>

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main(uint32_t* page_dir, multiboot_info_t* multiboot) {
	/* Initialize terminal interface */
	terminal_initialize();
	terminal_writestring("Terminal Initialized successfully.\n");
	
	terminal_writestring("Initializing MMU...\n");
	Paging paging_obj(page_dir);
	uint32_t tester = paging_obj.setupMultiboot(multiboot);
	terminal_writeHex(tester);
 
	/* Newline support is left as an exercise. */
	terminal_writestring("Hello, kernel World!\n");
}

//virtual function helper
extern "C" void __cxa_pure_virtual()
{
    // Do nothing or print an error message.
}