#include <myos/gui/Window.h>


Window::Window(DrawContext& dc) : dc(dc) {
	x = 0;
	y = 0;
	height = 100;
	width = 100;
	color = 1;
}

void Window::moveAtXY(int x, int y) {
	this->x = x;
	this->y = y;
}

void Window::show() {
	dc.setColor(color);
	dc.drawRect(x, y, width, height);	
}

void Window::hide() {

}

void Window::setSizes(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void Window::setColor(int color) {
	this->color = color;
}
