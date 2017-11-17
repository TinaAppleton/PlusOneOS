#include <stddef.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <kernel/GDTManager.h>
GDTDef_t* defChain;



GDTManager::GDTManager() {
	//define the necessary GDTs
	GDTDef_t def1,def2,def3;
	def1.prev = nullptr;
	def1.base = 0;
	def1.limit = 0;
	def1.type = 0;
	def1.next = &def2;
	
	def2.prev = &def1;
	def2.base = 0;
	def2.limit = 0xffffffff;
	def2.type = 0x9A;
	def2.next = &def3;
	
	def3.prev = &def2;
	def3.base = 0;
	def3.limit = 0xffffffff;
	def3.type = 0x92;
	def3.next = nullptr;
	
	uint64_t gdtArr[3];
	gdt = gdtArr;
	defs = &def1;
	
	encodeGDT();
}

void GDTManager::encodeGDT() {
	GDTDef_t* cdef = defs;
	
	for(uint32_t i = 0; i < gdt_length; i++) {
		uint8_t* target;
		target = (uint8_t*)(&gdt[i]);
		if((cdef->limit > 65536) && ((cdef->limit & 0xFFF) != 0xFFF)) {
			terminal_writestring("bad gdt entry...\n");
		}
		
		if(cdef->limit > 65536) {
			cdef->limit = cdef->limit >> 12;
			target[6] = 0xC0;
		} else {
			target[6] = 0x40;
		}
		
		//encode limit
		target[0] = cdef->limit & 0xFF;
		target[1] = (cdef->limit >> 8) & 0xFF;
		target[6] |= (cdef->limit >> 16) & 0xF;
		
		//encode base
		target[2] = cdef->base & 0xFF;
		target[3] = (cdef->base >> 8) & 0xFF;
		target[4] = (cdef->base >> 16) &0xFF;
		target[7] = (cdef->base >> 24) & 0xFF;
		
		target[5] = cdef->type;
		
		//get the next definition
		if(cdef->next == nullptr)
			break;
		cdef = cdef->next;
	}
}
extern "C" {void _setGdtASM(uint32_t length, uint32_t address);}
extern "C" {void _reloadSegments();}

void GDTManager::setGDT() {
	uint32_t tbl_length = (8*gdt_length)-1;
	_setGdtASM(tbl_length, (uint32_t)gdt);
	_reloadSegments();
}