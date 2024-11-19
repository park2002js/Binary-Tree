CC = gcc
CFLAGS = -Wall -g

#
main: main.o binary_tree.o huffman.o node.o queue.o stack.o
	$(CC) -o main main.o binary_tree.o huffman.o node.o queue.o stack.o

binary_tree.o: binary_tree.c
	$(CC) $(CFLAGS) -c binary_tree.c

huffman.o: huffman.c
	$(CC) $(CFLAGS) -c huffman.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

run : main
	./main
# "make run" 입력시 빌드 및 실행까지

clean:
	rm -f main main.exe *.o 
#-del main main.exe *.o 

