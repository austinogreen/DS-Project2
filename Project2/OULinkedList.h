#ifndef OU_LINKED_LIST
#define OU_LINKED_LIST

#include "OULink.h"
#include "Comparator.h"
#include "OULinkedListEnumerator.h"

// OULinkedList stands for Ordered, Unique Linked List. It is a linked list that is always maintained in
// order (based on the comparator provided to it when the list is created) and that only contains unique
// items (that is, duplicates are not allowed)
template <typename T>
class OULinkedList {
	//template <typename T>
	//friend class OULinkedListEnumerator;
private:
	Comparator<T>* comparator = NULL;               // used to determine list order and item equality
	unsigned long size = 0;                         // actual number of items currently in list
	OULink<T>* first = NULL;                        // pointer to first link in list
	OULink<T>* last = NULL;                         // pointer to last link in list
public:
	OULinkedList(Comparator<T>* comparator);        // creates empty linked list with comparator
	virtual ~OULinkedList();                        // deletes all links and their data items

	// if an equivalent item is not already present, insert item in order and return true
	// if an equivalent item is already present, leave list unchanged and return false
	bool insert(T item);

	// if item is greater than item at last, append item at end and return true
	// if item is less than or equal to item at last, leave list unchanged and return false
	bool append(T item);

	// if an equivalent item is already present, replace item and return true
	// if an equivalent item is not already present, leave list unchanged and return false
	bool replace(T item);

	// if an equivalent item is already present, remove item and return true
	// if an equivalent item is not already present, leave list unchanged and return false
	bool remove(T item);

	// if any items are present, return a copy of the first item
	// if no items are present, throw new ExceptionLinkedListAccess
	T getFirst() const;

	// if any items are present, return a copy of the first item, remove it from list
	// if no items are present, throw new ExceptionLinkedListAccess
	T pullFirst();

	// if any items are present, remove the first item and return true
	// if no items are present, leave list unchanged and return false
	bool removeFirst();

	// if an equivalent item is present, return true
	// if an equivalent item is not present, false
	bool contains(T item) const;

	// if an equivalent item is present, return a copy of that item
	// if an equivalent item is not present, throw a new ExceptionLinkedListAccess
	T find(T item) const;

	void clear();                                     // deletes all links in the list, resets size to 0

	unsigned long getSize() const;                    // returns the current number of items in the list

	OULinkedListEnumerator<T> enumerator() const;     // create an enumerator for this linked list
};

// Add your implementation below this line. Do not add or modify anything above this line.

// creates empty linked list with comparator
template <typename T>
OULinkedList<T> :: OULinkedList(Comparator<T>* comparator) {
	this->comparator = comparator;
}

// deletes all links and their data items
template <typename T>
OULinkedList<T> :: ~OULinkedList() {
	delete comparator;
	size = 0;
	first = NULL;
	last = NULL;


}

