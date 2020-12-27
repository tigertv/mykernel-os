.PHONY: all clean run

KERNEL_NAME = mykernel

AS = as
ASPARAMS = --32

INC_DIR = include
CXX = g++
CXXPARAMS = -m32 -ffreestanding -fno-exceptions -fno-rtti -nostdlib -I$(INC_DIR)
#CXXPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -I$(INC_DIR)
LDPARAMS = -melf_i386

BUILD_DIR = build
ISO_DIR = $(BUILD_DIR)/iso
ISO_BOOT = $(ISO_DIR)/boot
GRUB_CONFIG = $(ISO_BOOT)/grub/grub.cfg
KERNEL = $(ISO_BOOT)/$(KERNEL_NAME).bin

SRC_DIR = src
SRC = $(shell find $(SRC_DIR) -type f -name '*.cpp') $(wildcard $(SRC_DIR)/*.s)
OBJS = $(SRC:=.o)
OBJS := $(addprefix $(BUILD_DIR)/, $(OBJS))
.SECONDARY: $(OBJS)
OBJS_DIRS = $(sort $(dir $(OBJS)))

all: $(KERNEL_NAME).iso

run: $(KERNEL_NAME).iso
	qemu-system-i386 -cdrom $<

$(KERNEL_NAME).iso: $(GRUB_CONFIG) $(KERNEL) 
	grub-mkrescue -o $@ $(ISO_DIR)

$(KERNEL): $(SRC_DIR)/linker.ld $(OBJS) | $(OBJS_DIRS)
	ld $(LDPARAMS) -T$< $(OBJS) -o $@

$(GRUB_CONFIG):
	mkdir -p $(@D)
	echo 'set timeout=0'                           > $(GRUB_CONFIG)
	echo 'set default=0'                           >> $(GRUB_CONFIG)
	echo ''                                        >> $(GRUB_CONFIG)
	echo 'menuentry "$(KERNEL_NAME) OS" {'         >> $(GRUB_CONFIG)
	echo '	multiboot2 /boot/$(KERNEL_NAME).bin'   >> $(GRUB_CONFIG)
	echo '	boot'                                  >> $(GRUB_CONFIG)
	echo '}'                                       >> $(GRUB_CONFIG)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(CXX) $(CXXPARAMS) $< -c -o $@

$(BUILD_DIR)/%.s.o: %.s
	$(AS) $(ASPARAMS) $< -o $@

$(OBJS_DIRS):
	mkdir -p $@

clean:
	rm -rf $(KERNEL_NAME).iso $(BUILD_DIR)
