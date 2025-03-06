#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
#include "LinkedList.h"

// Displays three lists using their member function printList()
void displayLists(const LinkedList& l1, const LinkedList& l2, const LinkedList& l3) {
	// Display list1 (words unique to file1)
	cout << "\nList for File 1:" << endl;
	l1.printList();
	cout << endl;

	// Display list2 (words unique to file2)
	cout << "List for File 2:" << endl;
	l2.printList();
	cout << endl;

	// Display common_list (words common to both files)
	cout << "Common List:" << endl;
	l3.printList();
	cout << endl;

	cout << "#############" << endl;
	cout << endl; // Extra blank line between displays
}

int main() {
	// File processing. No need for input checks
	// Not allowed to go over the files more than once

	string		file_name1, file_name2;		// Store file names received as console input
	ifstream	input1, input2;				// ifstream objects to read files

	// Keep 3 linked lists: One for file1 words, one for file2 words, one for common words
	LinkedList list1, list2, common_list;
	string line1, line2, word1, word2;		// Helper string objects to store the individual lines and words from files
	bool file1_has_data = true;				// Two flag variables to indicate if the reading of a file is finished
	bool file2_has_data = true;

	// Get first file name
	cout << "Please enter the first file name:" << endl;
	cin >> file_name1;
	input1.open(file_name1);

	// Keep trying until opening the first file successfully
	while ( input1.fail() ) {
		cout << "The file couldn't be opened." << endl << "Please enter a valid file name:" << endl;
		cin >> file_name1;
		input1.open(file_name1);
	}

	// Get second file name
	cout << "Please enter the second file name:" << endl;
	cin >> file_name2;
	input2.open(file_name2);

	// Keep trying until opening the second file successfully
	while ( input2.fail() ) {
		cout << "The file couldn't be opened." << endl << "Please enter a valid file name:" << endl;
		cin >> file_name2;
		input2.open(file_name2);
	}
	/*
	#ifndef NDEBUG
		cout << "[DEBUG] Successfully opened both files" << endl;
	#endif
	*/

	// Read from the files one by one: one word from file1 then one word from file2
	// if one of them finishes early, continue reading the unfinished
	// a particular word can appear only in one of the three lists
	// When you see a common word, delete it from its former linked list and add it to common linked list
	// Counts are for the number of occurrences of that word read from all the files so far
	// Nodes are SORTED. Lower count comes before. If same count, alphabetically ascending
	while (file1_has_data || file2_has_data) {
		// Process file1 if it has data
		if (file1_has_data && input1 >> word1) {
			cout << "Processing the word \"" << word1 << "\" from the 1st file." << endl;

			if (common_list.isInList(word1)) {
				// Simply increment the count
				common_list.incrementCount(word1);
			} else if (list2.isInList(word1)) {
				// Remove from list2, add to common
				int prev_count = list2.deleteItem(word1);
				common_list.addItem(word1, prev_count + 1);
			} else if (list1.isInList(word1)) {
				// Simply increment the count
				list1.incrementCount(word1);
			} else {
				// Word is unique to file1 so far
				list1.addItem(word1, 1);
			}
		} else {
			file1_has_data = false;
		}

		if (file2_has_data && input2 >> word2) {
			cout << "Processing the word \"" << word2 << "\" from the 2nd file." << endl;

			if (common_list.isInList(word2)) {
				// Simply increment the count
				common_list.incrementCount(word2);
			} else if (list1.isInList(word2)) {
				// If in list1, it's now common. Remove from list1, add it to common
				int prev_count = list1.deleteItem(word2);
				common_list.addItem(word2, prev_count + 1);
			} else if (list2.isInList(word2)) {
				// Already in list2, simply increment the count
				list2.incrementCount(word2);
			} else {
				// Word is unique to file 2 so far, add to list2
				list2.addItem(word2, 1);
			}
		} else {
			file2_has_data = false;
		}

		// Only display if we successfully read from both files this iteration
		if ((file1_has_data && !word1.empty()) || (file2_has_data && !word2.empty())) {
			displayLists(list1, list2, common_list);
		}
	}
	cout << "End of Files.";
	input1.close();
	input2.close();

	// Deallocate the memory for the lists
	list1.selfDestruct();
	list2.selfDestruct();
	common_list.selfDestruct();

	return 0;
}
