#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
//static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xC03FF000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

const int writer_length = 20;
char writer[writer_length];


void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	
	for(int i = 0; i < writer_length; i++) {
		writer[i] = 0;
	}
}

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
    /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

void update_cursor() {
	unsigned short index = terminal_row * VGA_WIDTH + terminal_column;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char)(index&0xFF));
	
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char)((index>>8)&0xFF));
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_scroll() {
	for(size_t y = 0; y < VGA_HEIGHT; y++) {
		for(size_t x = 0; x < VGA_WIDTH; x++) {
			if(y == (VGA_HEIGHT-1)) {
				const size_t index = y * VGA_WIDTH + x;
				terminal_buffer[index] = vga_entry(' ', terminal_color);
			} else {
				const size_t newIndex = y*VGA_WIDTH+x;
				const size_t oldIndex = (y+1)*VGA_WIDTH+x;
				terminal_buffer[newIndex] = terminal_buffer[oldIndex];
			}
		}
	}
}

void terminal_putchar(char c) {
	unsigned char uc = c;
	if(uc == '\n')
	{
		terminal_column = 0;
		if(++terminal_row == VGA_HEIGHT) {
			terminal_row = VGA_HEIGHT - 1;
			terminal_scroll();
		}
	} else {
		terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT) {
				terminal_row = VGA_HEIGHT - 1;
				terminal_scroll();
			}
		}
	}
	update_cursor();
}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}

void terminal_writeHex(const uint32_t hex_val) {
	
	for(int i = 0; i < writer_length; i++) {
		writer[i] = 0;
	}
	uint32_t counter = writer_length - 2;
	uint32_t holder = hex_val;
	do {
		uint32_t current = holder % 16;
		if(current > 9)
			writer[counter] = current + 65;
		else
			writer[counter] = current + 48;
		
		counter --;
		holder = holder/16;
	}while(holder > 0);
	
	writer[counter-1] = '0';
	writer[counter] = 'x';
	
	terminal_write(&(writer[counter-1]), writer_length-counter);
}
