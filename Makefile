CROSS = arm-none-eabi-
CC = $(CROSS)gcc
AS = $(CROSS)as
LD = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy

ASFLAGS = -g -gstabs -mcpu=cortex-m3 -mthumb -mapcs-32
CFLAGS = -Wall -g -Og -mthumb -ffreestanding -nostdinc
LDFLAGS = -g -nostdlib

bin = blink.bin
elf = blink.elf

objs = start.o blink.o stm32.o

default: $(bin)

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(elf): stm32.ld $(objs)
	$(LD) $(LDFLAGS) -T stm32.ld -o $@ $(objs)

$(bin): $(elf)
	$(OBJCOPY) -O binary $< $@

.PHONY: clean

clean:
	rm -f *.o *.elf *.bin

.PRECIOUS: %.elf
