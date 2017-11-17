#include <stdint.h>
#include <kernel/paging.h>
#include <kernel/tty.h>

static inline void reloadPaging();
extern uint32_t _kernel_start;
extern uint32_t _kernel_end;
const uint32_t PHYS_DIR_SIZE  = 131072;

uint32_t phys_address_directory[PHYS_DIR_SIZE];

/****************************
*	Paging class functions	*
*			start			*
****************************/
Paging::Paging(uint32_t* page_dir) {
	//set up a table to store the page directory at the end of
	uint32_t directory_table[1024] __attribute__((aligned(4096)));
	
	//clear the table so that all pages are set to not present
	uint32_t i;
	for(i = 0; i < 1024; i++)
	{
		directory_table[i] = 0;
	}
	
	//map the page directory to the last entry of the page table;
	directory_table[1023] = ((uint32_t)page_dir * 0xFFFFF000) + 3;

	//add the new table to the directory
	page_dir[1023] = ((uint32_t)directory_table) - 0xC0000000 + 3;
	
	//reload page table
	reloadPaging(); 
	
	//clear the physical page directory
	for(i = 0; i < PHYS_DIR_SIZE; i++)
	{
		phys_address_directory[i] = 0;
	}
	
	//initialize helper variables for establishing the kernel physical pages
	uint32_t kernel_length = _kernel_start - _kernel_end;
	uint32_t kernel_pages = kernel_length/4096;
	uint32_t kernel_first_page = (_kernel_start - 0xC0000000) / 4096;

	//set the kernel pages to used
	for(i = 0; i < kernel_pages; i++)
	{
		uint32_t cur_phys_page = kernel_first_page + i;
		uint32_t phys_dir_index = cur_phys_page / 32;
		uint32_t phys_dir_offset = cur_phys_page % 32;
		phys_address_directory[phys_dir_index] = ((uint32_t)1) << phys_dir_offset;
	}
	
	//set the terminal memory page to used
	uint32_t terminal_phys_page = 0x000B8000 / 4096;
	uint32_t term_phys_dir_index = terminal_phys_page / 32;
	uint32_t term_phys_dir_offset = terminal_phys_page % 32;
	phys_address_directory[term_phys_dir_index] = ((uint32_t)1) << term_phys_dir_offset;
	
	//set the page directory area to used
	phys_address_directory[PHYS_DIR_SIZE - 1] = 0x80000000;
	
	//set the major class variables
	this->phys_directory = phys_address_directory;
	this->page_directory = (uint32_t*)(0x3E7000);
}

uint32_t* Paging::allocPage() {
	//find first free physical page
	
	int arrayIndex, bitIndex;
	arrayIndex = 0;
	bitIndex = 0;
	int i = 0;
	while((i < PHYS_DIR_SIZE) && arrayIndex == 0) {
		if(!(phys_directory[i] == 0xFFFFFFFF)) {
			//one of the pages at this index is free, find it
			int b = 0;
			while((b < 32) && (bitIndex == 0)) {
				if(((1 << b) & phys_directory[i]) == 0) {
					//this bit index is free, claim it
					phys_directory[i] = phys_directory[i] | (1 << b);
					arrayIndex = i;
					bitIndex = b;
				}
				b++;
			}
		}
		i++;
	}
	// test if a free physical index was found, if not, return null pointer
	if(arrayIndex == 0 || bitIndex == 0)
		return 0;
	
	// find a free virtual page
	int d;
	for(d = 0; d < 1024; d++) {
		int t;
		for (t = 0; t < 1024; t++) {
			uint32_t* page_tbl = (uint32_t*)page_directory[d];
			if((page_tbl[t] & 1) == 0) {
				//found a free page, grab it
				page_tbl[t] = ((((arrayIndex * 32) + bitIndex) * 4096) + 3);
				reloadPaging();
				uint32_t* retval = (uint32_t*)(((d * 1024) + t) * 4096);
				return retval;
			}
		}
	}
	
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
	
}

void Paging::freePage(uint32_t* virt_addr) {
	uint32_t* phys_addr = getPhysAddrFromVirt(virt_addr);
	freeVirtPage(virt_addr);
	freePhysPage(phys_addr);
}

