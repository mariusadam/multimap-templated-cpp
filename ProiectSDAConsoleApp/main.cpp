#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "vector.h"
#include "multimap.h"
#include <string>

void testVector() {
	Vector<std::string> vec{ 1000 };
	vec.push_back("something");
	vec.push_back("sdf");
	vec.push_back("h6776j");
	vec.push_back("7j6tyjgfjfj");
	vec[2] = "333333333333333333";
	for (auto str : vec) {
		std::cout << str << std::endl;
	}
	try {
		vec[123];
	}
	catch (VectorException& ex) {
		std::cout << ex.what();
	}
}

void printMap(MultiMap & md) {
	auto keys = md.keys();
	for (const auto & key : keys) {
		std::cout << "---------------------\n";
		std::cout << key << " = :\n";
		for (const auto & value : md[key]) {
			std::cout << "      " << value << std::endl;
		}
		std::cout << "---------------------\n";
	}
}

void testMultiMap() {
	MultiMap md;
	md.add("red", "rosu");
	md.add("book", "carte");
	md.add("tail", "revers");
	md.add("blood", "sange");
	md.add("cry", "a plange");
	md.add("book", "a rezerva");
	md.add("blood", "neam");
	md.add("book", "publicatie");
	md.add("append", "a adauga");
	md.add("tail", "coada");
	md.add("cry", "strigat");
	md.add("append", "a atasa");
	md.add("cat", "pisica");
	md.add("red", "rosu");

	//for (const auto pair : md) {
	//	std::cout << pair << std::endl;
	//}
	//std::cout << "---------------------\n";
	printMap(md);
	md.deleteKey("cry");
	md.deleteKey("cat");
	md.deleteKey("book");
	md.deleteKey("append");
	md.deleteKey("tail");
		
	std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
	printMap(md);
}

int main() {
	//testVector();
	testMultiMap();
	std::getchar();
	_CrtDumpMemoryLeaks();
	return 0;
}