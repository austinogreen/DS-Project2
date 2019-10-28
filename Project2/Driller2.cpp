#include <iostream>
#include <fstream>
#include <string>
#include <ios>
#include <iomanip>
#include <vector>
#include "DrillingRecord.h"
#include "ResizableArray.h"
#include "Exceptions.h"
#include "DrillingRecordComparator.h"
#include "Search.h"
#include "Sorter.h"
#include "Comparator.h"
#include "OULink.h"
#include "OULinkedList.h"
#include "OULinkedListEnumerator.h"


using namespace std;

// Global Drilling Array and List
ResizableArray<DrillingRecord>* drillingArray = NULL;
OULinkedList<DrillingRecord>* drillingList = NULL;

// string to dump bad data
string garbage;

// number of data lines read in
int dataLines = 0;
// number of valid entries
int validEntries = 0;

// The biggest desision here is whether or not to assume more that more items already exist in the list or not
// This method assumes that there will be more new items in the list than not
// This is O(n) were n is the number of items in the drillingList
void mergeDrillingList(OULinkedList<DrillingRecord>* mergeList) {
	OULinkedListEnumerator<DrillingRecord> enumerator = mergeList->enumerator();

	bool hasInserted = false;

	// if empty exit
	if (mergeList->getSize() == 0) {
		return;
	}

	// While there is a next item
	while (enumerator.hasNext()) {
		DrillingRecord tempDR = enumerator.next();
		// Try to insert an item
		// Returns false if item already inserted
		hasInserted = drillingList->insert(tempDR);
		// If the item wasn't inserted it already exists
		// Then replace
		if (!hasInserted) {
			drillingList->replace(tempDR);
		}
	}

	return;
}

// Gets rid of items in pergeList from drillingList
// This is O(n) were n is the number of items in the drillingList
void pergeDrillingList(OULinkedList<DrillingRecord>* pergeList) {
	OULinkedListEnumerator<DrillingRecord> enumerator = pergeList->enumerator();

	// While there is a next item
	while (enumerator.hasNext()) {

		// Removes item from Drilling List
		drillingList->remove(enumerator.next());

	}
	return;
}

// Converts the list to an array
// Arrays are better for searching and sorting
// This is O(n) were n is the number of items in the drillingList
void listToArray() {

	// Deletes previous array and recreates it
	delete drillingArray;
	drillingArray = new ResizableArray<DrillingRecord>();

	if (drillingArray == NULL) {
		throw new ExceptionMemoryNotAvailable();
	}

	// Doesn't have any items
	if (drillingList->getSize() == 0) {
		return;
	}

	OULinkedListEnumerator<DrillingRecord> enumerator = drillingList->enumerator();

	// While there is a next item
	while (enumerator.hasNext()) {
		// Add the items to drillingArray
		drillingArray->add(enumerator.next());
	}

	return;
}

// Reads a files based on a user input
OULinkedList<DrillingRecord>* readFile() {
	ifstream inputFile;

	// File name that the user wants to input
	string fileName;

	// Compares by column
	DrillingRecordComparator* comparator = new DrillingRecordComparator(1);

	if (comparator == NULL) {
		throw new ExceptionMemoryNotAvailable();
	}

	OULinkedList<DrillingRecord>* tempList = new OULinkedList<DrillingRecord>(comparator);
	
	if (tempList == NULL) {
		throw new ExceptionMemoryNotAvailable();
	}



	// Initial file name input
	cout << "Enter data file name: ";

	getline(cin, fileName);

	inputFile.open(fileName);

	bool hasData = false;

	// Check if file exists
	if (inputFile.is_open()) {

		// The drilling array
		DrillingRecord* drillingRecord = new DrillingRecord();

		if (drillingRecord== NULL) {
			throw new ExceptionMemoryNotAvailable();
		}

		// Temperary string variable
		string tempString;

		// Time array
		string date;

		bool isValid;

		// iterator
		unsigned int i;

		int lineCount = 0;

		// Throws away first line
		getline(inputFile, garbage);

		// Puts date in date variable
		getline(inputFile, tempString, ',');
		date = tempString;

		// While not at end of file
		while (!(inputFile.eof())) {
			// preps the valid flag to true
			isValid = true;
			hasData = true;

			// Check if date is the same
			if (tempString.compare(date) != 0) {
				cout << "Non-matching date stamp " << tempString << " at line " << lineCount + 1 << "." << endl;
				isValid = false;
			}
			else {
				drillingRecord->addString(tempString);
			}

			getline(inputFile, tempString, ',');
			// If data is still valid
			if (isValid) {

				drillingRecord->addString(tempString);

				// Check if timestamp is in the list already
				if (tempList->contains(*drillingRecord)) {
					cout << "Duplicate timestamp " << tempString << " at line " << lineCount + 1 << "." << endl;
					isValid = false;
				}
			}

			// puts data in data array
			// gets first 15 data points that are separated by commas
			for (i = 0; i < 15; i++) {
				getline(inputFile, tempString, ',');

				drillingRecord->addNum(stod(tempString));
			}
			// gets final data point with newline
			getline(inputFile, tempString);
			drillingRecord->addNum(stod(tempString));

			// checks if data is valid
			for (i = 0; i < 16; i++) {
				if ((drillingRecord->getNum(i) <= 0) && isValid) {
					cout << "Invalid floating-point data at line " << lineCount + 1 << "." << endl;
					isValid = false;
					break;
				}
			}

			// If valid, increment dataPoints and add object to array
			if (isValid) {
				validEntries++;
				tempList->insert(*drillingRecord);
			}
			// If not valid, delete object and recreate it
			else {
				delete drillingRecord;
				drillingRecord = new DrillingRecord();

				if (drillingRecord == NULL) {
					throw new ExceptionMemoryNotAvailable();
				}
			}

			// Get next date parameter
			getline(inputFile, tempString, ',');

			lineCount++;
			dataLines++;
		}
		// Close file
		inputFile.close();

		// Linked List is Empty
		if (!hasData) {
			cout << "No valid records found." << endl;
			return NULL;
		}
		// Return Linked List
		else {
			return tempList;
		}

	}

	// File does not exist
	else {
		if (!fileName.empty()) {
			cout << "File is not available." << endl;
			return readFile();
		}
		return NULL;
	}
}