bool Paging::isPhysPagePresent(uint32_t* phys_addr) {
	
	uint32_t phys_page = ((uint32_t)phys_addr) / 4096;
	
	uint32_t index = phys_page / 32;
	uint32_t offset = phys_page % 32;
	
	//check to see if the page is actually in use. If yes,
	//free it. if not, return
	if(phys_address_directory[index] == 0) {
		//no pages at this index are in use, return
		return false;
	} else {
		//check to see if the specific page is in use
		uint32_t checker = phys_address_directory[index];
		if((checker & (((uint32_t)1) << offset)) == 0) {
			//the specific page is not set, return
			return false;
		} else {
			//the page is present
			return true;
		}
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
	uint32_t index = phys_page / 32;
	uint32_t offset = phys_page % 32;
	
	//check to see if it's a bad page
	if(index > (PHYS_DIR_SIZE - 1))
		return;
	
	//check to see if the page is actually in use. If yes,
	//free it. if not, return
	if(phys_address_directory[index] == 0) {
		//no pages at this index are in use, return
		return;
	} else {
		//check to see if the specific page is in use
		uint32_t checker = phys_address_directory[index];
		if((checker & (((uint32_t)1) << offset)) == 0) {
			//the specific page is not set, return
			return;
		} else {
			//clear the page
			uint32_t ander = ~(((uint32_t)1) << offset);
			phys_address_directory[index] = phys_address_directory[index] & ander;
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
	uint32_t phys_dir_index = phys_page / 32;
	uint32_t phys_dir_offset = phys_page % 32;
	
	if(!isPhysPagePresent(phys_addr))
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
		if(virt_multiboot == 0){ return 0;}
			//return false;
		//return true;
	} else {
		//multiboot structure is not in memory, map it
		virt_multiboot = (multiboot_info_t*)findFirstFreeVirt((uint32_t*)0xC0100000);
		//terminal_writeHex((uint32_t)virt_multiboot);
		//return (uint32_t)virt_multiboot;
		if(virt_multiboot == 0) {}
			//return false; // failed to setup the multiboot info tables
		
		//we got a good virtual address, now just map it to our physical address
		//uint32_t virtSuccess = setVirtPage((uint32_t*)multiboot, (uint32_t*)virt_multiboot, true, true, false);
		bool physSuccess = setPhysPage((uint32_t*)multiboot, true, true, false);
		//return virtSuccess;
		//return (virtSuccess && physSuccess);
		//return false;
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
		while((!success_t) && (t < 1024)) {
			if((page_tbl[t] & ((uint32_t)1)) == 0) {
				//free page!
				success_d = true;
				success_t = true;
				break;
			}
			
			t++;
		}
		
		if(success_d)
			break;
		d++;
	}
	
	if(success_d && success_t) {
		ret_addr = (uint32_t*)(((d * 1024) + t) * 4096);
	}
	
	//terminal_writeHex((uint32_t)ret_addr);
	return ret_addr;
}
bool Paging::setPhysPage(uint32_t* address, bool present, bool removable, bool isUserPage) {
	return false;
}
uint32_t Paging::setVirtPage(uint32_t* phys_address, uint32_t* virt_address, bool present, bool writable, bool isUserPage) {
	uint32_t* aligned_phys = (uint32_t*)(phys_address - ((uint32_t)phys_address % 4096));
	uint32_t page = (uint32_t)virt_address / 4096;
	uint32_t page_dir_index = page / 1024;
	uint32_t page_tbl_index = page % 1024;
	
	uint32_t* cur_page_dir = (uint32_t*)(page_directory[page_dir_index]);
	uint32_t tester1 = (uint32_t)cur_page_dir;
	//terminal_writeHex(tester1);
	if(((*cur_page_dir) & 1) != 1) {
		return false;
	}
	uint32_t* cur_page_tbl = (uint32_t*)(cur_page_dir[page_tbl_index]);
	//terminal_writeHex((uint32_t)cur_page_tbl);
	
	uint32_t adder = 0;
	if(present)
		adder += 1;
	if(writable)
		adder += 2;
	if(isUserPage)
		adder += 4;
	
	//(*cur_page_tbl) = ((uint32_t)aligned_phys) + adder;
	
	//return true;
	return page_dir_index;
}
/****************************
*	Paging class functions	*
*			 end			*
****************************/


static inline void reloadPaging()
{
	asm volatile ("movl %cr3, %eax\n\t movl %eax, %cr3");
}