#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"


Node* CreateNewNode(int value);

int RemoveIndex(Node* head, int index_to_remove) {
	int found = 0, index = 0;
	Node* previous_node = NULL;
	Node* current_node = head;
	while (current_node != NULL) {
		if (index_to_remove == index){
			found = 1;
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
		else {
			Node* tmp = current_node;
			head = current_node->next_node;
			free(tmp);


			//*head = *current_node->next_node; Ver1
		}
		//free(current_node); Ver 1 - works without freeing mem
		return 0;
	}
	else {
		printf("Error: index %d too large\n", index_to_remove);
		return 1;
	}

}

void TerminateList(Node* head)
{
	Node* temp_node_pointer;

	while (head != NULL)
	{
		temp_node_pointer = head;
		head = head->next_node;
		free(temp_node_pointer);
	}

}
	


void InsertEndOfList(Node** head, int value) {

	if (NULL == *head) {
		printf("List is empty. Creating..\n");
		*head = CreateNewNode(value);
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
	if (NULL == *head) {
		printf("List is empty. Creating..\n");
		*head = CreateNewNode(value);
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
		return 0;
	}
	else {
		printf("Error: element %d not found\n", element_before_new);
		return 1;
	}
	
}

Node* SearchForElement(Node* head, int value, int print_index) {
	int found = 0, index = 0;
	Node* current_node = head;
	while (current_node != NULL) {
		if (current_node->value == value) {
			found = 1;
			break;
		}
		current_node = current_node->next_node;
		index++;
	}

	if (print_index) {
		if (found) printf("%d\n", index);
		else printf("-1\n");
		return NULL;
	}
	else {
		if (found) return current_node;
		else return NULL;
	}
}

Node* CreateNewNode(int value) {

	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL) {
		exit(1);
	}
	new_node->value = value;
	new_node->next_node = NULL;
	return new_node;
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

