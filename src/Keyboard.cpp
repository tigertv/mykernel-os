#include <myos/Keyboard.h>

Keyboard::Keyboard() {

}

uint8_t Keyboard::getKey() {
	uint8_t res = inb(0x60);
	return res;

  uint8_t keycode = 0;
  while((keycode = inb(KEYBOARD_PORT)) != 0){
    if(keycode > 0)
      return keycode;
  }
  return keycode;
}

inline uint8_t Keyboard::inb(uint16_t port) {
	uint8_t result;
	asm volatile("inb %1, %0" : "=a" (result) : "Nd" (port));
	return result;
}

uint8_t Keyboard::readStatus() {
	uint8_t res = inb(0x64);
	return res;
}
