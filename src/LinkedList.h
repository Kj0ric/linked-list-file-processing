#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <iostream>
using namespace std;

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



#endif //LINKEDLIST_H
