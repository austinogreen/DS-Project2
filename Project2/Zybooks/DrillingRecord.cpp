#include "DrillingRecord.h"
#include <iomanip>
#include "Exceptions.h"

std::ostream& operator<<(std::ostream& os, const DrillingRecord& record) {
	os << record.getString(0) + ";";
	os << record.getString(1) + ";";
	os << std::fixed;
	os << std::setprecision(2);

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
	nums[numCtr] = num;
	if (numCtr == 15) {

		numCtr = 0;
	}
	else {
		numCtr++;
	}
	return;
}

void DrillingRecord::addString(std::string string) {
	strings[strCtr] = string;
	if (strCtr == 0) {
		strCtr++;
	}
	else {
		strCtr = 0;
	}
	return;
}

double DrillingRecord::getNum(unsigned int index) const {
	if (index > 15) {
		throw ExceptionIndexOutOfRange();
	}
	return nums[index];
}

std::string DrillingRecord::getString(unsigned int index) const {
	if (index > 1) {
		throw ExceptionIndexOutOfRange();
	}
	return strings[index];
}

void DrillingRecord::setNum (double num, unsigned int index) {
	if (index > 15) {
		throw ExceptionIndexOutOfRange();
	}
	nums[index] = num;

	return;
}

void DrillingRecord::setString(std::string string, unsigned int index) {
	if (index > 1) {
		throw ExceptionIndexOutOfRange();
	}
	strings[index] = string;

	return;
}
