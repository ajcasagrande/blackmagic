CROSS_COMPILE ?= arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS += -Istm32/include -mcpu=cortex-m4 -mthumb \
	-mfloat-abi=hard -mfpu=fpv4-sp-d16 \
	-DSTM32F4 -I../libopencm3/include \
	-Iplatforms/stm32 -DDFU_SERIAL_LENGTH=9

LDFLAGS = -lopencm3_stm32f4 \
	-Wl,-T,platforms/stm32/f4discovery.ld -nostartfiles -lc -lnosys \
	-Wl,-Map=mapfile -mthumb -mcpu=cortex-m4 -Wl,-gc-sections \
	-mfloat-abi=hard -mfpu=fpv4-sp-d16 \
	-L../libopencm3/lib

VPATH += platforms/stm32

SRC += 	cdcacm.c	\
	traceswodecode.c	\
	traceswo.c	\
	usbuart.c	\
	serialno.c	\
	timing.c	\
	timing_stm32.c	\

all: blackmagic.bin blackmagic.hex

blackmagic.dfu: blackmagic.hex
	@echo Creating $@
	@python3 ../scripts/dfu-convert.py -i $< $@

host_clean:
	-$(Q)$(RM) blackmagic.bin blackmagic.hex blackmagic.dfu
