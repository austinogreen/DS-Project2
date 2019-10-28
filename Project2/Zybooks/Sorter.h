// Signature must be retained. Implementation must be added.

#ifndef SORT_H
#define SORT_H

#include "Exceptions.h"
#include "ResizableArray.h"
#include "DrillingRecordComparator.h"

template <typename T>
class Sorter {
private:
	static void quickSort(ResizableArray<T>& array, unsigned long left, unsigned long right, const Comparator<T>& comparator);
	static unsigned long partition(ResizableArray<T>& array, unsigned long left, unsigned long right, const Comparator<T>& comparator);
public:
    static void sort(ResizableArray<T>& array, const Comparator<T>& comparator);
};

template<typename T>
void Sorter<T> :: sort(ResizableArray<T>& array, const Comparator<T>& comparator) {
	
	// Left and right bounds of original array
	unsigned long left = 0;
	unsigned long right = array.getSize() - 1;
   
   quickSort(array, left, right, comparator);
   
   return;
}

template<typename T>
void Sorter<T> :: quickSort(ResizableArray<T>& array, unsigned long left, unsigned long right, const Comparator<T>& comparator) {
   
   // Base case: If 1 or zero elements, partition is already sorted
   if (left >= right) {
      return;
   }
   
	// Partition the array. 
	//	Value middle is the location of last element in low partition
   unsigned long middle = partition(array, left, right, comparator);
   
   // Recursively sort low and high partitions
   quickSort(array, left, middle, comparator);
   quickSort(array, middle + 1, right, comparator);

	return;
}

template<typename T>
unsigned long Sorter<T> :: partition(ResizableArray<T>& array, unsigned long i, unsigned long k, const Comparator<T>& comparator) {
   // Initialize variables
   
   // Pick middle value as pivot
   unsigned long middle = i + (k - i) / 2;
   T pivot = array.get(middle);

   unsigned long left = i;
   unsigned long right = k;
   
   bool done = false;
   
   while (!done) {
      // Increment left while array.get(left) < pivot 
      while (comparator.compare(array.get(left), pivot) < 0) {
         ++left;
      }
      
      // Decrement right while pivot < array.get(right) 
      while (comparator.compare(pivot, array.get(right)) < 0) {
         --right;
      }
	  
	  // If there are zero or one items remaining, all numbers are partitioned. Return right 
      if (left >= right) {
         done = true;
      }
      else {
         // Swap array.get(left) and numbers[right], update left and right 
         T temp = array.get(left);
         array.replaceAt(array.get(right),left);
         array.replaceAt(temp,right);
         
         ++left;
         --right;
      }
   }
   return right;
}

#endif