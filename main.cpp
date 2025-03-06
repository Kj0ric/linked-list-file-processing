#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
using namespace std;
#include "LinkedList.h"

int main() {
	// File processing. No need for input checks
	// Not allowed to go over the files more than once

	string		file_name1, file_name2;
	ifstream	input1, input2;
	// Keep 3 linked lists: One for file1 words, one for file2 words, one for common words
	LinkedList list1, list2, common_list;
	string line1, line2, word;
	bool file1_has_data = true;
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

	#ifndef NDEBUG
		cout << "[DEBUG] Successfully opened both files" << endl;
	#endif

	// Read from the files one by one: one word from file1 then one word from file2
	// if one of them finishes early, continue reading the unfinished
	// a particular word can appear only in one of the three lists
	// When you see a common word, delete it from its former linked list and add it to common linked list
	// Counts are for the number of occurrences of that word read from all the files so far
	// Nodes are SORTED. Lower count comes before. If same count, alphabetically ascending

	while (file1_has_data || file2_has_data) {
		// Process file1 if it has data
		if (file1_has_data && input1 >> word) {
			cout << "Processing the word \"" << word << "\" from the 1st file." << endl;
			/*
			if (list2.isInList(word)) {
				// If in list2, delete it from list2 and add it to common_list with
				// the count aggregated
				list2.deleteItem(word);
				common_list.addWord(word);
			} else if (common_list.isInList(word)) {
				// If in common_list, increment the count there
				common_list.incrementCount(word);

			} else {
				// word is unique to file1 so far, add to list1
				list1.addWord(word);
			}
			*/
		} else {
			file1_has_data = false;
		}

		if (file2_has_data && input2 >> word) {
			cout << "Processing the word \"" << word << "\" from the 2nd file." << endl;
			/*
			if (list1.isInList(word)) {
				// If word is in list1, remove it from list1 and add to common
				list1.delete(word);
				common_list.addWord(word);
			} else if (common_list.isInList(word)) {
				// If word is in common, increment its count
				common_list.incrementCount(word);
			} else {
				// word is unique to file2 so far, add to list2
				list2.addWord(word);
			}
			*/
		} else {
			file2_has_data = false;
		}
	}
	input1.close();
	input2.close();

	return 0;
}