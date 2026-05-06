# ============================================================
# Makefile
# ============================================================

# ------------------------------------------------------------
# Project configuration
# ------------------------------------------------------------

TARGET      = untitled
MCU         = cortex-m4
FPU         = fpv4-sp-d16
FLOAT_ABI   = hard

OPENOCD = C:/Dev/_tools/msys64/mingw64/bin/openocd.exe
OPENOCD_SCRIPTS = C:/Dev/_tools/msys64/mingw64/share/openocd/scripts

# ------------------------------------------------------------
# Toolchain
# ------------------------------------------------------------

CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

# ------------------------------------------------------------
# Build output directory
# ------------------------------------------------------------

OUT_DIR = out

# ------------------------------------------------------------
# Compiler flags
# ------------------------------------------------------------

CFLAGS  = -mcpu=$(MCU) -mthumb -mfpu=$(FPU) -mfloat-abi=$(FLOAT_ABI)
CFLAGS += -ffreestanding -fno-builtin -Wall -Wextra
CFLAGS += -g3 -Og

# ------------------------------------------------------------
# Linker flags
# ------------------------------------------------------------

LDFLAGS = -T linker.ld -Wl,--gc-sections -nostdlib

# ------------------------------------------------------------
# Source files
# ------------------------------------------------------------

SRCS = \
src/main.c \
src/gpio_driver.c \
src/i2c_driver.c \
src/usart_driver.c \
src/logger.c \
startup.s

# Convert source files to object files in OUT_DIR
OBJS = $(SRCS:%.c=$(OUT_DIR)/%.o)
OBJS := $(OBJS:%.s=$(OUT_DIR)/%.o)

# ------------------------------------------------------------
# Default build target
# ------------------------------------------------------------

all: $(OUT_DIR) $(OUT_DIR)/$(TARGET).elf $(OUT_DIR)/$(TARGET).bin size

# ------------------------------------------------------------
# Compile rules
# ------------------------------------------------------------

$(OUT_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%.o: %.s
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# ------------------------------------------------------------
# Link ELF
# ------------------------------------------------------------

$(OUT_DIR)/$(TARGET).elf: $(OBJS) linker.ld
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -lgcc -o $@

# ------------------------------------------------------------
# Convert ELF -> raw binary
# ------------------------------------------------------------

$(OUT_DIR)/$(TARGET).bin: $(OUT_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# ------------------------------------------------------------
# Size information
# ------------------------------------------------------------

size: $(OUT_DIR)/$(TARGET).elf
	$(SIZE) $<

# ------------------------------------------------------------
# Flash to target
# ------------------------------------------------------------

flash: $(OUT_DIR)/$(TARGET).elf
	"$(OPENOCD)" -s "$(OPENOCD_SCRIPTS)" -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program $< verify reset exit"

# ------------------------------------------------------------
# Start OpenOCD for debugging
# ------------------------------------------------------------

debug:
	"$(OPENOCD)" -s "$(OPENOCD_SCRIPTS)" -f interface/stlink.cfg -f target/stm32f4x.cfg


# ------------------------------------------------------------
# Utility targets
# ------------------------------------------------------------

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -rf $(OUT_DIR)

.PHONY: all size flash debug clean