void outputLoop(void) {
	// if there is a valid input
	if (validEntries > 0) {

		// Output choice
		char choice;
		string temp;
		string fileName;
		// File out
		ofstream outputFile;
		// Column the data is currently sorted by
		int sortedColumn = 1;

		// This flag sets weather or not the array needs to be updated because changes have been made to the list
		bool changed = false;

		OULinkedList<DrillingRecord>* tempList = NULL;

		// comparator
		DrillingRecordComparator* comparator;

		// Temp Drilling Record
		DrillingRecord* tempDR = new DrillingRecord();

		if (tempDR == NULL) {
			throw new ExceptionMemoryNotAvailable();
		}

		listToArray();

		cout << "Enter (o)utput, (s)ort, (f)ind, (m)erge, (p)urge, (r)ecords, or (q)uit: ";

		cin >> choice;
		getline(cin, temp);

		while (choice != 'q') {
			switch (choice) {
				case 'o':
					// If the list has been updated since last array transfer
					if (changed) {
						listToArray();
						sortedColumn = 1;
						changed = false;
					}

					// Checks for file to output to
					cout << "Enter output file name: ";
					getline(cin, fileName);

					// Output to chosen file
					if (!(fileName.empty())) {
						// open file
						outputFile.open(fileName);

						// Loops until valid file is entered
						while (!(outputFile.is_open())) {
							cout << "File is not available." << endl;

							// Checks for file to output to
							cout << "Enter output file name: ";
							getline(cin, fileName);

							// open file
							outputFile.open(fileName);
						}

						try {
							for (long unsigned int i = 0; i < drillingArray->getSize(); i++) {
								outputFile << drillingArray->get(i) << endl;
							}

							// Outputs internal tallies
							outputFile << "Data lines read: " << dataLines
								<< "; Valid Drilling records read: " << validEntries
								<< "; Drilling records in memory: " << drillingArray->getSize()
								<< endl;

							outputFile.close();
						}
						catch (ExceptionIndexOutOfRange e) {
							// It broke :(
						}
					}

					else {
						// Prints data (loop)
						try {
							for (long unsigned int i = 0; i < drillingArray->getSize(); i++) {
								cout << drillingArray->get(i) << endl;
							}

							// Outputs internal tallies
							cout << "Data lines read: " << dataLines
								<< "; Valid Drilling records read: " << validEntries
								<< "; Drilling records in memory: " << drillingArray->getSize()
								<< endl;
						}
						catch (ExceptionIndexOutOfRange e) {
							// It broke :(
						}
					}
					break;
				case 's':
					// If the list has been updated since last array transfer
					if (changed) {
						listToArray();
						sortedColumn = 1;
						changed = false;
					}
					// sort stuff
					// column to sort
					int column;

					// Get column to sort
					cout << "Enter sort field (0-17):" << endl;
					cin >> column;
					getline(cin, garbage);

					// if there is no data, break
					if (drillingArray->getSize() == 0) {
						break;
					}

					// Make sure to check if valid
					if ((column < 0) && (column > 17)) {

						// invalid column
						// returns to loop
					}

					// Sorts data
					else {

						comparator = new DrillingRecordComparator(column);

						if (comparator == NULL) {
							throw new ExceptionMemoryNotAvailable();
						}

						Sorter<DrillingRecord>::sort(*drillingArray, *comparator);

						sortedColumn = column;
					}

					break;

				case 'f': {
					// If the list has been updated since last array transfer
					if (changed) {
						listToArray();
						sortedColumn = 1;
						changed = false;
					}
					// Get column to search
					cout << "Enter search field (0-17): ";
					cin >> column;
					getline(cin, garbage);

					// whether data is sorted by indicated column to choose which search to preform
					bool isSorted = (column == sortedColumn);

					// Make sure to check if valid
					if ((column < 0) && (column > 17)) {

						// invalid column
					}

					// Column is the sorted column therefore can use binary search
					else {
						if ((column >= 2) && (column <= 17)) {
							// Get value to sort
							double value;
							cout << "Enter positive field value: ";
							cin >> value;
							getline(cin, garbage);
							tempDR->setNum(value, column - 2);
						}
						else if ((column == 0) || (column == 1)) {
							string value;
							cout << "Enter exact text on which to search: ";
							getline(cin, value);
							tempDR->setString(value, column);
						}

						comparator = new DrillingRecordComparator(column);

						if (comparator == NULL) {
							throw new ExceptionMemoryNotAvailable();
						}

						ResizableArray<long long>* idxArray = search(*tempDR, *drillingArray, isSorted, *comparator);

						unsigned long count = idxArray->getSize();

						// idx is negative therefore element dne
						if (isSorted && (idxArray->get(0) < 0)) {
							count = 0;
						}
						else {
							for (unsigned long i = 0; i < count; i++) {
								cout << drillingArray->get((unsigned long)idxArray->get(i)) << endl;
							}
						}

						cout << "Drilling records found: " << count << "." << endl;
					}
				}

					break;

				case 'm':

					tempList = readFile();

					if (tempList != NULL) {
						mergeDrillingList(tempList);

						// Set flag to update array if something is to be done with it
						changed = true;
					}

					break;

				case 'p':

					tempList = readFile();

					if (tempList != NULL) {
						pergeDrillingList(tempList);

						// Set flag to update array if something is to be done with it
						changed = true;
					}

					break;

				case 'r':

					OULinkedListEnumerator<DrillingRecord> enumerator = drillingList->enumerator();

					// Checks for file to output to
					cout << "Enter output file name: ";
					getline(cin, fileName);

					// Output to chosen file
					if (!(fileName.empty())) {
						// open file
						outputFile.open(fileName);

						// Loops until valid file is entered
						while (!(outputFile.is_open())) {
							cout << "File is not available." << endl;

							// Checks for file to output to
							cout << "Enter output file name: ";
							getline(cin, fileName);

							// open file
							outputFile.open(fileName);
						}

						try {
							// Drilling List has nothing to display
							if (drillingList->getSize() == 0) {
								// Outputs internal tallies
								outputFile << "Data lines read: " << dataLines
									<< "; Valid Drilling records read: " << validEntries
									<< "; Drilling records in memory: " << drillingList->getSize()
									<< endl;
								break;
							}

							while (enumerator.hasNext()) {
								outputFile << enumerator.next() << endl;
							}

							// Outputs internal tallies
							outputFile << "Data lines read: " << dataLines
								<< "; Valid Drilling records read: " << validEntries
								<< "; Drilling records in memory: " << drillingList->getSize()
								<< endl;
						}
						catch (ExceptionIndexOutOfRange e) {
							// It broke :(
						}
					}

					else {
						// Prints data (loop)
						try {
							// Drilling List has nothing to display
							if (drillingList->getSize() == 0) {
								// Outputs internal tallies
								cout << "Data lines read: " << dataLines
									<< "; Valid Drilling records read: " << validEntries
									<< "; Drilling records in memory: " << drillingList->getSize()
									<< endl;
								break;
							}
							while (enumerator.hasNext()) {
								cout << enumerator.next() << endl;
							}

							// Outputs internal tallies
							cout << "Data lines read: " << dataLines
								<< "; Valid Drilling records read: " << validEntries
								<< "; Drilling records in memory: " << drillingList->getSize()
								<< endl;
						}
						catch (ExceptionIndexOutOfRange e) {
							// It broke :(
						}
					}
					break;

			}

			cout << "Enter (o)utput, (s)ort, (f)ind, (m)erge, (p)urge, (r)ecords, or (q)uit: ";
				cin >> choice;
			getline(cin, garbage);
		}
	}
}

// Main function, this calls other functions in the Driller2 program
int main() {

	// Initializes the drilling list
	drillingList = new OULinkedList<DrillingRecord>(new DrillingRecordComparator(1));
	if (drillingList == NULL) {
		throw new ExceptionMemoryNotAvailable();
	}

	// Creates a temporary list for new data to be placed into
	OULinkedList<DrillingRecord>* tempList = NULL;

	// Gets user input and places it into the list
	tempList = readFile();

	// if the list is not null, it has data and therefore needs to be merged
	if (tempList != NULL) {
		mergeDrillingList(tempList);
	}

	// Goes into the user output loop
	outputLoop();
	
	// Only thank if valid data was input
	if (validEntries > 0) {
		cout << "Thanks for using Driller." << endl;
	}
	return 0;
}