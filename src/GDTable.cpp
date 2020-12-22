#include <myos/GDTable.h>


SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type) {
	uint8_t* target = (uint8_t*)this;
	limitLow = 0;
	baseLow = 0;
	baseMiddle = 0;
	this->type = type;
	limitHigh = 0;
	baseHigh = 0;
}

GDTable::GDTable() 
	: nullDescr(0, 0, 0), codeDescr(0, 64*1024*1024, 0x9a),
	  dataDescr(0, 64*1024*1024, 0x92), tssDescr(0, 0, 0) {
}

void GDTable::load() {
	uint32_t i[2];
    i[0] = sizeof(GDTable) << 16;
    i[1] = (uint32_t)this;
    asm volatile("lgdt (%0)": :"p" (((uint8_t *) i) + 2));
    //asm volatile("lgdt (%0)": :"p"(i) );
    //asm volatile("lgdt %0": :"m" (((uint8_t *) i) + 2));
    //asm volatile("lgdt %0": :"m" (i));
}
