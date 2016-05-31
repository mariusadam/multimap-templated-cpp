#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "vector.h"
#include "pereche.h"
#include <exception>

class MultiMapException : public std::exception {
public:
	MultiMapException() : std::exception() {}
	MultiMapException(const char* msg) : std::exception{ msg }{}
};

class IteratorMultiMap;

class MultiMap {
private:
	int __size;
	int __capacity;
	Pereche* __pairs;

	int __dispersion(const Pereche &pair, int i) {
		return (pair.hashCode() + i) % this->__capacity;
	}
	void __redispersion();
public:
	friend class IteratorMultiMap;
	static const int DEFAULT_CAPACITY;
	MultiMap();
	~MultiMap();
	void add(const TCheie &key, const TValoare &value);
	void deleteKey(const TCheie &key);
	bool keyExists(const TCheie &key);
	Vector<TCheie> keys();
	Vector<TValoare> values();
	Vector<TValoare> getValuesByKey(const TCheie key);
	bool empty();
	Vector<TValoare> operator[](const TCheie &key);
	const int capacity() const;
	const int size() const;
	IteratorMultiMap begin() const;
	IteratorMultiMap end();

};

class IteratorMultiMap {
private:
	const MultiMap &__multiMap;
	int __curent;

	void __ensureValidPosition() {
		while (this->__curent < this->__multiMap.capacity() && this->__multiMap.__pairs[this->__curent].valid() == false) {
			this->__curent++;
		}
	}
public:
	friend class MultiMap;
	IteratorMultiMap(const MultiMap& map) : __multiMap{ map } {
		this->__curent = 0;
		this->__ensureValidPosition();
	}
	IteratorMultiMap(const MultiMap& map, int poz) : __multiMap{ map }, __curent{ poz } {}
	bool valid() const {
		return this->__curent < this->__multiMap.capacity();
	}
	Pereche& element() const {
		return this->__multiMap.__pairs[this->__curent];
	}
	void next() {
		this->__curent++;
		this->__ensureValidPosition();
	}
	Pereche& operator*() const {
		return this->element();
	}
	IteratorMultiMap& operator++() {
		this->next();
		return *this;
	}
	bool operator==(const IteratorMultiMap& other) const {
		return this->__curent == other.__curent;
	}
	bool operator!=(const IteratorMultiMap& other) const {
		return !(*this == other);
	}
};