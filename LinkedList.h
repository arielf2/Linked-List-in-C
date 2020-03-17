#ifndef LINKEDLIST_H
#define LINKEDLIST_H




typedef struct LinkedListNode {
	int value;
	struct LinkedListNode* next_node;
} Node;

void InsertEndOfList(Node** head, int value);

void InsertStartOfList(Node** head, int value);

int InsertAfterElement(Node** head, int new_elemenet, int element_before_new);

Node* SearchForElement(Node* head, int value, int print_index);

void PrintList(Node* head);

int RemoveIndex(Node** head, int index);

void TerminateList(Node* head);

#endif
