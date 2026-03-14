all: unrolledLinkedListNormal unrolledLinkedListDynamic

unrolledLinkedListNormal: unrolledLinkedListNormal.o listManagementNormal.o
	gcc -o unrolledLinkedListNormal unrolledLinkedListNormal.o listManagementNormal.o

unrolledLinkedListDynamic: unrolledLinkedListDynamic.o listManagementDynamic.o
	gcc -o unrolledLinkedListDynamic unrolledLinkedListDynamic.o listManagementDynamic.o

#########################################################################

unrolledLinkedListDynamic.o: unrolledLinkedListDynamic.c 
	gcc -c unrolledLinkedListDynamic.c

listManagementDynamic.o: ./src/listManagementDynamic.c
	gcc -c ./src/listManagementDynamic.c

#########################################################################

unrolledLinkedListNormal.o: unrolledLinkedListNormal.c 
	gcc -c unrolledLinkedListNormal.c

listManagementNormal.o: ./src/listManagementNormal.c
	gcc -c ./src/listManagementNormal.c

#########################################################################

clean:
	rm -f ./*.o unrolledLinkedListNormal unrolledLinkedListDynamic
	clear