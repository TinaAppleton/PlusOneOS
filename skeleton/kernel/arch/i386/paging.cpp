#include <stdint.h>
#include <kernel/paging.h>
#include <kernel/tty.h>

static inline void reloadPaging();
extern uint32_t _kernel_start;
extern uint32_t _kernel_end;
const uint32_t PHYS_DIR_SIZE  = 1048576;

uint32_t phys_address_directory[PHYS_DIR_SIZE/4];
/*
 *	PHYSICAL DIRECTORY STRUCTURE
 *	each entry represents 1 entry in the page directory
 *	1st bit = page present, set to 1 if it is linked to a page table entry
 *	2nd bit = user bit, set to 1 if user accessible, 0 if os only
 *	3rd bit = removable bit, set to 1 if removable, 0 if necessary to remain
 *	remaining bits = currently unused

*/

/****************************
*	Paging class functions	*
*			start			*
****************************/
Paging::Paging() {
	//set up the location of the page directory;
	page_directory = (uint32_t*)0xFFFFF000;
	
	//set up the physical directory;
	phys_directory = (uint8_t*)phys_address_directory;
	
	uint32_t i;
	
	//now clear the physical directory
	for(i = 0; i < PHYS_DIR_SIZE; i++) {
		phys_directory[i] = 0;
	}
	
	//initialize helper variables for establishing the kernel physical pages
	uint32_t kernel_length = _kernel_start - _kernel_end;
	uint32_t kernel_pages = (kernel_length/4096)+1;
	uint32_t kernel_first_page = (_kernel_start - 0xC0000000) / 4096;

	//set the kernel pages to used
	for(i = 0; i < kernel_pages; i++)
	{
		phys_directory[kernel_first_page+i] = 1;
	}
	
	//set the terminal memory page to used
	uint32_t terminal_phys_page = 0x000B8000 / 4096;
	phys_directory[terminal_phys_page] = 1;
	
	//set the page directory area to used
	uint32_t base_entry = ((uint32_t)page_directory) / 4096;
	for(i = 0; i < 1024; i++) {
		phys_directory[base_entry+i] = 1;
	}
	
}



uint32_t* Paging::allocPage() {
	//find first free physical page
	
	uint32_t* phys_addr = findFirstFreePhys((uint32_t*)0);

	// find a free virtual page
	uint32_t* virt_addr = findFirstFreeVirt((uint32_t*)0);
	
	if(virt_addr == 0 || phys_addr == 0) 
		return 0;
	
	setPhysPage(phys_addr, true, true, false);
	setVirtPage(phys_addr, virt_addr, true, true, false);
	return virt_addr;
	
	// if it hasn't returned by now, no free pages left. return 0
	return 0;
}

uint32_t* Paging::allocPageAtPhys(uint32_t* phys_addr) {
	if(isPhysPagePresent(phys_addr))
		return getVirtAddrFromPhys(phys_addr);
	
	uint32_t* virt_addr = findFirstFreeVirt((uint32_t*)0);
	if(virt_addr == 0)
		return 0;
	
	setPhysPage(phys_addr, true, true, false);
	setVirtPage(phys_addr, virt_addr, true, true, false);
	return virt_addr;
}

uint32_t* Paging::allocPageAtVirt(uint32_t* virt_addr) {
	if(isVirtPagePresent(virt_addr))
		return getPhysAddrFromVirt(virt_addr);
	
	uint32_t* phys_addr = findFirstFreePhys((uint32_t*)0);
	if(phys_addr == 0)
		return 0;
	
	setPhysPage(phys_addr, true, true, false);
	setVirtPage(phys_addr, virt_addr, true, true, false);
	return phys_addr;
}

void Paging::freePage(uint32_t* virt_addr) {
	uint32_t* phys_addr = getPhysAddrFromVirt(virt_addr);
	freeVirtPage(virt_addr);
	freePhysPage(phys_addr);
}

bool Paging::isPhysPagePresent(uint32_t* phys_addr) {
	
	uint32_t phys_page = ((uint32_t)phys_addr) / 4096;
	
	//check to see if the page is actually in use. If yes,
	//free it. if not, return
	if(phys_directory[phys_page] == 0) {
		//no pages at this index are in use, return
		return false;
	} else {
		//the page is present
		return true;
	}
	
	return false;
}

