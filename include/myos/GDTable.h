#ifndef GLOBAL_DESCRIPTION_TABLE 
#define GLOBAL_DESCRIPTION_TABLE 

#include <myos/types.h>


class SegmentDescriptor {
	uint16_t limitLow;
	uint16_t baseLow;
	uint8_t baseMiddle;
	uint8_t type; // not fully
	uint8_t limitHigh; // not fully
	uint8_t baseHigh;
public:
	SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
} __attribute__((packed));


// Note: GDT may contain not only Segment descriptors but also TSS, LDT, Call Gates
class GDTable {
private:
	SegmentDescriptor nullDescr;
	SegmentDescriptor codeDescr;
	SegmentDescriptor dataDescr;
	SegmentDescriptor tssDescr;
public:
	GDTable();
	void load();
} __attribute__((packed));


#endif
