#include "VideoContext.h"
#include "TextCursor.h"


typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
	for(constructor* i = &start_ctors; i != &end_ctors; i++)
		(*i)();
}

extern "C" void kernelMain(const void* multiboot_structure, unsigned int magicNumber) {
	VideoContext a;
	a.print("Hello World!!!\n");
	a.print("We are creating an OS!\n");
	a.nextLine();

	VideoContext b(Color::Gray, Color::Red);
	b.goAt(50, 2);
	b.print("Print at");

	a.print("LINE---------------------\n");
	a.print("NEXT_LINE---------------------");

	b.print("\tPrint at");

	TextCursor t;
	t.enable(15, 15);
	t.move(0, 10);

	while(1);
}
