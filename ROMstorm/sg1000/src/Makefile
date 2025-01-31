CC=i686-w64-mingw32-gcc -O2 -fexec-charset=cp932 -Wall
#CC=x86_64-w64-mingw32-gcc -O2 -fexec-charset=cp932 -Wall

.SUFFIXES: .asm .rom

all: sg1000

sg1000: sg1000.c loader.h SG1000.DAT.h
	$(CC) -o $@ $<
	strip $@

.asm.rom:
	zasm --z80 -l0 -i $< -o $@

.rom.h:
	xxd -i $< | sed "s/unsigned char/const uint8_t/;s/SG1000_DAT_rom/SG1000_DAT/;/unsigned int/d" > $@

clean:
	$(RM) sg1000 loader.h loader.rom SG1000.DAT.h SG1000.DAT.rom
