#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;


int main() {
	// File processing. No need for input checks
	// Not allowed to go over the files more than once


	string		file_name1, file_name2;
	string		line;
	ifstream	input1, input2;

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


	// Keep 3 linked lists: One for file1 words, one for file2 words, one for common words
	// a particular word can appear only in one of the three lists
	// When you see a common word, delete it from its former linked list and add it to common linked list
	// Counts are for the number of occurrences of that word read from all the files so far
	// Nodes are SORTED. Lower count comes before. If same count, alphabetically ascending

	//

	return 0;
}