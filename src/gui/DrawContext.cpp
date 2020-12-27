#include <myos/gui/DrawContext.h>


DrawContext::DrawContext(VGArray& vga) : vga(vga) {
	scrWidth = vga.getWidth();
	scrHeight = vga.getHeight();
	videoBegin = vga.getVideoBegin();
	color = 0;
}

void DrawContext::setColor(int color) {
	this->color = color;	
}

void DrawContext::drawRect(int x, int y, int width, int height) {
	if (x >= scrWidth || y >= scrHeight) return;
	int x2 = x + width;
	int y2 = y + height;
	if (x2 < 0 || y2 < 0) return;

	// window limits
	if (x2 >= scrWidth) width = scrWidth - x;
	if (y2 >= scrHeight) height = scrHeight - y;
	if (x < 0) {
		width += x;
		x = 0;
	}
	if (y < 0) {
		height += y;
		y = 0;
	}

	uint8_t* p = (uint8_t*) videoBegin;
	p += x + y * scrWidth ;
	for (int j = 0; j < height; ++j) {
		// draw horizontal line
		for (int i = 0; i < width; ++i) {
			*p++ = color;
		}
		p += scrWidth - width;
	}
}


void DrawContext::drawPoint(int x, int y) {
	if (x < 0 || x >= scrWidth) return;
	if (y < 0 || y >= scrHeight) return;

	uint8_t* p = (uint8_t*)videoBegin;
	p += x + y * scrWidth;
	*p = color;
}

void DrawContext::drawLine(int x1, int y1, int x2, int y2) {

	// TODO: check boundaries
	int dx = x2 - x1;
	int dy = y2 - y1; 
	int diry = dy;

	if (dx < 0) dx = -dx;
	if (dy < 0) {
		dy = -dy;
		diry = -1;
	} else if (diry != 0) diry = 1;

	int err = 0;
	int derr = dy + 1;
	int y = y1;

	for(int x = x1; x <= x2; ++x) {
		drawPoint(x, y);
		err += derr;
		if (err >= (dx + 1)) {
			y += diry;
			err -= dx + 1;
		}
	}


}

void DrawContext::drawCircle(int x, int y, int radius) {
	// TODO: check boundaries
	int x1 = 0;
	int y1 = radius;

	int delta = 1 - 2 * radius;
	int error = 0;
	while (y1 >= 0) {
		drawPoint(x + x1, y + y1);
		drawPoint(x + x1, y - y1);
		drawPoint(x - x1, y + y1);
		drawPoint(x - x1, y - y1);
		error = 2 * (delta + y1) - 1;
		if ((delta < 0) && (error <= 0)) {
			delta += 2 * (++x1) + 1;
			continue;
		}
		if ((delta > 0) && (error > 0)) {
			delta -= 2 * (--y1) + 1;
			continue;
		}
		delta += 2 * ((++x1) - (--y1));
	}
}
