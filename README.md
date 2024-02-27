# EchoOS
![Assembly Icon](https://img.shields.io/badge/x86-Assembly-green?style=for-the-badge&logo=assembly)

I'm trying to build my own Operating System and its kernel (Project still in progress). So far I implemented:
- The bootloader
- Global Descriptor Table (GDT), so I can switch to 32-bit Protected mode
- Simple LBA driver to read from disk in protected mode (Because we can't use __INT 0x13__ from BIOS anymore)
