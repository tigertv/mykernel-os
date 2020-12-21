#include "VideoContext.h"

unsigned short* VideoContext::videoBegin = (unsigned short*)0xb8000;

VideoContext::VideoContext(Color background, Color foreground) {
	cursor = videoBegin;
	width = 80;
	height = 25;
	setColors(background, foreground);
}

VideoContext::VideoContext() : VideoContext(Color::Black, Color::Cyan) {

}

void VideoContext::setColors(Color background, Color foreground) {
	colors = (background << 4 | foreground) << 8;
}

void VideoContext::print(const char *str) {
	for (char *c = (char*)str ; *c != '\0'; ++c) {
		switch(*c) {
		case '\n': 
			nextLine();
			break;
		case '\t': 
			for(int i = 0; i < TAB_SIZE; ++i) {
				printChar(' ');
			}
			break;
		default:
			printChar(*c);
		}
	}
}

void VideoContext::printChar(char c) {
	*cursor++ = colors | c;
}

void VideoContext::nextLine() {
	cursor += width - (cursor - videoBegin) % width;
}

void VideoContext::goAt(int x, int y) {
	cursor = videoBegin + y * width + x;	
}
