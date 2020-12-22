#ifndef DRAW_CONTEXT_H
#define DRAW_CONTEXT_H

#include <myos/VGArray.h>


class DrawContext {
private:
	VGArray& vga; 
	int scrWidth;
	int scrHeight;
	int videoBegin;
	int color;
	
public:
	DrawContext(VGArray& vga);
	void drawRect(int x, int y, int width, int height);
	void drawPoint(int x1, int y1);
	void setColor(int color);
	void drawCircle(int x, int y, int radius);
	void drawLine(int x0, int y0, int x1, int y1);
};

#endif
