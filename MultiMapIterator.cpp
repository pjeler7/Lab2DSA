#include "MultiMapIterator.h"
#include "MultiMap.h"

//Complexity: Theta(1)
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	dllKeys = c.dllKeys;
	currentKey = c.dllKeys->head;
	if (currentKey != NULL)
		currentValue = currentKey->values->head;
}

//Complexity: Theta(1)
TElem MultiMapIterator::getCurrent() const{
	if (!valid())
		throw exception();
	return TElem(currentKey->key, currentValue->value);
}

//Complexity: Theta(1)
bool MultiMapIterator::valid() const {
	return currentKey != NULL;
}

//Complexity: Theta(1)
void MultiMapIterator::next() {
	if (!valid())
		throw exception();
	if (currentValue->next != NULL)
		currentValue = currentValue->next;
	else {
		currentKey = currentKey->next;
		if (currentKey != NULL)
			currentValue = currentKey->values->head;
	}
}

//Complexity: Theta(1)
void MultiMapIterator::first() {
	currentKey = col.dllKeys->head;
	if (currentKey != NULL)
		currentValue = currentKey->values->head;
}

