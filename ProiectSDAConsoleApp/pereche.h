#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <string>

typedef std::string TCheie;
typedef std::string TValoare;

class Pereche {
private:
	TCheie __key;
	TValoare __value;
public:
	static const TValoare INVALID_VALUE;
	/**
	*	The default constructor
	*/
	Pereche() : __key{ INVALID_VALUE }, __value{ INVALID_VALUE } {}

	/**
	*	The explicit constructor
	*/
	Pereche(const TCheie &key, const TValoare &value) {
		this->__key = key;
		this->__value = value;
	}

	TCheie getKey() const {
		return this->__key;
	}

	bool valid() {
		return (this->__key != INVALID_VALUE && this->__value != INVALID_VALUE);
	}

	TValoare getValue() const {
		return this->__value;
	}

	TValoare& getValueRef() {
		return this->__value;
	}

	/*

	*/
	int hashCode() const {
		if (this->__key.empty()) {
			return 0;
		}
		return (int)this->__key[0];
	}

	Pereche& operator=(const Pereche& other) {
		this->__key = other.__key;
		this->__value = other.__value;
		return *this;
	}

	void makeInvalid() {
		this->__value = INVALID_VALUE;
		this->__key = INVALID_VALUE;
	}

	bool operator<(const Pereche &other) const {
		return this->__key < other.__key;
	}

	bool operator<=(const Pereche &other) const {
		return this->__key <= other.__key;
	}

	bool operator>(const Pereche &other) const {
		return this->__key > other.__key;
	}

	bool operator>=(const Pereche &other) const {
		return this->__key >= other.__key;
	}

	bool operator==(const Pereche &other) const {
		return this->__key == other.__key;
	}

	bool operator!=(const Pereche &other) const {
		return this->__key != other.__key;
	}

	friend std::ostream &operator<<(std::ostream& out, const Pereche& pair) {
		return out << pair.__key << " = " << pair.__value;
	}
};