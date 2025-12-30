ASM	= nasm
CC	= gcc
LD	= ld

LD_FLAGS	= -m elf_i386 -Map kernel.map --no-warn-rwx-segments
ASM_FLAGS	= -f elf32
CC_FLAGS	= -m32 -ffreestanding

BUILD_DIR	= build
SOURCE_DIR	= src
BUILD_INNER	= $(patsubst $(SOURCE_DIR)/%, $(BUILD_DIR)/%, $(shell find $(SOURCE_DIR)/* -type d))


ASM_SOURCES	= $(shell find $(SOURCE_DIR) -name '*.s')
CC_SOURCES	= $(shell find $(SOURCE_DIR) -name '*.c')

ASM_OBJECTS	= $(patsubst $(SOURCE_DIR)/%, $(BUILD_DIR)/%.o, $(ASM_SOURCES))
CC_OBJECTS	= $(patsubst $(SOURCE_DIR)/%, $(BUILD_DIR)/%.o, $(CC_SOURCES))
OBJECTS		= $(ASM_OBJECTS) $(CC_OBJECTS)

GRUB_CFG_FILE	= $(SOURCE_DIR)/grub.cfg
LINK_FILE	= $(SOURCE_DIR)/link.ld
IMAGE		= $(BUILD_DIR)/kernel.elf


.PHONY: all makedirs clean run build link install update
all: clean build link run

run: link
	qemu-system-i386 -kernel $(IMAGE) -no-reboot -vga std -full-screen $(QEMU_FLAGS)

link: build
	@echo "--- Linking ---"
	$(LD) $(LD_FLAGS) -T $(LINK_FILE) -o $(IMAGE) $(OBJECTS)

	@cp $(GRUB_CFG_FILE) $(BUILD_DIR)

	@rm -rf $(BUILD_INNER) kernel.map

build: makedirs $(BUILD_INNER) $(OBJECTS)

%.s.o: $(ASM_SOURCES)
	@echo "--- Compiling $@ ---"
	$(ASM) $(ASM_FLAGS) -o $@ $(patsubst $(BUILD_DIR)/%.o, $(SOURCE_DIR)/%,$@)
	# $(patsubst %, -I%, $(BUILD_INNER))

%.c.o: $(CC_SOURCES)
	@echo "--- Compiling $@ ---"
	$(CC) $(CC_FLAGS) -o $@ -c $(patsubst $(BUILD_DIR)/%.o, $(SOURCE_DIR)/%,$@) $(patsubst %, -I%, $(BUILD_INNER))

$(IMAGE): link

clean:
	@rm -rf $(BUILD_DIR) kernel.map

makedirs:
	@echo "--- Directories $(BUILD_INNER) ---"
	@mkdir -p $(BUILD_DIR) $(BUILD_INNER)

install: link
	@parted -s $(DISK_TO_INSTALL) mklabel msdos
	@parted -s $(DISK_TO_INSTALL) mkpart primary fat32 0% 100%
	@parted -s $(DISK_TO_INSTALL) set 1 boot on
	@mkfs.fat -F 32 $(DISK_TO_INSTALL)1
	@mount $(DISK_TO_INSTALL)1 /mnt/usb
	@mkdir /mnt/usb/boot
	@grub-install --target=i386-pc --boot-directory=/mnt/usb/boot $(DISK_TO_INSTALL)
	@cp $(IMAGE) /mnt/usb/boot/
	@cp $(GRUB_CFG_FILE) /mnt/usb/boot/grub/
	@umount /mnt/usb

update: link
	@mount $(DISK_TO_INSTALL)1 /mnt/usb
	@cp $(IMAGE) /mnt/usb/boot/
	@cp $(GRUB_CFG_FILE) /mnt/usb/boot/grub/
	@umount /mnt/usb

