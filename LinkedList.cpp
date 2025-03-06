#include "LinkedList.h"

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



