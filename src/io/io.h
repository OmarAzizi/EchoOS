#ifndef __IO_H__
#define __IO_H__

/*
    implementing functions that does a similar job as the
    IN & OUT instructions in x86 assembly (reading/writing to a specific port)
*/
unsigned char insb(unsigned short port);  // reading 1 byte from the port
unsigned short insw(unsigned short port); // reading 2 bytes from the port

void outb(unsigned short port, unsigned char val);  // for outputin 1 byte to the port
void outw(unsigned short port, unsigned short val); // for outputing 2 bytes to the port

#endif
