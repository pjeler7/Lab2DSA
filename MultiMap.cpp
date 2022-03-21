#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

//Complexity: Theta(1)
MultiMap::MultiMap() {
	dllKeys = new DLLKeys();
	dllKeys->head = NULL;
	dllKeys->tail = NULL;

}

//Complexity: O(n)
void MultiMap::add(TKey c, TValue v) {
	KeyNode* current = dllKeys->head;

	while (current != dllKeys->tail && current->key != c) {
		current = current->next;
	}
	if (current == NULL) {
		KeyNode* newNode = new KeyNode();
		newNode->key = c;
		DLLValues* dv = new DLLValues();
		ValueNode* valueNode = new ValueNode();
		valueNode->value = v;
		dv->head = valueNode;
		dv->head->next = NULL;
		dv->head->prev = NULL;
		dv->tail = dv->head;
		newNode->values = dv;
		dllKeys->head = newNode;
		dllKeys->tail = newNode;
		return;
	}
	if (current->key == c) {
		ValueNode* newNode = new ValueNode();
		newNode->value = v;
		newNode->next = NULL;
		newNode->prev = current->values->tail;
		if (current->values->head == NULL) {
			current->values->head = newNode;
			current->values->tail = newNode;
		}
		else {
			current->values->tail->next = newNode;
			current->values->tail = newNode;
		}
	}
	else {
		KeyNode* newNode = new KeyNode();
		newNode->key = c;
		DLLValues* dv = new DLLValues();
		ValueNode* valueNode = new ValueNode();
		valueNode->value = v;
		dv->head = valueNode;
		dv->head->next = NULL;
		dv->head->prev = NULL;
		dv->tail = dv->head;
		newNode->values = dv;
		if (current == dllKeys->head) {
			dllKeys->head = newNode;
			newNode->prev = NULL;
			newNode->next = current;
			current->prev = newNode;
			return;
		}
		if (current == dllKeys->tail) {
			dllKeys->tail = newNode;
			newNode->next = NULL;
			newNode->prev = current;
			current->next = newNode;
			return;
		}
		newNode->prev = current->prev;
		newNode->next = current;
		current->prev = newNode;
		current->prev->next = newNode;
	}
}

void MultiMap::print() {
	KeyNode* key = dllKeys->head;
	while (key) {
		cout << "Key: " << key->key << ": ";
		ValueNode* nn = key->values->head;
		while (nn) {
			cout << nn->value << " ";
			nn = nn->next;
		}
		key = key->next;
		cout << endl;
	}
}


bool MultiMap::remove(TKey c, TValue v) {
	KeyNode* keyNode = dllKeys->head;
	while (keyNode != NULL) {
		if (keyNode->key == c) {
			bool wasRemoved = deleteValueElement(keyNode->values, v);
			if (wasRemoved)
				if (keyNode->values->head == NULL)
					deleteKeyElement(keyNode->key);
			return wasRemoved;
		}
		keyNode = keyNode->next;
	}
	return  false;
}

//Complexity: O(n*m)
vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> v;
	KeyNode* keyNode = dllKeys->head;
	while (keyNode != NULL) {
		if (keyNode->key == c) {
			ValueNode* valueNode = keyNode->values->head;
			while (valueNode != NULL) {
				v.push_back(valueNode->value);
				valueNode = valueNode->next;
			}
			return v;
		}
		keyNode = keyNode->next;
	}
	return v;
}

//Complexity: Theta(n)
int MultiMap::size() const {
	int nr = 0;
	KeyNode* keyNode = dllKeys->head;
	while (keyNode != NULL) {
		ValueNode* valueNode = keyNode->values->head;
		while (valueNode != NULL) {
			nr++;
			valueNode = valueNode->next;
		}
		keyNode = keyNode->next;
	}
	return nr;
}

//Complexity: Theta(1)
bool MultiMap::isEmpty() const {
	return dllKeys->head == NULL;
}

//Complexity: Theta(1)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

//Complexity: Theta(n*m)
MultiMap::~MultiMap() {
	KeyNode* currentNode = dllKeys->head;
	while (currentNode != dllKeys->tail) {
		ValueNode* valueNode = currentNode->values->head;
		while (valueNode != currentNode->values->tail) {
			valueNode = valueNode->next;
			delete valueNode->prev;
		}
		delete valueNode;
		delete currentNode->values;
		currentNode = currentNode->next;
		delete currentNode->prev;
	}
	delete currentNode;
	delete dllKeys;
}

void MultiMap::deleteKeyElement(TKey key)
{
	KeyNode* currentNode = dllKeys->head;
	while (currentNode != dllKeys->tail && currentNode->key != key) {
		currentNode = currentNode->next;
	}
	if (currentNode != NULL) {
		if (currentNode == dllKeys->head)
			dllKeys->head = currentNode->next;

		if (currentNode == dllKeys->tail)
			dllKeys->tail = currentNode->prev;

		if (currentNode->next != NULL)
			currentNode->next->prev = currentNode->prev;

		if (currentNode->prev != NULL)
			currentNode->prev->next = currentNode->next;

		delete currentNode;
	}
}

bool MultiMap::deleteValueElement(DLLValues* dllValues, TValue value)
{
	ValueNode* currentNode = dllValues->head;
	while (currentNode != NULL) {
		if (currentNode->value == value) {
			if (currentNode == dllValues->head)
				dllValues->head = currentNode->next;

			if (currentNode == dllValues->tail)
				dllValues->tail = currentNode->prev;

			if (currentNode->prev != NULL)
				currentNode->prev->next = currentNode->next;

			if (currentNode->next != NULL)
				currentNode->next->prev = currentNode->prev;

			delete currentNode;
			return true;
		}
		currentNode = currentNode->next;
	}
	return false;
}

