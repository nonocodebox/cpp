FLAGS = -Wall -g

all: ex1

ex1: MyLinkedList.o MyHashMap.o HashMapBinaryOperations.o
	g++ $(FLAGS) MyLinkedList.o MyHashMap.o HashMapBinaryOperations.o -o ex1

HashMapBinaryOperations.o:
	g++ $(FLAGS) -c HashMapBinaryOperations.cpp

MyLinkedList.o: MyLinkedList.cpp MyLinkedList.h
	g++ $(FLAGS) -c MyLinkedList.cpp

MyHashMap.o: MyHashMap.cpp MyHashMap.h
	g++ $(FLAGS) -c MyHashMap.cpp
	
clean:
	rm -f *.o ex1 test_hash_simple test_hash_example test_list_example
	
clean_tar:
	rm -f ex1.tar

# ==== Tests ====
	
ListExample.o:
	g++ $(FLAGS) -c ListExample.cpp
	
HashSimpleCheck.o:
	g++ $(FLAGS) -c HashSimpleCheck.cpp
	
TestHashMapBinFuncs.o:
	g++ $(FLAGS) -c TestHashMapBinFuncs.cpp

test_list_example: MyLinkedList.o ListExample.o ListExample.o
	g++ $(FLAGS) MyLinkedList.o ListExample.o -o test_list_example
	
test_hash_simple: MyLinkedList.o MyHashMap.o HashSimpleCheck.o
	g++ $(FLAGS) MyLinkedList.o MyHashMap.o HashSimpleCheck.o -o test_hash_simple

test_hash_example: MyLinkedList.o MyHashMap.o TestHashMapBinFuncs.o
	g++ $(FLAGS) MyLinkedList.o MyHashMap.o TestHashMapBinFuncs.o -o test_hash_example
	

tests: test_list_example test_hash_simple test_hash_example

	
# ==== tar ====
tar: ex1.tar

ex1.tar: HashMapBinaryOperations.cpp MyLinkedList.cpp MyLinkedList.h MyHashMap.cpp MyHashMap.h Makefile
	tar cvf ex1.tar HashMapBinaryOperations.cpp MyLinkedList.cpp MyLinkedList.h MyHashMap.cpp MyHashMap.h Makefile
	
.PHONY: all clean tar tests clean_tar
