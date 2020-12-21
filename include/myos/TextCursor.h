#ifndef TEXT_CURSOR_H
#define TEXT_CURSOR_H

#include "types.h"

class TextCursor {
private:
	int x;
	int y;
public:
	TextCursor();
	void enable(uint8_t cursor_start, uint8_t cursor_end);
	void disable();
	void move(int x, int y);
	uint16_t getPosition();
};

#endif
