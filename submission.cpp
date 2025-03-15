#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

// ------------- Class Interface -------------
struct Node {
	string word;
	int count;
	Node* next;

	explicit Node(const string& w)
		: word(w), count(0), next(nullptr)
	{}

	Node(const string& w, int count)
		: word(w), count(count), next(nullptr)
	{}
};

class LinkedList {
private:
	Node* head;
public:
	LinkedList();

	int deleteItem(const string& word);
	Node* isInList(const string& word);
	void addItem(const string& word, int count);
	void incrementCount(const string& word);
	void printList() const;
	void selfDestruct();
};

// ------------- Class Implementation -------------
// Constructor
LinkedList::LinkedList()
	: head(nullptr)
{}

// Prints the list to the console so that at each line only five words are displayed
void LinkedList::printList() const {
	if (!head) {
		cout << "--||" << endl;
		return;
	}

	int item_count = 0;
	Node* p_current = head;
	while (p_current) {
		cout << p_current->word << "(" << p_current->count << ")";

		p_current = p_current->next;
		item_count++;

		if (p_current) {
			// Start a new line after 5 items
			if (item_count % 5 == 0) {
				cout << " -->" << endl;
				//item_count = 0;
			} else {
				cout << " --> ";
			}
		} else {
			// End of list, print null
			cout << " -->";
			if (item_count % 5 == 0) {
				cout << endl << "--||";
			} else {
				cout << " --||";
			}
		}
	}
	cout << endl;
}


// Precondition: The list contains the node with word
// Postcondition: The node contains word is not in the list
int LinkedList::deleteItem(const string& word) {
	Node* p_current = head;
	Node* p_prev = nullptr;
	string current_word;
	int count = 0;

	while (p_current) {
		current_word = p_current->word;
		if (word != current_word) {
			// Continue iterating
			p_prev = p_current;
			p_current = p_current->next;
		} else {
			// Get the count before deleting
			count = p_current->count;

			if (p_prev == nullptr) {	// Deleting the head
				head = p_current->next; // Update the head
			} else {					// Deleting a non-head node
				p_prev->next = p_current->next;
			}
			delete p_current;
			p_current = nullptr;	// Nullify after deletion
		}
	}
	return count;
}

// Checks if the node containing word is in the list.
// If yes returns the pointer pointing to that node.
// If not, return nullptr.
Node* LinkedList::isInList(const string& word) {
	Node* p_current = head;

	while (p_current) {
		if (p_current->word != word) {
			// Continue iterating
			p_current = p_current->next;
		} else {
			return p_current;
		}
	}
	return nullptr;
}

// Precondition: There is no item containing word in the list. The list is ordered.
// Postcondition: A new node containing word is added to the list. The list is ordered.
// The list order: Lower count comes before. Among same count, alphabetically ascending
void LinkedList::addItem(const string &word, int count) {
	Node* p_current = head;
	Node* p_prev = nullptr;
	Node* p_new = new Node(word, count);

	if (!p_current) {
		// Case 0: List is empty, add to beginning
		head = p_new;	// Update head
	} else {
		while (p_current && (p_current->count < count ||
				p_current->count == count && p_current->word < word)) {
			// Iterate until p_current points to the item that is p_new->next
			p_prev = p_current;
			p_current = p_current->next;
		}
		if (!p_prev) {
			// Case 1: Adding to the beginning
			p_new->next = head;
			head = p_new;
		} else {
			// Case 2: Adding to the middle or end
			p_prev->next = p_new;
			p_new->next = p_current;
		}
	}
}

// Precondition: Sorted list, node containing word has count n
// Postcondition: Sorted list, node containing word has count n+1
void LinkedList::incrementCount(const string &word) {
	Node* p_target = this->isInList(word);
	if (!p_target) return;	// Word not found, nothing to increment

	// Increment the count
	p_target->count++;
	int target_count = p_target->count;

	// Remove target node from its current position
	Node* p_prev = nullptr;
	Node* p_current = head;
	while (p_current && p_current != p_target) {
		p_prev = p_current;
		p_current = p_current->next;
	}
	// Now p_current points to the target node
	// and p_prev points to the one node before it

	if (p_prev) {
		// Remove from middle or end
		p_prev->next = p_target->next;
	} else {
		// Remove from head
		head = p_target->next;
	}

	// Reinsert target node in sorted position
	p_target->next = nullptr;

	p_prev = nullptr;
	p_current = head;
	while (p_current && (p_current->count < target_count ||
			(p_current->count == target_count && p_current->word < p_target->word))) {
		p_prev = p_current;
		p_current = p_current->next;
	}
	// Now target node can be inserted between p_prev and p_current
	if (!p_prev) {
		// Insert at head
		p_target->next = head;
		head = p_target;
	} else {
		// Insert after p_prev
		p_prev->next = p_target;
		p_target->next = p_current;
	}
}

void LinkedList::selfDestruct() {
	Node* p_temp;

	while (head) {
		p_temp = head->next;
		delete head;
		head = p_temp;
	}
}

// ------------- Free Functions -------------
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

// ------------- Main Function -------------
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