bool Paging::isVirtPagePresent(uint32_t* virt_addr) {
	//set up variables for finding the page which represents the address
	uint32_t page_index = ((uint32_t)virt_addr) / 4096;
	uint32_t page_dir_index = page_index / 1024;
	uint32_t page_tbl_index = page_index % 1024;
	
	if((page_directory[page_dir_index] & 1) == 1) {
		//page directory entry is present, test page table
		uint32_t* page_table = (uint32_t*)page_directory[page_dir_index];
		if((page_table[page_tbl_index] & 1) == 1) {
			//page table is present, return true
			return true;
		}
	}
	//all unsuccessful cases land here, return false
	return false;
}


void Paging::freePhysPage(uint32_t* phys_addr) {
	
	//set up helper variables
	uint32_t phys_page = ((uint32_t)phys_addr) / 4096;

	
	//check to see if it's a bad page
	if(phys_page > (PHYS_DIR_SIZE - 1))
		return;
	
	//check to see if the page is actually in use. If yes,
	//free it. if not, return
	if(phys_directory[phys_page] == 0) {
		//no pages at this index are in use, return
		return;
	} else {
		//check to see if the specific page is in use
		uint32_t checker = phys_directory[phys_page];
		if((checker & 1) == 0) {
			//the specific page is not set, return
			return;
		} else {
			//clear the page
			phys_directory[phys_page] = 0;
		}
	}
}

void Paging::freeVirtPage(uint32_t* virt_addr) {
	//set up helper variables
	uint32_t page_counter = ((uint32_t)virt_addr) / 4096;
	uint32_t page_dir_index = page_counter / 1024;
	uint32_t page_tbl_index = page_counter % 1024;
	uint32_t* page_tbl = (uint32_t*)page_directory[page_dir_index];
	
	//check to see if the page is actuall in use
	if((page_tbl[page_tbl_index] & 1) == 0) {
		//table is not present, return
		return;
	}
	//if it is present, remove it
	page_tbl[page_tbl_index] = 0;
	
	reloadPaging();
}

uint32_t* Paging::getPhysAddrFromVirt(uint32_t* virt_addr) {
	uint32_t* phys_addr = 0;
	uint32_t addr_offset = ((uint32_t)virt_addr) % 4096;
	uint32_t page_counter = ((uint32_t)virt_addr) / 4096;
	uint32_t page_dir_index = page_counter / 1024;
	uint32_t page_tbl_index = page_counter % 1024;
	uint32_t* cur_page_tbl = (uint32_t*)(page_directory[page_dir_index]);
	if((cur_page_tbl[page_tbl_index] & 1) == 1) {
		phys_addr = (uint32_t*)((cur_page_tbl[page_tbl_index] & 0xFFFFF000) + addr_offset);
	}
	return phys_addr;
}

uint32_t* Paging::getVirtAddrFromPhys(uint32_t* phys_addr) {
	uint32_t* virt_addr = 0;
	uint32_t addr_offset = ((uint32_t)phys_addr) % 4096;
	uint32_t aligned_phys = ((uint32_t)phys_addr) - addr_offset;
	uint32_t phys_page = ((uint32_t)phys_addr) / 4096;
	
	if(!isPhysPagePresent((uint32_t*)phys_page))
		return virt_addr;
	
	int d, t;
	for(d = 0; d < 1024; d++)
	{
		if ((page_directory[d] & 1) == 1) {
			uint32_t* dir_entry = (uint32_t*)(page_directory[d] & 0xFFFFF000);
			for(t = 0; t < 1024; t++) {
				if((dir_entry[t] & 1) == 1) {
					uint32_t tbl_entry = (dir_entry[t] & 0xFFFFF000);
					if(tbl_entry == aligned_phys) {
						virt_addr = (uint32_t*)((d * 1024 * 4096) + (t * 4096) + addr_offset);
					}
				}
			}
		}
	}
	return virt_addr;
}

