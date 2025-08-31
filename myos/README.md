# 🪐 JupiterOS

**A cosmic-scale 32-bit operating system built from scratch with passion and low-level programming magic!**

---

## 🌟 Features

### ✅ Currently Implemented
- **Multiboot-compliant bootloader** (GRUB compatible)
- **Protected mode kernel** written in C and NASM assembly
- **Advanced text-based UI** with scrolling and cursor support
- **Full keyboard driver** with scancode translation and shift support
- **RAM-based file system** (create, read, delete, list files)
- **Memory management** with simulated allocator
- **Process management** with basic scheduler framework
- **Interactive shell** with command history and auto-complete
- **System timer** with uptime tracking and sleep functions
- **Interrupt infrastructure** (IDT, PIC, ISRs ready for enablement)

### 🚧 In Development
- **Preemptive multitasking** with process switching
- **Hardware interrupt handling** (timer, keyboard)
- **Persistent storage** (FAT12 filesystem)
- **System calls** and user mode programs
- **Graphical mode** with basic GUI

---

## 🛠️ Technical Stack

- **Bootloader:** NASM assembly with Multiboot spec
- **Kernel:** C99 with GCC cross-compiler
- **Assembly:** NASM for low-level routines
- **Emulator:** QEMU for testing
- **Build System:** GNU Make

---

## 📦 Project Structure
