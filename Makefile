.PHONY: all clean run

KERNEL_NAME = mykernel
AS = as
ASPARAMS = --32
CXX = g++
CXXPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
LDPARAMS = -melf_i386
ISO_DIR = isofiles
ISO_BOOT = $(ISO_DIR)/boot
GRUB_CONFIG = $(ISO_BOOT)/grub/grub.cfg

SRC := $(wildcard *.cpp)
SRC +=  $(wildcard *.s)
OBJS = $(SRC:=.o)

all: $(KERNEL_NAME).iso

run: $(KERNEL_NAME).iso
	qemu-system-i386 $<

%.cpp.o : %.cpp
	$(CXX) $(CXXPARAMS) $< -c -o $@
%.s.o : %.s
	$(AS) $(ASPARAMS) $< -o $@
%.bin: linker.ld $(OBJS) 
	ld $(LDPARAMS) -T $< -o $@ $(OBJS)
%.iso: %.bin
	cp $< $(ISO_BOOT)/
	echo 'set timeout=10'                           > $(GRUB_CONFIG)
	echo 'set default=0'                           >> $(GRUB_CONFIG)
	echo ''                                        >> $(GRUB_CONFIG)
	echo 'menuentry "$(KERNEL_NAME) OS" {'         >> $(GRUB_CONFIG)
	echo '	multiboot2 /boot/$(KERNEL_NAME).bin'    >> $(GRUB_CONFIG)
	echo '	boot'                                  >> $(GRUB_CONFIG)
	echo '}'                                       >> $(GRUB_CONFIG)
	grub-mkrescue -o $@ $(ISO_DIR)
	
clean:
	rm -f *.bin *.iso *.o $(ISO_BOOT)/*.bin
