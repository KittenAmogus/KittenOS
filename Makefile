# TOOLS
CC = gcc

# FLAGS
CFLAGS = -m32 -std=gnu11 -ffreestanding -nostdlib -fno-builtin -Wall -Wextra -O0 -fno-pie -isystem include
LDFLAGS = -m32 -nostdlib -no-pie

# SOURCES AND OBJECTS
CSOURCES = $(shell find src -name '*.c')
SSOURCES = $(shell find src -name '*.S')
OBJECTS = $(patsubst src/%,build/%.o,$(CSOURCES) $(SSOURCES))

# FILES
TARGET = kernel
LINKER = linker.ld

EMULATOR_MEM = 32

# RULES
.PHONY: all clean qemu

all: $(TARGET).elf

$(TARGET).elf: $(OBJECTS)
	@echo ">> Linking $@ <- ($^)"
	$(CC) $(LDFLAGS) -T $(LINKER) -o $@ $^

build/%.o: src/%
	@mkdir -p $(dir $@)
	@echo ">> Compiling $@ <- $<"
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@echo ">> Cleaning up"
	@rm -rf build

# RUN COMMANDS
qemu: $(TARGET).elf
	@echo ">> Running with qemu (RAM $(EMULATOR_MEM)M)"
	# # Uncomment to add HDD A
	# @echo "-> Creating HDD A size 128M"
	# qemu-img create -f raw hda.img 128M
	# # Uncomment to add HDD B
	# @echo "-> Creating HDD B size 128M"
	# qemu-img create -f raw hdb.img 128M
	qemu-system-i386 -kernel $< -m $(EMULATOR_MEM) -serial stdio -name "qemu_KittenOS" \
		# -drive file=hda.img,format=raw,index=0,media=disk \
		# -drive file=hdb.img,forhat=raw,index=1,media=disk \

