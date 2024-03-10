# EchoOS
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![Assembly Icon](https://img.shields.io/badge/x86-Assembly-green?style=for-the-badge&logo=assembly)

I'm trying to build my own Operating System and its kernel (Project still in progress). So far I implemented:
- The bootloader
- Global Descriptor Table (GDT), so I can switch to 32-bit Protected mode
- Simple LBA driver to read from disk in protected mode (Because we can't use __INT 0x13__ from BIOS anymore)
- VGA 16-color text mode 
- Interrupt Descriptor Table (IDT)
- Simple memset function
- Remapped Master & Slave PICs

## Testing Interrupts
This screenshot shows the output in qemu after I devided by zero in to trigger the interrupt 0 in IDT
![image](https://github.com/OmarAzizi/EchoOS/assets/110500643/bea5a44c-fa8d-4538-b1b9-4dd36e24034c)


This screenshot shows the output after pressing a key on the keyboard (This is after remapping the PICs so the interrupt called here is 0x21)
![image](https://github.com/OmarAzizi/EchoOS/assets/110500643/3a9eef5d-fb3b-4b94-80e2-99bf8f2ffa7c)

## Clone & Run
Clone the repository
```bash
git clone https://github.com/OmarAzizi/EchoOS.git && cd EchoOS
```

Building the source and running it
```bash
./build.sh && make run
```

### Note
To build the code successfully, you need to set up:
1. [QEMU emulator](https://www.qemu.org/)
2. [GCC Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler)
3. A tree structure that looks like this (in the root of the project):

.
├── bin
├── build
│   ├── idt
│   ├── io
│   └── memory
│       ├── heap
│       └── paging

