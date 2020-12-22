#include <myos/VideoContext.h>
#include <myos/TextCursor.h>
#include <myos/Keyboard.h>
#include <myos/GDTable.h>
#include <myos/VGArray.h>
#include <myos/gui/Window.h>


typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
	for(constructor* i = &start_ctors; i != &end_ctors; i++)
		(*i)();
}

extern "C" void myprint() {
	VideoContext b(Color::Gray, Color::Green);
	b.goAt(50, 0);
	b.print("PRINT MYPRINT");
}

/*
Multiboot specification 2.0

When the boot loader invokes the 32-bit operating system, the machine must have the following state:

‘EAX’
Must contain the magic value ‘0x36d76289’(‘0x2BADB002’ for version 1); the presence of this value indicates to the operating system that it was loaded by a Multiboot2-compliant boot loader (e.g. as opposed to another type of boot loader that the operating system can also be loaded from).

‘EBX’
Must contain the 32-bit physical address of the Multiboot2 information structure provided by the boot loader (see Boot information format).

‘CS’
Must be a 32-bit read/execute code segment with an offset of ‘0’ and a limit of ‘0xFFFFFFFF’. The exact value is undefined.

‘DS’
‘ES’
‘FS’
‘GS’
‘SS’
Must be a 32-bit read/write data segment with an offset of ‘0’ and a limit of ‘0xFFFFFFFF’. The exact values are all undefined.

‘A20 gate’
Must be enabled.

‘CR0’
Bit 31 (PG) must be cleared. Bit 0 (PE) must be set. Other bits are all undefined.

‘EFLAGS’
Bit 17 (VM) must be cleared. Bit 9 (IF) must be cleared. Other bits are all undefined.

All other processor registers and flag bits are undefined. This includes, in particular:

‘ESP’
The OS image must create its own stack as soon as it needs one.

‘GDTR’
Even though the segment registers are set up as described above, the ‘GDTR’ may be invalid, so the OS image must not load any segment registers (even just reloading the same values!) until it sets up its own ‘GDT’.

‘IDTR’
The OS image must leave interrupts disabled until it sets up its own IDT.

On EFI system boot services must be terminated.

//*/

extern "C" void kernelMain(const void* multiboot_structure, unsigned int magicNumber) {
	//GDTable table;
	//table.load();

	VGArray vga;
	vga.setMode();

	DrawContext dc(vga);
	Window win1(dc);
	win1.setSizes(0, 0, 50, 20);
	win1.setColor(1);
	win1.moveAtXY(50, 20);
	win1.show();

	Window win2(dc);
	win2.setSizes(100, 100, 40, 30);
	win2.setColor(2);
	win2.show();

	dc.setColor(3);
	dc.drawLine(0, 0, 40, 180);
	dc.setColor(5);
	for(int i = 40; i > 10; --i) {
		dc.drawCircle(200, 100, i);
	}	

/*
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
	//*/



	//b.print("\tAfter SetMode");

	/*
	Keyboard k;
	uint8_t key = 37;
	
	while(true) {
		key = k.getKey();
		if (key != 0) break;
	}
	a.nextLine();
	//a.printHex((int)key);
	key = k.readStatus();
	//b.printHex(key);
	b.nextLine();
	for (uint32_t i = 0x0; i < 0x10; ++i) {
		uint32_t* p = (uint32_t*)(i << 2);
		b.printHex(i << 2);
		b.printChar('=');
		b.printHex(*p);
		b.printChar(' ');
	}
	uint32_t *p = (uint32_t*)(0x4);
	*p = (uint32_t)&myprint;
	b.printChar('&');
	b.printChar('=');
	b.printHex(*p);
	b.printChar(';');
	b.printChar(';');
	//((void(*)())p)();


	for (uint32_t i = 0x0; i < 0x10; ++i) {
		uint32_t* p = (uint32_t*)(i << 2);
		b.printHex(i << 2);
		b.printChar('=');
		b.printHex(*p);
		b.printChar(' ');
	}

	b.nextLine();
	b.nextLine();
	uint32_t s = (uint32_t)&kernelMain;
	b.printHex(s);

	b.goAt(50, 0);
	b.print("WHILE");

	while(1) {
		b.goAt(57, 0);
		key = k.getKey();
		b.printHex(key);
	}
	//*/
	while(1) {

	}

}
