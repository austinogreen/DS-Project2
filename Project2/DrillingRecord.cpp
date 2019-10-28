#include "DrillingRecord.h"
#include <iomanip>
#include "Exceptions.h"

std::ostream& operator<<(std::ostream& os, const DrillingRecord& record) {
	// Outputs data according to project
	os << record.getString(0) + ";";
	os << record.getString(1) + ";";

	// sets precision to 2 decimal with fixed decimal
	os << std::fixed;
	os << std::setprecision(2);
	// Ouputs numbers
	for (int i = 0; i < 15; i++) {
		os << record.getNum(i) << ";";
	}
	// ensures that there isn't a semicolon at end of line
	os << record.getNum(15);
	return os;
}

DrillingRecord::DrillingRecord() {
	// Initializes strings to empty
	strings[0] = "";
	strings[1] = "";

	// Initiialzes nums to 0.0
	for (unsigned int i = 0; i < MAX_NUMS; i++) {
		nums[i] = 0.0;
	}
}

void DrillingRecord::addNum(double num) {
	// adds number into array
	nums[numCtr] = num;
	// if numCtr is at 15, wrap
	if (numCtr == 15) {

		numCtr = 0;
	}
	// Adds to numCtr
	else {
		numCtr++;
	}
	return;
}

void DrillingRecord::addString(std::string string) {
	// adds string into array
	strings[strCtr] = string;
	// add 1
	if (strCtr == 0) {
		strCtr++;
	}
	// if strCtr is at 1, wrap to zero
	else {
		strCtr = 0;
	}
	return;
}

double DrillingRecord::getNum(unsigned int index) const {
	// out of range
	if (index > 15) {
		throw ExceptionIndexOutOfRange();
	}
	return nums[index];
}

std::string DrillingRecord::getString(unsigned int index) const {
	// out of range
	if (index > 1) {
		throw ExceptionIndexOutOfRange();
	}
	return strings[index];
}

void DrillingRecord::setNum (double num, unsigned int index) {
	// out of range
	if (index > 15) {
		throw ExceptionIndexOutOfRange();
	}
	nums[index] = num;

	return;
}

void DrillingRecord::setString(std::string string, unsigned int index) {
	// out of range
	if (index > 1) {
		throw ExceptionIndexOutOfRange();
	}
	strings[index] = string;

	return;
}
