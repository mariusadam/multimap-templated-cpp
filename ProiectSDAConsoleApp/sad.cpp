const int MultiMap::DEFAULT_CAPACITY = 1;

MultiMap::MultiMap() {
	this->__size = 0;
	this->__capacity = this->DEFAULT_CAPACITY;
	this->__pairs = new Pereche[DEFAULT_CAPACITY];
}

MultiMap::~MultiMap() {
	delete[] this->__pairs;
}

void MultiMap::__redispersion() {
	Entry* oldPairs = this->__pairs;
	int newCapacity = this->__capacity * 2 + 1;
	int oldCapacity = this->__capacity;
	this->__capacity = newCapacity;
	this->__size = 0;
	this->__pairs = new Pereche[this->__capacity];
	for (int i = 0; i < oldCapacity; i++) {
		if (oldPairs[i].valid()) {
			this->add(oldPairs[i].getKey(), oldPairs[i].getValue());
		}
	}
	delete[] oldPairs;
}

void MultiMap::adddd(const TKey & key, const TValue & value) {
	int i, j;
	Entry pair{ key, value };
	bool found = false;
	for (i = 0; i < this->__capacity && !found; i++) {
		j = this->__dispersion(pair, i);
		if (this->__pairs[j].valid() == false) {
			//am gasit o pozitie libera
			this->__pairs[j] = pair;
			found = true;
			this->__size++;
		}
	}
	if (i == this->__capacity) {
		this->__redispersion();
		this->add(key, value);
	}	
}

void MultiMap::deleteKey(const TKey & key) {
	if (this->keyExists(key) == false) {
		std::string error{ "KeyError : key " + key + " could not be found!" };
		throw MultiMapException(error.c_str());
	}
	int i = 0, j;
	Entry pair{ key, "__cant be empty" };
	//itterate through all possible positions and delete pairs with __key = key
	for (int i = 0; i < this->__capacity; i++) {
		j = this->__dispersion(pair, i);
		if (this->__pairs[j].getKey() == key) {
			this->__pairs[j].makeInvalid();
		}
	}
}

bool MultiMap::keyExists(const TKey & key) {
	int i = 0, j;
	bool found = false;
	Entry pair{ key, "__cant be empty" };
	for (int i = 0; i < this->__capacity && !found; i++) {
		j = this->__dispersion(pair, i);
		if (this->__pairs[j].getKey() == key) {
			found = true;
		}
	}
	return found;
}

Vector<TKey> MultiMap::keys() {
	Vector<TKey> keys;
	for (int i = 0; i < this->__capacity; i++) {
		if (this->__pairs[i].valid() && keys.has(this->__pairs[i].getKey()) == false) {
			keys.push_back(this->__pairs[i].getKey());
		}
	}
	return keys;
}

Vector<TValue> MultiMap::values() {
	Vector<TKey> values;
	for (int i = 0; i < this->__capacity; i++) {
		if (this->__pairs[i].valid()) {
			values.push_back(this->__pairs[i].getValue());
		}
	}
	return values;
}

Vector<TValue> MultiMap::getValuesByKey(const TKey key) {
	if (this->keyExists(key) == false) {
		std::string error{ "KeyError : key " + key + " could not be found!" };
		throw MultiMapException(error.c_str());
	}
	Vector<TValue> values;
	for (int i = 0; i < this->__capacity; i++) {
		if (this->__pairs[i].valid() && this->__pairs[i].getKey() == key) {
			values.push_back(this->__pairs[i].getValue());
		}
	}
	return values;
}

bool MultiMap::empty() {
	return this->__size == 0;
}

Vector<TValue> MultiMap::operator[](const TKey & key) {
	return this->getValuesByKey(key);
}

const int MultiMap::capacity() const {
	return this->__capacity;
}

IteratorMultiMap MultiMap::begin() const
{
	return IteratorMultiMap(*this);
}

IteratorMultiMap MultiMap::end() {
	return IteratorMultiMap(*this, this->__capacity);
}

const int MultiMap::size()const {
	return this->__size;
}
