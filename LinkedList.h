//
// Created by Harun Yılmaz on 4.03.2025.
//
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <iostream>
using namespace std;


struct Node {
	string word;
	int count;
	Node* next;

	Node(const string& w)
		: word(w), count(0), next(nullptr)
	{}
};

class LinkedList {
private:
	Node* head;
public:
	LinkedList();
	void printList();
	void addWord(const string& word);
};



#endif //LINKEDLIST_H
