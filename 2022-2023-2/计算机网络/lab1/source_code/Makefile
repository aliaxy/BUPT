CC = gcc
CFLAGS = -O2

test : test.o protocol.o lprintf.o crc32.o
	gcc test.o protocol.o lprintf.o crc32.o -o datalink -lm

datalink : datalink.o protocol.o lprintf.o crc32.o
	gcc datalink.o protocol.o lprintf.o crc32.o -o datalink -lm

sr : sr.o protocol.o lprintf.o crc32.o
	gcc sr.o protocol.o lprintf.o crc32.o -o datalink -lm

gbn : gbn.o protocol.o lprintf.o crc32.o
	gcc gbn.o protocol.o lprintf.o crc32.o -o datalink -lm

.PHONY : clean

clean :
	${RM} *.o datalink *.log
