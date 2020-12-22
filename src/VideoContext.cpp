#include <myos/VideoContext.h>


uint16_t* VideoContext::videoBegin = (uint16_t*)0xb8000;

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

void VideoContext::printInt(int num) {
	if (num < 0) {
		printChar('-');
		num = -num;
	}

	int i = 0;
	char ch[64] = {0};

	int q;
	do {
		q = num / 10;
		ch[i] = '0' + num % 10;
		num = q;
		++i;
	} while (q != 0);

	--i;

	for(; i >= 0; --i) {
		printChar(ch[i]);
	}

}

void VideoContext::printHex(uint32_t num) {
	char ch[64] = {0};
	char alphabet[] = "0123456789abcdef";

	uint32_t q;
	int i = 0;
	do {
		q = num / 16;
		ch[i] = alphabet[num % 16];
		num = q;
		++i;
	} while (q != 0);

	--i;
	print("0x");

	for(; i >= 0; --i) {
		printChar(ch[i]);
	}
}
