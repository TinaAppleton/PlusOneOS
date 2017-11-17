#ifndef _GDTMANAGER_H
#define _GDTMANAGER_H
#include <stddef.h>
#include <stdint.h>

typedef struct GDTDef {
		uint32_t base;
		uint32_t limit;
		uint8_t type;
		GDTDef* prev;
		GDTDef* next;
} GDTDef_t;

class GDTManager {
	public:
		GDTManager();
	private:
		GDTDef_t* defs;
		uint64_t* gdt;
		uint32_t gdt_length;
		void encodeGDT();
		void setGDT();
};


#endif