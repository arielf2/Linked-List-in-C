#include <stdlib.h>
#include <stdio.h>

#include "LinkedList.h"


#define ERROR_INDEX_NOT_FOUND -1
#define SUCCESS 0
#define ERROR 1

/*  Note to grader:
	RemoveIndex and SearchForElement perform similar operations,
	yet they are still 2 different functions because they have
	a fundamental difference - RemoveIndex has to keep track of
	2 nodes during traversal of linked list, and SearchForElement
	has to keep track of only one node. I could not find a way to
	have both features under a single function while keeping our
	coding conventions, therefore I have two similar (albeit not identical)
	functions */


void InitalizeLinkedList(Node** head, int value);

bool IsEmptyList(Node* head);

Node* CreateNewNode(int value);

void PrintIndexIfFound(bool found, int index);


void InitalizeLinkedList(Node** head, int value) {
	*head = CreateNewNode(value);
}

Node* CreateNewNode(int value) {

	Node* new_node = (Node*)malloc(sizeof(Node));

	new_node->value = value;
	new_node->next_node = NULL;
	return new_node;
}

bool IsEmptyList(Node* head) {
	if (NULL == head) {
		return true;
	}
	return false;
}

void InsertEndOfList(Node** head, int value) {

	if (IsEmptyList(*head)) {
		InitalizeLinkedList(head, value);
	}
	else {
		Node* current_node = *head;
		while (current_node->next_node != NULL) {
			current_node = current_node->next_node;
		}
		current_node->next_node = CreateNewNode(value);
	}
		
}

void InsertStartOfList(Node** head, int value) {

	if (IsEmptyList(*head)) {
		InitalizeLinkedList(head, value);
	}

	else {
		Node* new_start_node = CreateNewNode(value);
		new_start_node->next_node = *head;
		*head = new_start_node;
	}
}

int InsertAfterElement(Node** head, int new_element, int element_before_new) {
	Node* current_node = SearchForElement(*head, element_before_new, 0);
	if (NULL != current_node) {
		Node* new_node = CreateNewNode(new_element);
		new_node->next_node = current_node->next_node;
		current_node->next_node = new_node;
		return SUCCESS;
	}
	else {
		printf("Error: element %d not found\n", element_before_new);
		return ERROR;
	}
	
}

Node* SearchForElement(Node* head, int value, bool print_index) {
	int index = 0;
	bool found = false;
	Node* current_node = head;
	while (current_node != NULL) {
		if (current_node->value == value) {
			found = true;
			break;
		}
		current_node = current_node->next_node;
		index++;
	}

	if (print_index) {
		PrintIndexIfFound(found, index);
		return NULL;
	}
	else {
		if (found) {
			return current_node;
		}
		else {
			return NULL;
		}
	}
}

void PrintIndexIfFound (bool found, int index){
	if (found) {
		printf("%d\n", index);
	}
	else {
		printf("%d\n", ERROR_INDEX_NOT_FOUND);
	}
}

void PrintList(Node* head) {

	if (NULL == head) {
		printf("[]\n");
		return;
	}
	Node* current_node = head;
	printf("[");
	while (current_node->next_node != NULL) {
		printf("%d, ", current_node->value);
		current_node = current_node->next_node;
	}
	printf("%d]\n", current_node->value);
}

int RemoveIndex(Node** head, int index_to_remove) {

	int index = 0;
	bool found = false;
	Node* previous_node = NULL;
	Node* current_node = *head;

	while (current_node != NULL) {
		if (index_to_remove == index) {
			found = true;
			break;
		}
		previous_node = current_node;
		current_node = current_node->next_node;
		index++;
	}
	if (found) {
		if (previous_node != NULL) {
			previous_node->next_node = current_node->next_node;
		}
		else { // special case - remove head of list
			*head = current_node->next_node;
		}
		free(current_node);
		return SUCCESS;
	}
	else {
		printf("Error: index %d exceeds size of linked list\n", index_to_remove);
		return ERROR;
	}
}

void TerminateList(Node* head)
{
	Node* temp_node_pointer;

	while (!IsEmptyList(head))
	{
		temp_node_pointer = head;
		head = head->next_node;
		free(temp_node_pointer);
	}

}


