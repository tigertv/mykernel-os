#ifndef VIDEO_GRAPHICS_ARRAY
#define VIDEO_GRAPHICS_ARRAY

#include "types.h"


class VGArray{
private:
	uint32_t videoBegin;
	int width;
	int height;
	
public:
	VGArray();
	void setMode();
	void readRegs(uint8_t *regs);
	void writeRegs(uint8_t *regs);
	uint32_t getVideoBegin();
	int getWidth();
	int getHeight();
};

#endif
