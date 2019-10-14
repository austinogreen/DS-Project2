#ifndef OU_LINKED_LIST_ENUMERATOR
#define OU_LINKED_LIST_ENUMERATOR

#include "Enumerator.h"
#include "OULink.h"
#include "Exceptions.h"

template <typename T>
class OULinkedListEnumerator : public Enumerator<T>
{
private:
	OULink<T>* current;
public:
	OULinkedListEnumerator(OULink<T>* first);
	bool hasNext() const;
	T next();			// throws ExceptionEnumerationBeyondEnd if no next item is available
	T peek() const;		// throws ExceptionEnumerationBeyondEnd if no next item is available
};

// Add your implementation below this line. Do not add or modify anything above this line.

template<typename T>
OULinkedListEnumerator<T>::OULinkedListEnumerator(OULink<T>* first) {
	current = first;
}

template<typename T>
bool OULinkedListEnumerator<T>::hasNext() const {
	// Returns false if next is null
	if (current->next == null) {
		return false;
	}

	return true;
}

// returns copy of next element and advances to next position
// throws ExceptionEnumerationBeyondEnd if no next item is available
template<typename T>
T OULinkedListEnumerator<T>::next() {
	if (hasNext() == false) {
		throw ExceptionEnumerationBeyondEnd;
	}

	T temp* = current;
	
	current = current->next;

	return temp;
}

// returns copy of next element without advancing position
// throws ExceptionEnumerationBeyondEnd if no next item is available
template<typename T>
T OULinkedListEnumerator<T>::peek() const {
	if (hasNext() == false) {
		throw ExceptionEnumerationBeyondEnd;
	}

	return current;
}

#endif // !OU_LINKED_LIST_ENUMERATOR

