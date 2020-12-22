#ifndef WINDOW_H
#define WINDOW_H

#include <myos/types.h>
#include "DrawContext.h"


class Window {
private:
	int x;
	int y;
	int height;
	int width;
	int color;
	DrawContext& dc;
	
public:
	Window(DrawContext& dc);
	void moveAtXY(int x, int y);
	void setSizes(int x, int y, int width, int height);
	void setColor(int color);
	void show();
	void hide();
};

#endif
