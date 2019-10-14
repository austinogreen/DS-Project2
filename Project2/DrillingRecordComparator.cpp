#include "DrillingRecordComparator.h"
#include "Comparator.h"
#include "DrillingRecord.h"

DrillingRecordComparator::DrillingRecordComparator(unsigned int column) {
	this->column = column;
}

// returns -1 if item1 < item2, 0 if item1 == item2, +1 if item1 > item2
int DrillingRecordComparator :: compare(const DrillingRecord& item1, const DrillingRecord& item2) const {
	
	// compares strings
	if ((column == 0) || (column == 1)) {
		return (item1.getString(column)).compare(item2.getString(column));
	}

	// compares doubles
	// column - 2 to get correct number column
	else {
		if ((item1.getNum(column - 2)) > (item2.getNum(column - 2))) {
			return 1;
		}
		else if ((item1.getNum(column - 2)) < (item2.getNum(column - 2))) {
			return -1;
		}
		else {
			return 0;
		}
	}
}