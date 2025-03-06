//
// Created by Harun Yılmaz on 4.03.2025.
//

#include "LinkedList.h"

LinkedList::LinkedList()
	: head(nullptr)
{}

void LinkedList::printList() {

}

/* Delete the first occurrence of word
*/
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

bool LinkedList::isInList(const string& word) {

}

void LinkedList::addNodeInOrder(const string& word) {

}

/* Add a node containing word if the word is not in the list.
 * If the word is in the list, increment the count of the node containing word
*/
void LinkedList::addWord(const string &word) {
	// Check if word is in the list
	// If yes, increase the count
	// Otherwise add the word by keeping the sorted order

}


