// Signature must be retained. Implementation must be added.

#ifndef SEARCH_H
#define SEARCH_H

#include "Exceptions.h"
#include "ResizableArray.h"
#include "Comparator.h"

// returns FIRST array location matching the given item (based on the comparator)
// if not found, returns -(location to insert + 1)
template <typename T>
long long binarySearch(const T& item, const ResizableArray<T>& array, const Comparator<T>& comparator) {
	
	// Parameters of binary search
	long long left = 0;
	long long right = (long long)(array.getSize() - 1);
	long long middle;

	int compare;

	// searches while left and right don't overlap
	while (left <= right) {

		middle = (right + left) / 2;

		compare = comparator.compare(item, array.get((unsigned long) middle));

		// item is less than the element so search in left half
		if (compare < 0) {
			right = middle - 1;
		}

		// item is greater than the element so search in right half
		else if (compare > 0) {
			left = middle + 1;
		}

		// item found
		else {
			// ensures that it is the first element that is found
			while ((middle > 0) && (comparator.compare(item, array.get((unsigned long)(middle - 1))) == 0)) {
				middle--;
			}
			return middle;
		}
	}
	// item not found, exit array
	return -(middle + 1);
}

template <typename T>
ResizableArray<long long>* linearSearch(const T& item, const ResizableArray<T>& array, const Comparator<T>& comparator) {

	ResizableArray<long long>* idxArray = new ResizableArray<long long>();

	for (long unsigned int i = 0; i < array.getSize(); i++) {
		if (comparator.compare(array.get(i), item) == 0) {
			idxArray->add(i);
		}
	}
	return idxArray;
}

template <typename T>
ResizableArray<long long>* search(const T& item, const ResizableArray<T>& array, bool isSorted,  const Comparator<T>& comparator) {
	
	ResizableArray<long long>* idxArray = new ResizableArray<long long>();
	
	if (isSorted) {
		long long idx = binarySearch(item, array, comparator);

		idxArray->add(idx);

		// Searches indexes after the returned index to see if multiple items exist
		while ((idx >= 0) && (idx < (long long)(array.getSize() - 1)) && ((comparator.compare(item, array.get((unsigned long)(idx + 1)))) == 0)) {
			idxArray->add(idx + 1);
			idx++;
		}

		return idxArray;
	}

	else {
		return linearSearch(item, array, comparator);
	}
}



#endif