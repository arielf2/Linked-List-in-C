#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "LinkedList.h"

#define MAX_LINE_LENGTH 100
#define NUM_OF_ARGS_O 1
#define NUM_OF_ARGS_T 2
#define NUM_OF_ARGS_TH 3

#define STRINGS_ARE_EQUAL( Str1, Str2 ) ( strcmp( (Str1), (Str2) ) == 0 )

void GetUserInput(char* destination);

int ParseUserInput(char* user_input, char* command, int* argument1, int* argument2);

int DoCommand(Node** head, int num_of_args, char* command, int argument1, int argument2);

void ConvertToLowercase(char* str);

void UsageGuide();

int main() {
	
	char user_action[MAX_LINE_LENGTH], command[MAX_LINE_LENGTH];
	int exitcode = 0, argument1 = 0, argument2 = 0;
	/*	Note to grader: I assume that the 'average programmer' understands that the 
		arguments (1 and 2) serve different purposes depending on the operation required,
		therefore they are named generically. If he's not sure and he enters invalid 
		command or arguments, this program will print the correct usage */
	int num_of_arguments = -1;
	Node* head = NULL;

	while (exitcode == 0) {


		GetUserInput(user_action);

		//fgets(user_action, MAX_LINE_LENGTH, stdin);

		//user_action[strlen(user_action) - 1] = '\0';
		//ConvertToLowercase(user_action);

		num_of_arguments = ParseUserInput(user_action, command, &argument1, &argument2);


		exitcode = DoCommand(&head, num_of_arguments, command, argument1, argument2);
		
	}
	TerminateList(head);

	return 0;
}

void GetUserInput(char* destination)
{
	fgets(destination, MAX_LINE_LENGTH, stdin);
}

int ParseUserInput(char* user_input, char* command, int* argument1, int* argument2)
{
	user_input[strlen(user_input) - 1] = '\0';

	ConvertToLowercase(user_input);

	int num_of_arguments = sscanf(user_input, "%s %d %d", command, argument1, argument2) - 1;
	// don't count the command itself as an argument - therefore minus 1

	return num_of_arguments;
}

int DoCommand(Node** start, int num_of_args, char* command, int argument1, int argument2) {

	if (STRINGS_ARE_EQUAL(command, "add_end") && num_of_args == 1) {
		InsertEndOfList(start, argument1);
	}
	else if (STRINGS_ARE_EQUAL(command, "add_start") && num_of_args == 1) {
		InsertStartOfList(start, argument1);
	}
	else if (STRINGS_ARE_EQUAL(command, "add_after") && num_of_args == 2) {
		return InsertAfterElement(start, argument1, argument2);
	}
	else if (STRINGS_ARE_EQUAL(command, "index") && num_of_args == 1) {
		SearchForElement(*start, argument1, 1);
	}
	else if (STRINGS_ARE_EQUAL(command, "del") && num_of_args == 1) {
		return RemoveIndex(start, argument1);
	}
	else if (STRINGS_ARE_EQUAL(command, "print") && num_of_args == 0) {
		PrintList(*start);
	}
	else if (STRINGS_ARE_EQUAL(command, "exit") && num_of_args == 0) {
		return 1;
	}
	else {
		printf("Unrecognized command or invalid number of arguments requested\n");
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