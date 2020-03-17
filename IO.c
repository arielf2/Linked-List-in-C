#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "LinkedList.h"

#define MAX_LINE_LENGTH 100

int WhichCommand(Node** head, int num_of_args, char* command, int argument1, int argument2);

void ConvertToLowercase(char* str);

void UsageGuide();

int main() {
	
	char user_action[MAX_LINE_LENGTH];
	char command[MAX_LINE_LENGTH];
	int exitcode = 0, argument1 = 0, argument2 = 0;
	int num_of_arguments = -1;
	Node* head = NULL;

	while (exitcode == 0) {

		fgets(user_action, MAX_LINE_LENGTH, stdin);
		user_action[strlen(user_action) - 1] = '\0';

		ConvertToLowercase(user_action);

		argument1, argument2 = 0;
		num_of_arguments = sscanf(user_action, "%s %d %d", command, &argument1, &argument2);

		exitcode = WhichCommand(&head, num_of_arguments, command, argument1, argument2);
		
	}
	TerminateList(head);
	
}

int WhichCommand(Node** start, int num_of_args, char* command, int argument1, int argument2) {

	if (strcmp(command, "add_end") == 0 && num_of_args == 2) {
		InsertEndOfList(start, argument1);
	}
	else if (strcmp(command, "add_start") == 0 && num_of_args == 2) {
		InsertStartOfList(start, argument1);
	}
	else if (strcmp(command, "add_after") == 0 && num_of_args == 3) {
		return InsertAfterElement(start, argument1, argument2);
	}
	else if (strcmp(command, "index") == 0 && num_of_args == 2) {
		SearchForElement(*start, argument1, 1);
	}
	else if (strcmp(command, "del") == 0 && num_of_args == 2) {
		return RemoveIndex(start, argument1);
	}
	else if (strcmp(command, "print") == 0 && num_of_args == 1) {
		PrintList(*start);
	}
	else if (strcmp(command, "exit") == 0 && num_of_args == 1) {
		return 1;
	}
	else {
		printf("Unrecognized command or invalid num of arguments requested\n");
		UsageGuide();
	}
	return 0;
}

void ConvertToLowercase(char* str) {
	if (NULL == str) {
		printf("ConvertToLowercase received a NULL string\n");
		return;
	}
	else {
		int i = 0;
		for (i = 0; str[i] != '\0'; i++) {
			str[i] = tolower(str[i]);
		}
	}
}

void UsageGuide() {

	printf(	"\nPlease use one of the following allowed commands:\n\n"
			"add_end i:		add item i to the end of the list\n"
			"add_start i:		add item i to the start of the list\n"
			"add_after j i:		add item j after item i, if existing. If i not found, exit\n"
			"del i:			remove item i from the list, if found. If i not found, exit\n"
			"index i:		return the index of first occurence of item i\n"
			"print:			print the linked list in the following format : [i, j, k, ..]\n"
			"exit:			free the linked list and exit the program\n");
}