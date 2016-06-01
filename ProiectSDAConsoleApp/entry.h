#ifndef PERECHE_H
#define PERECHE_H

#include <string>

template<typename TKey, typename TValue> class Entry {
private:
	TKey __key;
	TValue __value;
	bool __isValid;
public:
	/**
	*	The default constructor
	*/
	Entry() : __key{}, __value{}, __isValid{ false } {}

	/**
	*	The explicit constructor
	*/
	Entry(const TKey &key, const TValue &value) {
		this->__key = key;
		this->__value = value;
		this->__isValid = true;
	}

	TKey getKey() const {
		return this->__key;
	}

	bool isValid() {
		return this->__isValid;
	}

	TValue getValue() const {
		return this->__value;
	}

	int hashCode() const {
		int key_hash = std::hash<TKey>()(this->__key);
		return (int)key_hash;
	}

	Entry& operator=(const Entry& other) {
		this->__key = other.__key;
		this->__value = other.__value;
		this->__isValid = other.__isValid;
		return *this;
	}

	void makeInvalid() {
		this->__isValid = false;
	}

	bool operator<(const Entry &other) const {
		return this->__key < other.__key;
	}

	bool operator<=(const Entry &other) const {
		return this->__key <= other.__key;
	}

	bool operator>(const Entry &other) const {
		return this->__key > other.__key;
	}

	bool operator>=(const Entry &other) const {
		return this->__key >= other.__key;
	}

	bool operator==(const Entry &other) const {
		return this->__key == other.__key;
	}

	bool operator!=(const Entry &other) const {
		return this->__key != other.__key;
	}

	friend std::ostream &operator<<(std::ostream& out, const Entry& pair) {
		return out << pair.__key << " = " << pair.__value;
	}
};

#endif /* PERECHE_H */