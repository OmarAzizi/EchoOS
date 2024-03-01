# EchoOS
![Assembly Icon](https://img.shields.io/badge/x86-Assembly-green?style=for-the-badge&logo=assembly)

I'm trying to build my own Operating System and its kernel (Project still in progress). So far I implemented:
- The bootloader
- Global Descriptor Table (GDT), so I can switch to 32-bit Protected mode
- Simple LBA driver to read from disk in protected mode (Because we can't use __INT 0x13__ from BIOS anymore)
- VGA 16-color text mode 
- Interrupt Descriptor Table (IDT)
- Simple memset function

## Demo
This demo shows the output in qemu after I devided by zero in to trigger the interrupt 0 in IDT

![image](https://github.com/OmarAzizi/EchoOS/assets/110500643/bea5a44c-fa8d-4538-b1b9-4dd36e24034c)

