/*
 * HashMapBinaryOperations.cpp
 *
 * This file contains examples of usage of hash map operators:
 * &, |, -, >, <, ==.
 *
 *  Created on: Aug 25, 2014
 */

#include "MyHashMap.h"
#include <iostream>

#define EXIT_SUCCESS 0

/**
 * Main function contains examples of usage of hash map operators.
 */
int main()
{
	MyHashMap hashMap1, hashMap2;
	MyHashMap minusOp, unionOp, interOp;

	hashMap1.add("a", 2);
	hashMap1.add("b", 3);
	hashMap1.add("c", 4);
	hashMap1.add("d", 5);
	hashMap1.add("e", 6);
	hashMap1.add("f", 7);


	hashMap2.add("a", 8);
	hashMap2.add("b", 9);
	hashMap2.add("i", 10);
	hashMap2.add("j", 11);
	hashMap2.add("e", 12);
	hashMap2.add("k", 13);

	minusOp = hashMap1 - hashMap2;
	unionOp = hashMap1 | hashMap2;
	interOp = hashMap1 & hashMap2;

	if (hashMap1 > hashMap2)
	{
		std::cout << "hashMap1 is bigger" << std::endl;
	}

	else if (hashMap2 > hashMap1)
	{
		std::cout << "hashMap1 is smaller" << std::endl;
	}

	if (hashMap2 == hashMap1)
	{
		std::cout << "equals" << std::endl;
	}

	return EXIT_SUCCESS;
}
