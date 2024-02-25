all:
	nasm -f bin boot.asm -o boot.bin

run:
	qemu-system-x86_64 -hda boot.bin

clean:
	rm -rf boot.bin
