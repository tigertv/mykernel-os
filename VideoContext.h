#ifndef VIDEO_CONTEXT_H
#define VIDEO_CONTEXT_H

enum Color {
	Black = 0, Blue, Green, Cyan,
	Red, Purple, Brown, Gray,
	DarkGray, LightBlue, LightGreen, LightCyan,
	LightRed, LightPurple, Yellow, White
};

class VideoContext {
private:
	static unsigned short* videoBegin;
	static const int TAB_SIZE = 4;
	unsigned short* cursor;
	unsigned int width;
	unsigned int height;
	unsigned short colors;
	
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