// if an equivalent item is not already present, insert item in order and return true
// if an equivalent item is already present, leave list unchanged and return false
template <typename T>
bool OULinkedList<T> :: insert(T item) {
	if (first == NULL) {
		first = item;
		last = item;
		item->next = NULL;
		size++;
		return true;
	}
	OULink<T>* current = first;
	OULINK<T>* prev = NULL;
	while (!(current->next == NULL) {
		if ((comparator->compare(item, current) == 0)) {
			return false;
		}
		else if ((comparator->compare(item, current) > 0)) {
			prev->next = item;
			item->next = current;
			size++;
			return true;
		}

		prev = current;
		current = current->next;
	}
	current->next = item;
	item->next = NULL;
	last = item;
	size++;
	return true;
}

// if item is greater than item at last, append item at end and return true
// if item is less than or equal to item at last, leave list unchanged and return false
template <typename T>
bool OULinkedList<T> :: append(T item) {
	if (first == NULL) {
		first = item;
		last = item;
		item->next = NULL;
		size++;
		return true;
	}

	OULink<T>* current = first;
	OULINK<T>* prev = NULL;
	
	if (comparator->compare(item, last) > 0) {
		last->next = item;
		last = item;
		item->next = NULL;
		size++;
		return true;
	}

	return false;
}

// if an equivalent item is already present, replace item and return true
// if an equivalent item is not already present, leave list unchanged and return false
template <typename T>
bool OULinkedList<T> :: replace(T item) {
	if (first == NULL) {
		return false;
	}

	OULink<T>* current = first;
	OULINK<T>* prev = NULL;

	while (!(current->next == NULL) {
		if ((comparator->compare(item, current) == 0)) {
			prev->next = item;
			item->next = current->next;
			delete current;
			return true;
		}

		prev = current;
		current = current->next;
	}

	return false;
}

// if an equivalent item is already present, remove item and return true
// if an equivalent item is not already present, leave list unchanged and return false
template <typename T>
bool OULinkedList<T> :: remove(T item) {
	if (first == NULL) {
		return false;
	}

	OULink<T>* current = first;
	OULINK<T>* prev = NULL;

	while (!(current->next == NULL) {
		if ((comparator->compare(item, current) == 0)) {
			prev->next = current->next;
			delete current;
			size--;
			return true;
		}

		prev = current;
		current = current->next;
	}

	return false;
}

// if any items are present, return a copy of the first item
// if no items are present, throw new ExceptionLinkedListAccess
template <typename T>
T OULinkedList<T> :: getFirst() const {
	if (first == NULL) {
		throw ExceptionLinkedListAccess;
	}

	return first;
}

// if any items are present, return a copy of the first item, remove it from list
// if no items are present, throw new ExceptionLinkedListAccess
template <typename T>
T OULinkedList<T> ::pullFirst() {
	if (first == NULL) {
		throw ExceptionLinkedListAccess;
	}

	OULink<T>* temp = first;
	delete first;
	first = temp->next;
	size--;

	return temp;
}

// if any items are present, remove the first item and return true
// if no items are present, leave list unchanged and return false
template <typename T>
bool OULinkedList<T> :: removeFirst() {
	if (first == NULL) {
		return false;
	}

	OULink<T>* temp = first;
	delete first;
	first = temp->next;
	size--;

	return true;
}

// if an equivalent item is present, return true
// if an equivalent item is not present, false
template <typename T>
bool OULinkedList<T> :: contains(T item) const {
	if (first == NULL) {
		return false;
	}

	OULink<T>* current = first;

	while (!(current->next == NULL) {
		if ((comparator->compare(item, current) == 0)) {
			return true;
		}

		prev = current;
		current = current->next;
	}

	return false;
}

// if an equivalent item is present, return a copy of that item
// if an equivalent item is not present, throw a new ExceptionLinkedListAccess
template <typename T>
T OULinkedList<T> :: find(T item) const {
	if (first == NULL) {
		throw ExceptionLinkedListAccess;
	}

	OULink<T>* current = first;

	while (!(current->next == NULL) {
		if ((comparator->compare(item, current) == 0)) {
			return current;
		}

		prev = current;
		current = current->next;
	}

	throw ExceptionLinkedListAccess;
}

// deletes all links in the list, resets size to 0
template <typename T>
void OULinkedList<T> :: clear() {
	if (first == NULL) {
		size = 0;
		return;
	}

	OULink<T> current = first;
	OULink<T> temp;

	// While a next item exists
	while (!(current->next == NULL)) {
		// Stores next item
		temp = current->next;
		// Deletes item
		delete current;
		// Stores next item in current
		current = temp;
	}

	// Deletes remaining current
	delete current;

	size = 0;
	first = NULL;
	last = NULL;

	return;
}

// returns the current number of items in the list
template <typename T>
unsigned long OULinkedList<T> :: getSize() const {
	return size;
}

// create an enumerator for this linked list
template <typename T>
OULinkedListEnumerator<T> OULinkedList<T> :: enumerator() const {
	return new OULinkedListEnumerator(first);
}

#endif // !OU_LINKED_LIST
