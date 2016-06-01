#ifndef MULTIMAP_H
#define MULTIMAP_H

#include "vector.h"
#include "entry.h"
#include <exception>

class MultiMapException : public std::exception {
public:
	MultiMapException() : std::exception() {}
	MultiMapException(const char* msg) : std::exception{ msg }{}
};

template<typename TKey, typename TValue>class IteratorMultiMap;

template<typename TKey, typename TValue>class MultiMap {
private:
	int __size;
	int __capacity;
	Entry<TKey, TValue>* __entries;

	int __dispersion(const Entry<TKey, TValue> &entry, int i) {
		return (entry.hashCode() + i) % this->__capacity;
	}
	void __redispersion();
public:
	static const int DEFAULT_CAPACITY;

	MultiMap();
	~MultiMap();
	void add(const TKey &key, const TValue &value);
	bool containsEntry(const TKey &key, const TValue &value) const;
	bool containsKey(const TKey &key) const;
	Vector<Entry<TKey, TValue>> entries() const;
	Vector<TValue> get(const TKey &key) const;
	Vector<TKey> keys() const;
	Vector<TValue> values() const;
	Vector<TKey> keySet() const;
	Vector<TValue> getValuesByKey(const TKey key);
	void remove(const TKey &key, const TValue &value) const;
	void removeAll(const TKey &key) const;
	bool empty();
	Vector<TValue> operator[](const TKey &key);
	const int capacity() const;
	const int size() const;
	IteratorMultiMap<TKey, TValue> begin() const;
	IteratorMultiMap<TKey, TValue> end();

};

/* Start of MultiMap implementation */

template<typename TKey, typename TValue>const int MultiMap<TKey, TValue>::DEFAULT_CAPACITY = 1;

template<typename TKey, typename TValue>MultiMap<TKey, TValue>::MultiMap() {
	this->__size = 0;
	this->__capacity = this->DEFAULT_CAPACITY;
	this->__entries = new Entry<TKey, TValue>[this->__capacity];
}

template<typename TKey, typename TValue>MultiMap<TKey, TValue>::~MultiMap() {
	delete[] this->__entries;
}

template<typename TKey, typename TValue>void MultiMap<TKey, TValue>::__redispersion() {
	Entry<TKey, TValue>* oldEntries = this->__entries;
	int newCapacity = this->__capacity * 2 + 1;
	int oldCapacity = this->__capacity;
	this->__capacity = newCapacity;
	this->__size = 0;
	this->__entries = new Entry[this->__capacity];
	for (int i = 0; i < oldCapacity; i++) {
		if (oldEntries[i].isValid()) {
			this->add(oldEntries[i].getKey(), oldEntries[i].getValue());
		}
	}
	delete[] oldEntries;
}

template<typename TKey, typename TValue>void MultiMap<TKey, TValue>::add(const TKey &key, const TValue &value) {
	int i, j;
	Entry<TKey, TValue> newEntry{ key, value };
	bool added = false;
	for (i = 0; i < this->__capacity && !added; i++) {
		j = this->__dispersion(newEntry, i);
		if (this->__entries[j].isValid() == false) {
			//am gasit o pozitie libera
			this->__entries[j] = newEntry;
			this->__size++;
			added = true;
		}
	}
}

/* End of MultiMap implementation */

template<typename TKey, typename TValue>class IteratorMultiMap {
private:
	const MultiMap<TKey, TValue> &__multiMap;
	int __curent;

	void __ensureValidPosition() {
		while (this->__curent < this->__multiMap.capacity() && this->__multiMap.__entries[this->__curent].valid() == false) {
			this->__curent++;
		}
	}
public:
	//friend class MultiMap;
	IteratorMultiMap(const MultiMap& map) : __multiMap{ map } {
		this->__curent = 0;
		this->__ensureValidPosition();
	}
	IteratorMultiMap(const MultiMap& map, int poz) : __multiMap{ map }, __curent{ poz } {}
	bool valid() const {
		return this->__curent < this->__multiMap.capacity();
	}
	Entry<TKey, TValue>& element() const {
		return this->__multiMap.__entries[this->__curent];
	}
	void next() {
		this->__curent++;
		this->__ensureValidPosition();
	}
	Entry<TKey, TValue>& operator*() const {
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

#endif /* MULTIMAP_H */