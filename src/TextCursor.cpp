#include <myos/TextCursor.h>
#include <myos/ports.h>

TextCursor::TextCursor() : x(0), y(0) {
	
}

void TextCursor::enable(uint8_t cursor_start, uint8_t cursor_end) {
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void TextCursor::disable() {
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void TextCursor::move(int x, int y) {
	this->x = x;
	this->y = y;

	int width = 80;
	uint16_t pos = y * width + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

uint16_t TextCursor::getPosition() {
    uint16_t pos = 0;
    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);
    outb(0x3D4, 0x0E);
    pos |= ((uint16_t)inb(0x3D5)) << 8;
    return pos;
}
