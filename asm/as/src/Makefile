all: write.o mmap.o socket.o daemon.o args.o

write.o:
	gcc -c write.s; \
	ld -s -o write write.o

mmap.o:
	gcc -c mmap.s; \
	ld -s -o mmap mmap.o

socket.o:
	gcc -c socket.s; \
	ld -s -o socket socket.o

daemon.o:
	gcc -c daemon.s; \
	ld -s -o daemon daemon.o

args.o:
	gcc -c args.s; \
	ld -s -o args args.o

clean:
	rm -f write mmap socket daemon args; \
	rm -f write.o mmap.o socket.o daemon.o args.o; \
	rm -f core