uint32_t Paging::setupMultiboot(multiboot_info_t* multiboot) {
	multiboot_info_t* virt_multiboot = 0;
	if(isPhysPagePresent(((uint32_t*)multiboot))) {
	
		//multiboot structure is in virtual memory, get its virtual address
		virt_multiboot = (multiboot_info_t*)getVirtAddrFromPhys((uint32_t*)multiboot);
		if(virt_multiboot == 0)
			return 1;
	} else {
		//multiboot structure is not in memory, map it
		virt_multiboot = (multiboot_info_t*)findFirstFreeVirt((uint32_t*)0xC0100000);
		if(virt_multiboot == 0) {}
			return 2; // failed to setup the multiboot info tables
		
		//we got a good virtual address, now just map it to our physical address
		bool virtSuccess = setVirtPage((uint32_t*)multiboot, (uint32_t*)virt_multiboot, true, true, false);
		bool physSuccess = setPhysPage((uint32_t*)multiboot, true, true, false);
		if(!(virtSuccess && physSuccess))
			return 3;
		
		virt_multiboot += ((uint32_t)multiboot % 4096);
	}
	
	multiboot = virt_multiboot;
	
	return 0;
}

void Paging::printPageDir() {
	for(int i = 0; i < 1024; i++) {
		//terminal_writeHex(page_directory[i]);
		terminal_writestring("\n");
	}
}

uint32_t* Paging::findFirstFreePhys(uint32_t* starting_addr) {
	uint32_t start_page = ((uint32_t)starting_addr)/4096;
	
	for(uint32_t i = start_page; i < PHYS_DIR_SIZE; i++) {
		if(phys_directory[i] == 0)
			return (uint32_t*)(i*4096);
	}
	return 0;
}

uint32_t* Paging::findFirstFreeVirt(uint32_t* starting_addr) {
	uint32_t* ret_addr = 0;
	
	uint32_t page_counter = ((uint32_t)starting_addr) / 4096;
	uint32_t start_page_dir_index = page_counter / 1024;
	uint32_t start_page_tbl_index = page_counter % 1024;
	
	uint32_t d = start_page_dir_index;
	uint32_t t = start_page_tbl_index;
	bool success_d = false;
	bool success_t = false;
	
	while((!success_d) && (d < 1024))
	{
		uint32_t* page_tbl = (uint32_t*)page_directory[d];
		if((((uint32_t)page_tbl) & (uint32_t)1) == 1) {
			while((!success_t) && (t < 1024)) {
				if((page_tbl[t] & ((uint32_t)1)) == 0) {
					//free page!
					success_d = true;
					success_t = true;
					break;
				}
				
				t++;
			}
		}
		
		if(success_d)
			break;
		d++;
	}
	
	if(success_d && success_t) {
		ret_addr = (uint32_t*)(((d * 1024) + t) * 4096);
	}
	
	return ret_addr;
}

bool Paging::setPhysPage(uint32_t* address, bool present, bool removable, bool isUserPage) {
	uint32_t page = (uint32_t)address / 4096;
	
	uint32_t adder = 0;
	if(present)
		adder += 1;
	if(isUserPage)
		adder += 2;
	if(removable)
		adder += 4;
	
	phys_directory[page] = adder;
	
	return true;
}

bool Paging::setVirtPage(uint32_t* phys_address, uint32_t* virt_address, bool present, bool writable, bool isUserPage) {
	uint32_t* aligned_phys = (uint32_t*)(phys_address - ((uint32_t)phys_address % 4096));
	uint32_t page = (uint32_t)virt_address / 4096;
	uint32_t page_dir_index = page / 1024;
	uint32_t page_tbl_index = page % 1024;
	
	uint32_t* cur_page_dir = (uint32_t*)(page_directory[page_dir_index]);

	if(((*cur_page_dir) & 1) != 1) {
		return false;
	}
	uint32_t* cur_page_tbl = (uint32_t*)(cur_page_dir[page_tbl_index]);

	
	uint32_t adder = 0;
	if(present)
		adder += 1;
	if(writable)
		adder += 2;
	if(isUserPage)
		adder += 4;
	
	(*cur_page_tbl) = ((uint32_t)aligned_phys) + adder;
	reloadPaging();
	
	return true;
}

/****************************
*	Paging class functions	*
*			 end			*
****************************/


static inline void reloadPaging()
{
	asm volatile ("movl %cr3, %eax\n\t movl %eax, %cr3");
}