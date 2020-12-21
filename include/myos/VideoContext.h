#ifndef VIDEO_CONTEXT_H
#define VIDEO_CONTEXT_H

#include "types.h"

enum Color {
	Black = 0, Blue, Green, Cyan,
	Red, Purple, Brown, Gray,
	DarkGray, LightBlue, LightGreen, LightCyan,
	LightRed, LightPurple, Yellow, White
};

class VideoContext {
private:
	static uint16_t* videoBegin;
	static const int TAB_SIZE = 4;
	uint16_t *cursor;
	uint16_t width;
	uint16_t height;
	uint16_t colors;
	
public:
	VideoContext();
	VideoContext(Color background, Color foreground);
	void print(const char* str);
	void printChar(char c);
	void setColors(Color background, Color foreground);
	void nextLine();
	void goAt(int x, int y);
};

#endif
