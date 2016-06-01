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

void printMap(MultiMap<std::string, std::string> & md) {
	auto keys = md.keySet();
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
	MultiMap<std::string, std::string> md;
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

	for (const auto pair : md) {
		std::cout << pair << std::endl;
	}
	std::cout << "---------------------\n";
	printMap(md);
	md.removeAll("red");
	md.removeAll("cry");
	md.remove("blood", "neam");
	std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
	printMap(md);

	MultiMap<char*, int> d;
	d.add("cheia 1", 1);
	d.add("cheia 2", 2);
	d.add("cheia 3", 3);
	d.add("cheia 1", 4);
	for (auto e : d.entries()) {
		std::cout << e << "\n";
	}
	std::cout << "---------------\n"; return;
	MultiMap<double, char*> dc;
	dc.add(1.23, "am adaugat 1.23");
	dc.add(3.66, "am adaugat 3.66");
	dc.add(1, "numai 1");
	dc.add(1.230, "alta valoare pentru 1.23");
	std::cout << "size " << dc.size() << "\n";
	dc.removeAll(1.23);
	dc.removeAll(3.66);
	std::cout << "size " << dc.size() << "\n";
	auto keyset = dc.keySet();
	for (auto key : keyset) {
		std::cout << key << " = \n";
		for (auto val : dc[key])
			std::cout <<"      "<< val << "\n";
	}
}

int main() {
	//testVector();
	testMultiMap();
	std::getchar();
	_CrtDumpMemoryLeaks();
	return 0;
}