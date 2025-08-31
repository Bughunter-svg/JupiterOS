ASM = nasm
CC = gcc
LD = ld

# Fixed CFLAGS - removed conflicting options
CFLAGS = -m32 -ffreestanding -nostdlib -fno-exceptions -fno-pic -Wall -Wextra -I.

# All object files
OBJS = boot/boot.o kernel/kernel.o kernel/screen.o kernel/ports.o kernel/keyboard.o \
       kernel/string.o kernel/filesystem.o kernel/process.o kernel/timer.o \
       kernel/interrupts.o kernel/isr.o kernel/splash.o kernel/system.o kernel/memory.o

all: kernel.bin

boot/boot.o: boot/boot.s
	$(ASM) -f elf32 $< -o $@

kernel/kernel.o: kernel/kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel/screen.o: kernel/screen.c kernel/screen.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/ports.o: kernel/ports.c kernel/ports.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/keyboard.o: kernel/keyboard.c kernel/keyboard.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/string.o: kernel/string.c kernel/string.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/filesystem.o: kernel/filesystem.c kernel/filesystem.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/process.o: kernel/process.c kernel/process.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/timer.o: kernel/timer.c kernel/timer.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/interrupts.o: kernel/interrupts.c kernel/interrupts.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/isr.o: kernel/isr.asm
	$(ASM) -f elf32 $< -o $@

kernel/splash.o: kernel/splash.c kernel/splash.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/system.o: kernel/system.c kernel/system.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/memory.o: kernel/memory.c kernel/memory.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel.bin: $(OBJS) linker.ld
	$(LD) -m elf_i386 -T linker.ld -o $@ $(OBJS) -nostdlib

iso: kernel.bin
	mkdir -p isodir/boot/grub
	cp kernel.bin isodir/boot/kernel.bin
	cp boot/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir

run: iso
	qemu-system-i386 -cdrom myos.iso

clean:
	rm -rf boot/*.o kernel/*.o kernel.bin isodir myos.iso

.PHONY: all clean run iso
