#ifndef PORTS_H
#define PORTS_H

#include "types.h"


// TODO: Refactor it all !!!
inline void outb(uint16_t port, uint8_t data) {
	asm volatile("outb %0, %1" : : "a" (data), "Nd" (port));
}

// TODO: Refactor it all !!!
inline uint8_t inb(uint16_t port) {
	uint8_t result;
	asm volatile("inb %1, %0" : "=a" (result) : "Nd" (port));
	return result;
}

#endif
