#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "types.h"

class Keyboard {
private:
	static const uint8_t KEYBOARD_PORT = 0x60;
	static inline uint8_t inb(uint16_t port);
public:
	Keyboard();
	uint8_t getKey();
	uint8_t readStatus();
};

#endif
