all:
	nasm -f bin ./src/boot/boot.asm -o ./bin/boot.bin

run:
	qemu-system-x86_64 -hda ./bin/boot.bin

clean:
	rm -rf ./bin/boot.bin
