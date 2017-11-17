#ifndef PAGING_H
#define PAGING_H
#include <stdint.h>
#include <kernel/multiboot.h>

class Paging {
	public:
		Paging();
		uint32_t* allocPage();
		uint32_t* allocPageAtPhys(uint32_t* phys_addr);
		uint32_t* allocPageAtVirt(uint32_t* virt_addr);
		void freePage(uint32_t* virt_addr);
		uint32_t setupMultiboot(multiboot_info_t* multiboot);
		uint32_t* getPhysAddrFromVirt(uint32_t* virt_addr);
		uint32_t* getVirtAddrFromPhys(uint32_t* phys_addr);
		void printPageDir();
	private:
		uint32_t* page_directory;
		uint8_t* phys_directory;
		bool isPhysPagePresent(uint32_t* phys_addr);
		bool isVirtPagePresent(uint32_t* virt_addr);
		void freePhysPage(uint32_t* phys_addr);
		void freeVirtPage(uint32_t* virt_addr);
		uint32_t* findFirstFreeVirt(uint32_t* starting_addr);
		uint32_t* findFirstFreePhys(uint32_t* starting_addr);
		bool setPhysPage(uint32_t* address, bool present, bool removable, bool isUserPage);
		bool setVirtPage(uint32_t* phys_address, uint32_t* virt_address, bool present, bool writable, bool isUserPage); 
};


#endif