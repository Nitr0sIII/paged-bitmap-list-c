all: unrolledLinkedList.o listManagement.o
	gcc -o unrolledLinkedList unrolledLinkedList.o listManagement.o
	clear
	./unrolledLinkedList

unrolledLinkedList.o: unrolledLinkedList.c
	gcc -c unrolledLinkedList.c

listManagement.o: ./src/listManagement.c
	gcc -c ./src/listManagement.c

clear:
	rm ./*.o unrolledLinkedList
	clear